#include "BallMovement.h"

#include <QCoreApplication>
#include <QDebug>
#include <QPointer>
#include <QRandomGenerator>
#include <QtMath>

#include "managers/ScoreManager.h"


BallMovement::BallMovement(BallRenderer* ballRenderer,
                 const std::shared_ptr<ScoreManager> &scoreManager,
                 GameManager* gameManager)
    : m_gameManager(gameManager), m_ball(ballRenderer), m_scoreManager(scoreManager){
    calculateDirectionVectors();
    m_speed = m_baseSpeed;
    m_rightPlayer = m_gameManager->getRightPlayer();
    m_leftPlayer = m_gameManager->getLeftPlayer();

    m_direction = setNewAngle();
    if (QRandomGenerator::global()->bounded(m_maxRandomBound))
        m_direction.setY(-m_direction.y());
    m_direction = m_direction.normalized();
    m_velocity = {m_direction.x() * m_speed, m_direction.y() * m_speed};
}

void BallMovement::calculateDirectionVectors() {
    const std::vector<float> angleListRight = {240, 225, 180, 120, 135};
    const std::vector<float> angleListLeft = {300, 315, 0, 60, 45};

    for (int i = 0; i < angleListRight.size(); ++i) {
        const float rad1 = qDegreesToRadians(angleListRight[i]);
        QVector2D dir1(qCos(rad1), qSin(rad1));
        m_directionsRight.append(dir1.normalized());
    }

    for (int i = 0; i < angleListLeft.size(); ++i) {
        const float rad1 = qDegreesToRadians(angleListLeft[i]);
        QVector2D dir1(qCos(rad1), qSin(rad1));
        m_directionsLeft.append(dir1.normalized());
    }
}

void BallMovement::resizeEvent(const QResizeEvent *event, const float scaleRatio) {
    m_speed = m_baseSpeed * scaleRatio;
}

void BallMovement::showEvent(QShowEvent *event) {
    m_ballItem = m_ball->getBall();
    m_leftPlayer->setPlayerPartitions();
    m_rightPlayer->setPlayerPartitions();

    m_direction = setNewAngle();
    if (QRandomGenerator::global()->bounded(m_maxRandomBound))
        m_direction.setY(-m_direction.y());

    calculateDirectionVelocity();
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

    const bool collidesLeft = m_ballItem->collidesWithItem(m_leftPlayer.get());
    const bool collidesRight = m_ballItem->collidesWithItem(m_rightPlayer.get());

    if (collidesLeft && !m_collidingWithLeft) {
        detectPlayer(m_leftPlayer);
        m_collidingWithLeft = true;
    } else if (!collidesLeft) {
        m_collidingWithLeft = false;
    }

    if (collidesRight && !m_collidingWithRight) {
        detectPlayer(m_rightPlayer);
        m_collidingWithRight = true;
    } else if (!collidesRight) {
        m_collidingWithRight = false;
    }

    m_ballItem->setPos(newPos);
}

bool BallMovement::handleOutOfBounds(const qreal ballLeft, const qreal ballRight) {
    if (m_waitingToRespawn) return true;

    const qreal buffer = m_ballItem->boundingRect().width();

    if (ballRight < m_bounds.left() - buffer) {
        m_scoreManager->addPoint(ScoreSide::Right, 1);

        if (!m_gameManager->getGameOver()) {
            m_waitingToRespawn = true;
            scheduleRespawn();
        }

        return true;
    }

    if (ballLeft > m_bounds.right() + buffer) {
        m_scoreManager->addPoint(ScoreSide::Left, 1);

        if (!m_gameManager->getGameOver()) {
            m_waitingToRespawn = true;
            scheduleRespawn();
        }

        return true;
    }

    return false;
}

void BallMovement::scheduleRespawn() {
    QPointer self(this);
    constexpr int interval = 1000;

    QTimer::singleShot(interval, [self, this] {
        if (!self) return;
        self->m_ball->spawnBall();

        m_direction = setNewAngle();
        if (QRandomGenerator::global()->bounded(m_maxRandomBound))
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

void BallMovement::detectPlayer(const std::shared_ptr<PlayerItem> &player) {
    const QRectF ballRect = m_ballItem->sceneBoundingRect();
    const QRectF playerRect = player->sceneBoundingRect();
    const QRectF intersection = ballRect.intersected(playerRect);
    const QPointF collisionPointInScene = intersection.center();
    const QPointF collisionPointInPlayer = player->mapFromScene(collisionPointInScene);

    const auto &parts = player->getPartitions();

    m_index = -1;
    constexpr int offset = 1;
    const double y = collisionPointInPlayer.y();
    for (int i = 0; i < parts.size() - offset; ++i) {
        if (y >= parts[i] && y <= parts[i + offset]) {
            m_index = i;
            break;
        }
    }

    constexpr int invalidIndex = -1;
    if (m_index == invalidIndex && y >= parts.back()) {
        constexpr int indexOffset = 2;
        m_index = parts.size() - indexOffset;
    }
    if (m_index >= 0 && m_index < m_directionsRight.size()) {
        if (player == m_leftPlayer) {
            m_direction = m_directionsLeft[m_index];
        }
        else {
            m_direction = m_directionsRight[m_index];
        }
         m_velocity = {m_direction.x() * m_speed, m_direction.y() * m_speed};
    }
}
