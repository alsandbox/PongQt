#include <QTimer>
#include "BallMovement.h"
#include <cmath>
#include <qcoreapplication.h>

#include "ScoreManager.h"


BallMovement::BallMovement(const std::shared_ptr<BallRenderer> &ballRenderer,
                 const std::shared_ptr<ScoreManager> &scoreManager,
                 const std::shared_ptr<GameManager> &gameManager)
    : m_gameManager(gameManager), m_ball(ballRenderer), m_scoreManager(scoreManager){
    calculateDirectionVectors();

    m_rightPlayer = m_gameManager->getRightPlayer();
    m_leftPlayer = m_gameManager->getLeftPlayer();
    m_direction = m_direction.normalized();
    m_velocity = {m_direction.x() * m_speed, m_direction.y() * m_speed};
    m_timer = new QTimer(this);
}

void BallMovement::calculateDirectionVectors() {
    const std::vector<double> angleListRight = {240, 225, 180, 120, 135};
    const std::vector<double> angleListLeft = {300, 315,0,60, 45};

    for (int i = 0; i < angleListRight.size(); ++i) {
        const double rad1 = qDegreesToRadians(angleListRight[i]);
        QVector2D dir1(qCos(rad1), qSin(rad1));
        m_directionsRight.append(dir1.normalized());
    }

    for (int i = 0; i < angleListLeft.size(); ++i) {
        const double rad1 = qDegreesToRadians(angleListLeft[i]);
        QVector2D dir1(qCos(rad1), qSin(rad1));
        m_directionsLeft.append(dir1.normalized());
    }
}
void BallMovement::resizeEvent(const QResizeEvent *event) {
    m_size = event->size();
    if ((m_size.width() > event->oldSize().width() || m_size.width() < event->oldSize().width())
        && (event->oldSize().width() > 0 && m_size.width() > 0)) {
        const float scaleRatio = static_cast<float>(m_size.width()) / event->oldSize().width();
        m_speed *= scaleRatio;
    }
}

void BallMovement::setBounds(const QRectF& bounds) {
void BallMovement::showEvent(QShowEvent *event) {
    updateFrame();
}
    m_bounds = bounds;
}

QVector2D BallMovement::setNewAngle() {
    m_index = QRandomGenerator::global()->bounded(m_directionsRight.size());
    return m_directionsRight[m_index];
}

void BallMovement::moveBall() {
    const QPointF velocity = m_direction.toPointF() * m_speed;

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

bool BallMovement::handleOutOfBounds(const qreal ballLeft, const qreal ballRight) {
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
    const qreal playerSpeed = addPlayerSpeed();
    if (m_ball->getBall()->collidesWithItem(m_leftPlayer) || m_ball->getBall()->collidesWithItem(m_rightPlayer)) {
        constexpr qreal factor = 0.3;
        m_direction.setX(-m_direction.x());
        m_direction.setY(m_direction.y() + playerSpeed * factor);
        m_direction = m_direction.normalized();
    }
}

    }


void BallMovement::updateFrame() {
    connect(m_timer, &QTimer::timeout, this, &BallMovement::moveBall);
    m_timer->start(16);
}