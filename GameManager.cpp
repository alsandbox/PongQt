#include "GameManager.h"

GameManager::GameManager(QGraphicsScene* scene) {
    m_leftPlayer = std::make_shared<PlayerItem>(Qt::Key_W, Qt::Key_S, scene);
    m_rightPlayer = std::make_shared<PlayerItem>(Qt::Key_Up, Qt::Key_Down, scene);
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, [this]() {
    if (m_updateFunc) m_updateFunc();
});
}

void GameManager::keyPressEvent(QKeyEvent* event) {
    if (m_leftPlayer)
        m_leftPlayer->keyPressEvent(event);
    if (m_rightPlayer)
        m_rightPlayer->keyPressEvent(event);
}

void GameManager::keyReleaseEvent(QKeyEvent *event) {
    if (m_leftPlayer)
        m_leftPlayer->keyReleaseEvent(event);
    if (m_rightPlayer)
        m_rightPlayer->keyReleaseEvent(event);
}

void GameManager::updateFrame(const std::function<void()> &func) {
    m_updateFunc = func;
    if (!m_timer->isActive()) {
        constexpr int frameIntervalMs = 16;
        m_timer->start(frameIntervalMs);
    }
}

