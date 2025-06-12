#include "BallRenderer.h"

#include <QGraphicsEllipseItem>
#include <QRandomGenerator>

BallRenderer::BallRenderer(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer, const std::shared_ptr<PhysicsManager>& physicsManager)
    ball = std::make_unique<QGraphicsEllipseItem>();
    m_scene->addItem(ball.get());
}

void BallRenderer::spawnBall(const QSize newSize) const {
    displayBall(newSize);

    const QLineF line = m_line->getLine()->line();
    const int m_min = static_cast<int>(line.y1() + m_buffer);
    const int m_max = static_cast<int>(line.y2() - m_buffer);
    const int randomValue = QRandomGenerator::global()->bounded(m_min, m_max);
    ball->setPos(line.x1(), randomValue);
}

void BallRenderer::setBounds(const QRectF& bounds) {
    m_bounds = bounds;
}

void BallRenderer::resizeEvent(const QResizeEvent* event) {
    newSize = event->size();
    spawnBall(newSize);
}

void BallRenderer::displayBall(const QSize newSize) const {
    const QPen pen(Qt::white);
    const QBrush brush(Qt::white);

    ball->setPen(pen);
    ball->setBrush(brush);
    constexpr int scalingFactor = 35;
    const int ballSize = std::min(newSize.width(), newSize.height()) / scalingFactor;

    const QPointF currentPos = ball->pos();
    ball->setRect(0, 0, ballSize, ballSize);
    ball->setPos(currentPos);
}
