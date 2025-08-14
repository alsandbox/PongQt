#include "BallRenderer.h"

#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QRandomGenerator>

BallRenderer::BallRenderer(QGraphicsScene *scene, LineRenderer* lineRenderer)
    : m_scene(scene), m_line(lineRenderer) {
    ball = std::make_unique<QGraphicsRectItem>();
    m_scene->addItem(ball.get());
    ball->setCacheMode(DeviceCoordinateCache);
}

void BallRenderer::spawnBall() const {
    if (m_line->getLine() && ball){
        const QLineF line = m_line->getLine()->line();
        const int m_min = static_cast<int>(line.y1() + m_buffer);
        const int m_max = static_cast<int>(line.y2() - m_buffer);
        const int randomValue = QRandomGenerator::global()->bounded(m_min, m_max);
        ball->setPos(line.x1(), randomValue);
    }
}

void BallRenderer::setBounds(const QRectF& bounds) {
    m_bounds = bounds;
}

void BallRenderer::resizeEvent(const QResizeEvent* event) {
    m_size = event->size();
    if (ball) {
       displayBall();
    }
}

void BallRenderer::displayBall() const {
    const QPen pen(Qt::white);
    const QBrush brush(Qt::white);

    ball->setPen(pen);
    ball->setBrush(brush);

    constexpr int scalingFactor = 40;

    const int ballSize = std::min(m_size.width(), m_size.height()) / scalingFactor;
    ball->setRect(0, 0, ballSize, ballSize);
}

void BallRenderer::setVisible(const bool visible) const {
    ball ? void() : throw std::runtime_error("Ball is null");

    if (!visible) {
        ball->hide();
    }
    else {
        ball->show();
    }
}


