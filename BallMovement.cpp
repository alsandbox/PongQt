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

void BallMovement::updateFrame() {
    if (!m_timer->isActive()) {
        connect(m_timer, &QTimer::timeout, this, &BallMovement::moveBall);
        constexpr int frameIntervalMs = 16;
        m_timer->start(frameIntervalMs);
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

void BallMovement::showEvent(QShowEvent *event) {
    m_ballItem = m_ball->getBall();
    m_leftPlayer->setPlayerPartitions();
    m_rightPlayer->setPlayerPartitions();

    m_direction = setNewAngle();
    if (QRandomGenerator::global()->bounded(2))
        m_direction.setY(-m_direction.y());

    calculateDirectionVelocity();
    updateFrame();
}

void BallMovement::setBounds(const QRectF &bounds) {
    m_bounds = bounds;
}

QVector2D BallMovement::setNewAngle() {
    m_index = QRandomGenerator::global()->bounded(m_directionsRight.size());
    return m_directionsRight[m_index];
}

void BallMovement::moveBall() {
    const QPointF velocity = m_direction.toPointF() * m_speed;

    m_ballItem = m_ball->getBall();

    const QPointF newPos = m_ballItem->pos() + velocity;

    const QRectF ballBounds = m_ballItem->boundingRect().translated(newPos);

    if (ballBounds.bottom() > m_bounds.bottom() || ballBounds.top() <= 0) {
        m_direction.setY(-m_direction.y());
    }

    if (handleOutOfBounds(ballBounds.left(), ballBounds.right())) {
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

void BallMovement::scheduleRespawn() {
    QPointer self(this);
    constexpr int interval = 1000;

    QTimer::singleShot(interval, [self, this] {
        if (!self) return;
        self->m_ball->spawnBall(self->m_size);

        m_direction = setNewAngle();
        if (QRandomGenerator::global()->bounded(2))
            m_direction.setY(-m_direction.y());

        calculateDirectionVelocity();
        moveBall();
        self->m_waitingToRespawn = false;
    });
}

void BallMovement::calculateDirectionVelocity() {
    m_velocity = {m_direction.x() * m_speed, m_direction.y() * m_speed};
    m_direction.normalize();
}

    }

}