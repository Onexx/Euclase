#pragma once

#include <QFile>
#include <QWidget>
#include <QtCore/QWeakPointer>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QTcpSocket>
#include "Navig/BarcodePrinter/Printer.h"
#include "ui_RegistrationForm.h"

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget {
    Q_OBJECT

  public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

  private:
    void onIdRequest();
    void onRegRequest();

  private:
    Ui::RegistrationForm *ui;
    QScopedPointer<QTcpSocket> mCurrentSocket;
    QHostAddress mHostAddress;
};
