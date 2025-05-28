#include <QTimer>
#include "BallMovement.h"
#include <cmath>
#include <qcoreapplication.h>

#include "ScoreManager.h"

BallMovement::BallMovement(const std::shared_ptr<BallRenderer> &ball, const std::shared_ptr<ScoreManager> &scoreManager,
                           const PlayerItem *leftPlayer, const PlayerItem *rightPlayer)
    : m_ball(ball), m_scoreManager(scoreManager), m_leftPlayer(leftPlayer), m_rightPlayer(rightPlayer) {
    m_direction = QPointF(3, 5);
    m_speed = 4.0;
    const qreal length = std::sqrt(m_direction.x() * m_direction.x() + m_direction.y() * m_direction.y());
    m_direction /= length;
    m_timer = new QTimer(this);
}

void BallMovement::resizeEvent(QResizeEvent* event) {
    m_size = event->size();
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

    if (handleOutOfBounds(ballLeft, ballRight)){
        return;
    }

    m_ball->getBall()->setPos(newPos);
    detectPlayer();
}

bool BallMovement::handleOutOfBounds(qreal ballLeft, qreal ballRight) {
    if (m_waitingToRespawn) return true;

    const qreal buffer = m_ball->getBall()->boundingRect().width();

    if (ballRight < m_bounds.left() - buffer) {
        m_scoreManager->addPoint(ScoreSide::Right, 1);
        m_waitingToRespawn = true;
        QTimer::singleShot(1000, [this]() {
            m_ball->spawnBall(m_size);
            m_waitingToRespawn = false;
        });
        return true;
    }

    if (ballLeft > m_bounds.right() + buffer) {
        m_scoreManager->addPoint(ScoreSide::Left, 1);
        m_waitingToRespawn = true;
        QTimer::singleShot(1000, [this]() {
            m_ball->spawnBall(m_size);
            m_waitingToRespawn = false;
        });
        return true;
    }
    return false;
}

void BallMovement::detectPlayer() {
    if (m_ball->getBall()->collidesWithItem(m_leftPlayer) || m_ball->getBall()->collidesWithItem(m_rightPlayer)) {
        m_direction.setX(-m_direction.x());
    }
}

void BallMovement::updateFrame() {
    connect(m_timer, &QTimer::timeout, this, &BallMovement::moveBall);
    m_timer->start(16);
}