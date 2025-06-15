#include "PlayerRenderer.h"

#include "PlayerItem.h"
#include <QGraphicsView>
#include <QWidget>
#include "GameManager.h"


PlayerRenderer::PlayerRenderer(QGraphicsScene *scene, const std::shared_ptr<GameManager> &gameManager)
    : m_gameManager(gameManager), m_scene(scene){
    m_rightPlayer = m_gameManager->getRightPlayer();
    m_leftPlayer = m_gameManager->getLeftPlayer();
}

void PlayerRenderer::resizeEvent(QResizeEvent *event) {
    if (leftPlayer && !leftPlayerAdded) {
        m_scene->addItem(leftPlayer.get());
        leftPlayerAdded = true;
    }
    if (rightPlayer && !rightPlayerAdded) {
        m_scene->addItem(rightPlayer.get());
        rightPlayerAdded = true;
    }
    displayPlayer(leftPlayer.get(), true);
    m_physicsManager->createBoxShape(leftPlayer.get(), true);
    displayPlayer(rightPlayer.get(), false);
    m_physicsManager->createBoxShape(rightPlayer.get(), false);
}

void PlayerRenderer::setBounds(const QRectF &bounds) {
    m_bounds = bounds;
}

void PlayerRenderer::displayPlayer(PlayerItem *player, const bool isLeft) const {
    const QPen pen(Qt::white);
    const QBrush brush(Qt::white);
    player->setPen(pen);
    player->setBrush(brush);

    const QRectF rect = m_scene->sceneRect();

    const double width = rect.width() * 0.01;
    const double height = rect.height() * 0.1;
    const double yPos = (rect.height() - height) / 2;
    const double xPos = isLeft ? rect.left() + margin : rect.right() - width - margin;
    player->setRect(0, 0, width, height);
    player->setPos(xPos, yPos);
}
