#include "PlayerRenderer.h"

#include "../managers/GameManager.h"
#include "../PlayerItem.h"


PlayerRenderer::PlayerRenderer(QGraphicsScene *scene, GameManager* gameManager)
    : m_gameManager(gameManager), m_scene(scene) {
    m_rightPlayer = m_gameManager->getRightPlayer();
    m_leftPlayer = m_gameManager->getLeftPlayer();
}

void PlayerRenderer::resizeEvent(QResizeEvent *event) {
    if (m_leftPlayer && !m_leftPlayerAdded) {
        m_scene->addItem(m_leftPlayer.get());
        m_leftPlayerAdded = true;
    }
    if (m_rightPlayer && !m_rightPlayerAdded) {
        m_scene->addItem(m_rightPlayer.get());
        m_rightPlayerAdded = true;
    }
    displayPlayer(m_leftPlayer.get(), true);
    displayPlayer(m_rightPlayer.get(), false);
}

void PlayerRenderer::setBounds(const QRectF &bounds) {
    m_bounds = bounds;
}

void PlayerRenderer::displayPlayer(PlayerItem *player, const bool isLeft) const {
    const QPen pen(Qt::white);
    const QBrush brush(Qt::white);
    player->setPen(pen);
    player->setBrush(brush);

    constexpr double paddleWidthRatio = 0.015;
    constexpr double paddleHeightRatio = 0.1;

    const double width = m_bounds.width() * paddleWidthRatio;
    const double height = m_bounds.height() * paddleHeightRatio;

    constexpr double half = 2.0;
    const double yPos = (m_bounds.height() - height) / half;
    const double xPos = isLeft
                            ? m_bounds.left()
                            : m_bounds.right() - width;

    player->setRect(0, 0, width, height);
    player->setPos(xPos, yPos);
}
