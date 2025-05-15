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
    QPointF newPos = pos();

    if (event->key() == m_upKey)
        newPos.ry() -= 10;
    else if (event->key() == m_downKey)
        newPos.ry() += 10;

    const QRectF itemRect = boundingRect().translated(newPos);
    if (m_bounds.contains(itemRect))
        setPos(newPos);
}