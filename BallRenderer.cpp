#include "BallRenderer.h"
#include <QGraphicsEllipseItem>

BallRenderer::BallRenderer(QGraphicsScene *scene)
: m_scene(scene) {
    ball = std::make_unique<QGraphicsEllipseItem>();
    m_scene->addItem(ball.get());
}

void BallRenderer::setBounds(const QRectF& bounds) {
    m_bounds = bounds;
}

void BallRenderer::resizeEvent(const QResizeEvent* event) const {
    const QSize newSize = event->size();
    displayBall(newSize);
}

void BallRenderer::displayBall(const QSize newSize) const {
    const QPen pen(Qt::white);
    const QBrush brush(Qt::white);

    ball->setPen(pen);
    ball->setBrush(brush);
    const int ballSize = std::min(newSize.width(), newSize.height()) / 30;

    ball->setRect(
        (newSize.width() - ballSize) / 3.0,
        (newSize.height() - ballSize) / 2.0,
        ballSize,
        ballSize
    );
}
