#include "PlayerRenderer.h"
#include "PlayerItem.h"
#include "Renderer.h"

#include <QWidget>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QKeyEvent>


PlayerRenderer::PlayerRenderer(QGraphicsScene *scene, Renderer* renderer)
    : m_scene(scene) {
    leftPlayer = std::make_unique<PlayerItem>(Qt::Key_W, Qt::Key_S, scene);
    rightPlayer = std::make_unique<PlayerItem>(Qt::Key_Up, Qt::Key_Down, scene);

    renderer = dynamic_cast<Renderer*>(m_scene->views().first());
    if (renderer) {
        renderer->setLeftPlayer(leftPlayer.get());
        renderer->setRightPlayer(rightPlayer.get());
    }
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
    const double height = rect.height() * 0.1;
    const double yPos = (rect.height() - height) / 2;
    const double xPos = isLeft ? rect.left() + margin: rect.right() - width - margin;

    player->setRect(0, 0, width, height);
    player->setPos(xPos, yPos);
}
