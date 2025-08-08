#include "GameManager.h"
#include <QDateTime>


GameManager::GameManager(QGraphicsScene* scene, GameOverScreen* gameOverScreen): m_gameOverScreen(gameOverScreen) {
    m_leftPlayer = std::make_shared<PlayerItem>(Qt::Key_W, Qt::Key_S, scene);
    m_rightPlayer = std::make_shared<PlayerItem>(Qt::Key_Up, Qt::Key_Down, scene);
    m_timer = new QTimer(this);
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


float GameManager::changeSpeedAfterResize(const QSize& size) {
    if (!m_isInitSize) {
        m_initialWidth  = size.width();
        m_isInitSize = true;
    }

    float scaleRatio = 1.0f;
    if (m_initialWidth > 0 && size.width() > 0) {
        scaleRatio = static_cast<float>(size.width()) / static_cast<float>(m_initialWidth);
    }

    return scaleRatio;
}

void GameManager::updateFrame(std::function<void(qint64)> updateFunc) {
    m_updateFunc = std::move(updateFunc);

    if (!m_timer->isActive() && !isGameOver) {
        m_timer->start();
        m_lastUpdate = QDateTime::currentMSecsSinceEpoch();
        connect(m_timer, &QTimer::timeout, this, [this]() {
            const auto now = QDateTime::currentMSecsSinceEpoch();
            const qint64 delta = now - m_lastUpdate;
            m_lastUpdate = now;
            m_updateFunc(delta);
        });
    }
}

void GameManager::stopFrame() {
    if (m_timer->isActive()) {
        isGameOver = true;
        m_timer->stop();
        m_gameOverScreen->removeElements();
        m_gameOverScreen->addButtons();
    }
}
