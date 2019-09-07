#include "mainWindow.h"

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtNetwork/QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      saveResultsAction(new QAction(this)),
      mServer(new QTcpServer) {
    ui->setupUi(this);
    setWindowTitle("Status");
    ui->registrationStatus->setModel(&mModel);
    ui->registrationStatus->resizeColumnsToContents();
    ui->registrationStatus->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch);

    saveResultsAction->setText("Save");
    connect(saveResultsAction, &QAction::toggled, this,
            &MainWindow::writeRowsToCsv);
    QMenu *localQMenu = new QMenu("Tools", this);
    ui->menuBar->addMenu(localQMenu);
    localQMenu->addAction(saveResultsAction);

    readRowsFromCsv();

    connect(mServer.data(), &QTcpServer::newConnection, this,
            &MainWindow::onNewConnection);
    if (!mServer->listen(QHostAddress::Any, 9999)) {
        qDebug() << "Server could not start";
    } else {
        qDebug() << "Server started!";
    }
}

void MainWindow::onNewConnection() {
    QTcpSocket *socket = mServer->nextPendingConnection();
    socket->readAll();

    socket->waitForReadyRead();
    QString request = QString::fromUtf8(socket->readAll());

    if (request.startsWith("id")) {
        qDebug() << request;
        const QString id = request.section("id", 1).trimmed();
        qDebug() << QString("line with id %1 requested").arg(id);

        QString fio = "";
        for (int i = 0; i < mModel.rowCount(); ++i) {
            if (mModel.item(i, 0)->text() == id) {
                fio = mModel.item(i, 1)->text();
                break;
            }
        }

        socket->write(QString("ID: %1, name: %2\n Register?(Y/N):")
                          .arg(id)
                          .arg(fio)
                          .toLocal8Bit());
        socket->waitForBytesWritten();

        socket->waitForReadyRead();
        request = QString::fromUtf8(socket->readAll());

        if (request.contains("Y")) {
            for (int i = 0; i < mModel.rowCount(); ++i) {
                if (mModel.item(i, 0)->text() == id) {
                    mModel.item(i, 2)->setText("Registered");
                    break;
                }
            }

            socket->write(QString("ID: %1, name: %2 Registered\n")
                              .arg(id)
                              .arg(fio)
                              .toLocal8Bit());
            socket->waitForBytesWritten();
            qDebug() << "registration approved";
        } else {
            qDebug() << "registration failed";
        }

    } else {
        qDebug() << "wrong request from client" << request << "got";
    }

    socket->close();
    delete socket;
}

void MainWindow::readRowsFromCsv() {
    QFile file("participants.csv");
    if (file.exists() && file.open(QIODevice::ReadWrite)) {
        QStringList rows =
            QString::fromUtf8(file.readAll())
                .split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
        for (int i = 0; i < rows.length(); ++i) {
            QStringList participant = rows[i].split(';');
            mModel.insertRow(i);
            mModel.setItem(i, 0, new QStandardItem(participant[0]));
            mModel.setItem(i, 1, new QStandardItem(participant[1].trimmed()));
            mModel.setItem(
                i, 2,
                new QStandardItem(participant[2].toInt() ? "Registered"
                                                         : "Not registered"));
        }

        file.close();
    } else {
        qDebug() << "Can't open csv file";
    }
}

void MainWindow::writeRowsToCsv() {
    QFile file("participants.csv");
    if (file.open(QIODevice::ReadWrite)) {
        for (int i = 0; i < mModel.rowCount(); ++i) {
            auto row =
                QString("%1,%2,%3")
                    .arg(mModel.item(i)->text())
                    .arg(mModel.item(i, 1)->text())
                    .arg(mModel.item(i, 2)->text() == "Registered" ? 1 : 0);
            file.write(row.toLocal8Bit(), row.length());
        }

        file.close();
    }
}

MainWindow::~MainWindow() { delete ui; }
