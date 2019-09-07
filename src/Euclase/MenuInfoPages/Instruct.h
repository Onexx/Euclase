#pragma once

#include <QFileDialog>
#include <QGraphicsScene>
#include <QPen>
#include <QWidget>
#include "ui_Instruct.h"

namespace Ui {
class Instruct;
}

class Instruct : public QWidget {
    Q_OBJECT

  public:
    explicit Instruct(QWidget *parent = nullptr);
    ~Instruct();

  private:
    Ui::Instruct *ui;
    QGraphicsScene *scene;
};
