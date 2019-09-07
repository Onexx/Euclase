#include "RegistrationForm.h"

#include "Statistics/logs.h"
#include "data.h"

RegistrationForm::RegistrationForm(QWidget* parent)
    : QWidget(parent), ui(new Ui::RegistrationForm) {
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    QFile file("Settings/Host.txt");
    if (file.open(QIODevice::ReadWrite)) {
        const QString ip = QString::fromUtf8(file.readLine());
        mHostAddress.setAddress(ip);
    }

    // Connecting all buttons
    connect(ui->requestButton, &QPushButton::pressed, this,
            &RegistrationForm::onIdRequest);
    connect(ui->registerButton, &QPushButton::pressed, this,
            &RegistrationForm::onRegRequest);

    // Setting names to buttons from language file
    ui->requestButton->setText(Data::regForm::reqBtn);
    ui->registerButton->setText(Data::regForm::regBtn);
    ui->label_enter->setText(Data::regForm::enterLbl);
    ui->label_name->setText(Data::regForm::nameLbl);
}

/**
 * Requests guest name from server using provided id
 */
void RegistrationForm::onIdRequest() {
    const QString id = ui->lineEditId->text();
    LogPrint("Requesting guest name");
    if (id.isEmpty()) {
        LogPrint("Id field is empty");
        return;
    }
    LogPrint("Guest id: " + id);
    mCurrentSocket.reset(new QTcpSocket());
    mCurrentSocket->connectToHost(mHostAddress, 9999);
    mCurrentSocket->waitForConnected();
    QString request = QString("id %1").arg(id);
    mCurrentSocket->write(request.toLocal8Bit(), request.size());
    mCurrentSocket->waitForBytesWritten();
    mCurrentSocket->waitForReadyRead();
    QString localTrimmed =
        QString::fromLocal8Bit(mCurrentSocket->readAll()).trimmed();
    if (localTrimmed.contains(id)) {
        QString name =
            localTrimmed.split(QRegExp("[\r\n]"), QString::SkipEmptyParts)[0]
                .section("name: ", 1);
        ui->lineEditName->setText(name);
        LogPrint("Guest name: " + name);
    }
}

/**
 * Sends registration query to server and prints personal guest badge
 */
void RegistrationForm::onRegRequest() {
    if (mCurrentSocket->isOpen()) {
        mCurrentSocket->write("Y", 1);
        Printer* printer = new Printer();
        QString PName;
        QFile file("Settings/PrinterName.txt");
        if (file.open(QIODevice::Text | QIODevice::ReadOnly)) {
            PName = file.readLine();
        } else {
            qDebug() << "Printer name not found";
            LogPrint("Printer name not found");
        }
        LogPrint("Started printing guest badge");
        LogPrint("Configured printer:" + PName);
        printer->configurePrinter(PName);
        QString id = ui->lineEditId->text(), name = ui->lineEditName->text();
        LogPrint("Guest id: " + id);
        LogPrint("Guest name: " + name);
        printer->Print(id, name);
        mCurrentSocket->waitForBytesWritten();
    }
}

RegistrationForm::~RegistrationForm() {}
