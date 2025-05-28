#include <QTimer>
#include "BallMovement.h"
#include <cmath>

#include "ScoreManager.h"

BallMovement::BallMovement(const std::shared_ptr<BallRenderer> &ball, const std::shared_ptr<ScoreManager> &scoreManager,
                           const PlayerItem *leftPlayer, const PlayerItem *rightPlayer)
    : m_ball(ball), m_scoreManager(scoreManager), m_leftPlayer(leftPlayer), m_rightPlayer(rightPlayer) {
    m_direction = QPointF(3, 5);
    m_speed = 3.0;
    qreal length = std::sqrt(m_direction.x() * m_direction.x() + m_direction.y() * m_direction.y());
    const qreal length = std::sqrt(m_direction.x() * m_direction.x() + m_direction.y() * m_direction.y());
    m_direction /= length;
}

void BallMovement::setBounds(const QRectF& bounds) {
    m_bounds = bounds;
}

void BallMovement::moveBall() {
    QPointF velocity = m_direction * m_speed;

    QPointF newPos = m_ball->getBall()->pos();
    newPos += velocity;

    const qreal ballBottom = m_ball->getBall()->boundingRect().translated(newPos).bottom();
    const qreal ballTop = m_ball->getBall()->boundingRect().translated(newPos).top();
    const qreal ballLeft = m_ball->getBall()->boundingRect().translated(newPos).left();
    const qreal ballRight = m_ball->getBall()->boundingRect().translated(newPos).right();

    if (ballBottom > m_bounds.bottom() || ballTop <= 0) {
        m_direction.setY(-m_direction.y());
    }
    if (ballLeft > m_bounds.left() && ballRight > m_bounds.right() + m_ball->getBall()->boundingRect().width() * 2) {
        m_timer->stop();
    }

    m_ball->getBall()->setPos(newPos);
    detectPlayer();
}

void BallMovement::detectPlayer() {
    if (m_ball->getBall()->collidesWithItem(m_leftPlayer) || m_ball->getBall()->collidesWithItem(m_rightPlayer)) {
        m_direction.setY(-m_direction.y());
        m_direction.setX(-m_direction.x());
    }
}


void BallMovement::updateFrame() {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &BallMovement::moveBall);
    m_timer->start(16);
}