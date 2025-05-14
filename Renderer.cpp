#include "Renderer.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"


Renderer::Renderer(QGraphicsScene *scene, QWidget* parent) : QGraphicsView(scene, parent) {
    setScene(scene);
    setBackgroundBrush(Qt::black);
    setRenderHint(QPainter::Antialiasing);
    setResizeAnchor(AnchorViewCenter);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    playerRenderer = std::make_unique<PlayerRenderer>(scene, this);
    scoreRenderer = std::make_unique<ScoreRenderer>(scene);
    ballRenderer = std::make_unique<BallRenderer>(scene);
}

void Renderer::resizeEvent(QResizeEvent* event){
    QGraphicsView::resizeEvent(event);

    const QRectF rect(QPointF(0, 0), QSizeF(size()));
    scene()->setSceneRect(rect);

    if (playerRenderer)
        playerRenderer->resizeEvent(event);
    if (scoreRenderer)
        scoreRenderer->resizeEvent(event);
    if (ballRenderer)
        ballRenderer->resizeEvent(event);

    displayLine(rect);

    fitInView(scene()->sceneRect(), Qt::IgnoreAspectRatio);
}
void Renderer::keyPressEvent(QKeyEvent* event) {
    if (leftPlayer) {
        if (event->key() == Qt::Key_W) leftPlayer->moveBy(0, -10);
        if (event->key() == Qt::Key_S) leftPlayer->moveBy(0, 10);
    }
    if (rightPlayer) {
        if (event->key() == Qt::Key_Up) rightPlayer->moveBy(0, -10);
        if (event->key() == Qt::Key_Down) rightPlayer->moveBy(0, 10);
    }
}

void Renderer::keyReleaseEvent(QKeyEvent* event) {
    QGraphicsView::keyReleaseEvent(event);
}

void Renderer::setLeftPlayer(PlayerItem* player) {
    leftPlayer = player;
}

void Renderer::setRightPlayer(PlayerItem* player) {
    rightPlayer = player;
}
void Renderer::displayLine(const QRectF &rect) {
    if (!lineItem) {
        QPen pen(Qt::white);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(5);
        lineItem = scene()->addLine(QLineF(rect.width() / 2, 0, rect.width() / 2, rect.height()), pen);
    } else {
        lineItem->setLine(QLineF(rect.width() / 2, 0, rect.width() / 2, rect.height()));
    }
}