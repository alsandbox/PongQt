#include "PlayerItem.h"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QKeyEvent>


PlayerItem::PlayerItem(const Qt::Key upKey, const Qt::Key downKey, QGraphicsScene *scene)
        : m_upKey(upKey), m_downKey(downKey), m_scene(scene) {
    setFlag(ItemIsFocusable);
}

void PlayerItem::setBounds(const QRectF& bounds) {
    m_bounds = bounds;
}

void PlayerItem::keyPressEvent(QKeyEvent* event) {
    m_prevPos = pos();

    QPointF newPos = m_prevPos;

    if (event->key() == m_upKey)
        newPos.ry() -= m_moveStep * m_speed;
    else if (event->key() == m_downKey)
        newPos.ry() += m_moveStep * m_speed;

    const QRectF itemRect = boundingRect().translated(newPos);
    if (m_bounds.contains(itemRect)) {
        setPos(newPos);
        m_verticalSpeed = newPos.y() - m_prevPos.y();
    } else {
        m_verticalSpeed = 0;
    }
}
