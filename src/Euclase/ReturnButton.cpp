#include "ReturnButton.h"

#include "Menu.h"
#include "data.h"

ReturnButton::ReturnButton(QWidget *parent)
    : QWidget(parent), ui(new Ui::ReturnButton) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    connect(ui->PbReturn, &QPushButton::clicked, this, &ReturnButton::Return);
    ui->PbReturn->setText(Data::btnNames::Return);
}

/**
 * Returns to menu
 */
void ReturnButton::Return() {
    menu->show();
    soundTimer->stop();
    curSound->stop();
    retSound->stop();
    if (!nav->isHidden()) {
        nav->hide();
    }
    if (!info->isHidden()) {
        info->hide();
    }
    if (!prtn->isHidden()) {
        prtn->hide();
    }
    if (!descr->isHidden()) {
        descr->hide();
    }
    if (!tmtbl->isHidden()) {
        tmtbl->hide();
    }
    if (!reg->isHidden()) {
        reg->hide();
    }
    if (!instr->isHidden()) {
        instr->hide();
    }
    this->hide();
}

ReturnButton::~ReturnButton() { delete ui; }
