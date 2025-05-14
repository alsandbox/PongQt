#include "PlayerItem.h"

#include <QGraphicsItem>
#include <QKeyEvent>

PlayerItem::PlayerItem(const Qt::Key upKey, const Qt::Key downKey)
        : m_upKey(upKey), m_downKey(downKey) {
    setFlag(ItemIsFocusable);
}

void PlayerItem::keyPressEvent(QKeyEvent* event) {
    if (event->key() == m_upKey)
        moveBy(0, -10);
    else if (event->key() == m_downKey)
        moveBy(0, 10);
}