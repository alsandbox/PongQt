#include "BallRenderer.h"

#include <QGraphicsEllipseItem>
#include <random>


BallRenderer::BallRenderer(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer)
: m_scene(scene), m_line(lineRenderer) {
    ball = std::make_unique<QGraphicsEllipseItem>();
    m_scene->addItem(ball.get());
}

void BallRenderer::spawnBall(const QSize newSize) {
    displayBall(newSize);
    QLineF line = m_line->getLine()->line();
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(line.y1() + m_buffer,  line.y2() - m_buffer);
    ball->setPos(line.x1(), distrib(gen));
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
    const int ballSize = std::min(newSize.width(), newSize.height()) / 30;

    const QPointF currentPos = ball->pos();
    ball->setRect(0, 0, ballSize, ballSize);
    ball->setPos(currentPos);
}
