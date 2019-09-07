#pragma once
#include <QStandardItemModel>
#include <QtCore/QScopedPointer>
#include <QtNetwork/QTcpServer>
#include <QtWidgets/QMainWindow>

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void onNewConnection();

  private:
    void readRowsFromCsv();
    void writeRowsToCsv();

    Ui::MainWindow *ui;
    QAction *saveResultsAction;
    QScopedPointer<QTcpServer> mServer;
    QStandardItemModel mModel;
};
