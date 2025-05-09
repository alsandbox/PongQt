#include "PlayerRenderer.h"
#include <QGraphicsRectItem>
#include <QGraphicsView>

PlayerRenderer::PlayerRenderer(QGraphicsScene *scene)
    : m_scene(scene) {
    rightPlayer = std::make_unique<QGraphicsRectItem>();
    leftPlayer = std::make_unique<QGraphicsRectItem>();
}

void PlayerRenderer::resizeEvent(QResizeEvent* event) {
    if (leftPlayer && !leftPlayerAdded) {
        m_scene->addItem(leftPlayer.get());
        leftPlayerAdded = true;
    }
    if (rightPlayer && !rightPlayerAdded) {
        m_scene->addItem(rightPlayer.get());
        rightPlayerAdded = true;
    }
    displayPlayer(leftPlayer.get(), true);
    displayPlayer(rightPlayer.get(), false);
}

void PlayerRenderer::displayPlayer(QGraphicsRectItem* player, const bool isLeft) const {
    const QPen pen(Qt::white);
    const QBrush brush(Qt::white);
    player->setPen(pen);
    player->setBrush(brush);

    const QRectF rect = m_scene->sceneRect();

    const double width = rect.width() * 0.01;;
    const double height = rect.height() * 0.18;
    const double yPos = (rect.height() - height) / 2;
    const double xPos = isLeft ? rect.left() + margin: rect.right() - width - margin;

    player->setRect(0, 0, width, height);
    player->setPos(xPos, yPos);
}
