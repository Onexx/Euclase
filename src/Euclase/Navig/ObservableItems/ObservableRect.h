#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QSound>

#include "Navig/BarcodePrinter/BarcodePrinter.h"
#include "Navig/Navig.h"
#include "Statistics/Logs.h"
#include "data.h"

class ObservableRect : public QGraphicsRectItem {
  public:
    explicit ObservableRect(const QRectF& rect, QGraphicsItem* parent = 0);
    QRectF boundingRect() const Q_DECL_OVERRIDE;

    enum PointType {
        None,
        ResizeLeftTop,
        ResizeTop,
        ResizeRightTop,
        ResizeLeft,
        ResizeRight,
        ResizeLeftBottom,
        ResizeBottom,
        ResizeRightBottom,
        Rotate,
        Move
    };

    qreal kw = 1, kh = 1;

  private:
    PointType pointTypeAtPos(const QPointF& pos) const;
    void setCursorShape(const QPointF& pos);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
    void BCGen(QString number, QString name);

    bool resizeEvent = false;

    qreal w = 1, h = 1;
    qreal kx, ky, alpha;
    qreal kx0, ky0, alpha0;

    PointType pointType;

    QPointF startItemPoint;
    QPointF startMousePoint;
    QPointF previousPosition;

    QTransform transform, transform_inv;

    QSound* sound;

  protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) Q_DECL_OVERRIDE;
    void hoverMoveEvent(QGraphicsSceneHoverEvent* event) Q_DECL_OVERRIDE;
};
