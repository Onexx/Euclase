#pragma once

#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QPen>
#include "DragAndDrop/DragCircle.h"
#include "DragAndDrop/DragRect.h"
#include "DragAndDrop/DropScene.h"
#include "ObservableItems/ObservableCircle.h"
#include "ObservableItems/ObservableRect.h"
#include "Statistics/Statistics.h"
#include "Statistics/logs.h"
#include "ui_Navig.h"

namespace Ui {
class Navig;
}
class Menu;

/**
 * Describes navigation page in menu
 */
class Navig : public QWidget {
    Q_OBJECT

  public:
    explicit Navig(QWidget* parent = nullptr);

    ~Navig() Q_DECL_OVERRIDE;

    void keyPressEvent(QKeyEvent* event) Q_DECL_OVERRIDE;

    Ui::Navig* ui;
    bool isBlocked = false;
    QGraphicsScene* scene3;

  private slots:
    void Block();
    void Open();
    void OpenMap();
    void SaveMap();

  private:
    QGraphicsScene* scene;
};
