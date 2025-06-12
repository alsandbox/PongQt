#include "GameManager.h"

GameManager::GameManager(QGraphicsScene* scene) {
    m_leftPlayer = std::make_shared<PlayerItem>(Qt::Key_W, Qt::Key_S, scene);
    m_rightPlayer = std::make_shared<PlayerItem>(Qt::Key_Up, Qt::Key_Down, scene);
}

void GameManager::keyPressEvent(QKeyEvent* event) {
    if (m_leftPlayer)
        m_leftPlayer->keyPressEvent(event);
    if (m_rightPlayer)
        m_rightPlayer->keyPressEvent(event);
}

void GameManager::keyReleaseEvent(QKeyEvent* event) {
    QGraphicsView::keyReleaseEvent(event);
}