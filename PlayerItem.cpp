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
    const QPointF currentPos = pos();
    QPointF newPos = currentPos;

    if (event->key() == m_upKey)
        newPos.ry() -= m_moveStep * m_speed;
    else if (event->key() == m_downKey)
        newPos.ry() += m_moveStep * m_speed;

    const QRectF itemRect = boundingRect().translated(newPos);
    if (m_bounds.contains(itemRect))
        setPos(newPos);
}

void PlayerItem::setPlayerPartitions() {
    m_playerPartitions.clear();
    double part = 0;
    for (int i = 0; i < 5 ; i++) {
        part = i * rect().height() / 5;
        m_playerPartitions.push_back(part);
    }
}
