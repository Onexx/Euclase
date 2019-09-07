#pragma once

#include <QFileDialog>
#include <QGraphicsScene>
#include <QPen>
#include <QWidget>
#include "ui_InfoView.h"

namespace Ui {
class InfoView;
}

class InfoView : public QWidget {
    Q_OBJECT

  public:
    explicit InfoView(QWidget *parent = nullptr);
    ~InfoView();

  private:
    Ui::InfoView *ui;
    QGraphicsScene *scene;
};
