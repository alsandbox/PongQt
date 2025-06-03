#ifndef PLAYERITEM_H
#define PLAYERITEM_H
#include <QGraphicsRectItem>

#include "IBoundable.h"


class PlayerItem : public QGraphicsRectItem, public IBoundable {
public:
    PlayerItem(Qt::Key upKey, Qt::Key downKey, QGraphicsScene *scene);
    void setBounds(const QRectF& bounds) override;
    void keyPressEvent(QKeyEvent* event) override;
    qreal getVerticalSpeed() const { return m_verticalSpeed; }

private:
    Qt::Key m_upKey;
    Qt::Key m_downKey;
    QGraphicsScene* m_scene = nullptr;
    QRectF m_bounds;
    int m_moveStep = 3;
    float m_speed = 10.0f;
    QPointF m_prevPos;
    qreal m_verticalSpeed;
};




#endif //PLAYERITEM_H
