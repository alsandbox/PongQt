#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include <memory>
#include "../renderers/BallRenderer.h"
#include "../renderers/IBoundable.h"
#include "PlayerItem.h"
#include "../managers/ScoreManager.h"
#include "../managers/GameManager.h"

class BallMovement final : public QObject, public IBoundable {
    Q_OBJECT
public:
    BallMovement(BallRenderer* ballRenderer,
                 const std::shared_ptr<ScoreManager> &scoreManager,
                 GameManager* gameManager);
    void resizeEvent(const QResizeEvent *event, float scaleRatio);
    void showEvent(QShowEvent *event);
    void setUpDirection();
    void moveBall(qint64 deltaMs);
    void setBounds(const QRectF &bounds) override;
    void setPositionFromRenderer(const QPointF &pos);

private:
    void detectPlayer(const std::shared_ptr<PlayerItem> &player);
    bool handleOutOfBounds(qreal ballLeft, qreal ballRight);
    void scheduleRespawn();
    QVector2D setNewAngle();
    bool handleBounds();
    void handlePlayerCollision();
    void calculateDirectionVectors();
    void calculateDirectionVelocity();
    bool setPositionAfterResize(const QResizeEvent *event);

    GameManager* m_gameManager = nullptr;
    BallRenderer* m_ball = nullptr;
    std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;

    QRectF m_bounds{};

    QVector2D m_direction{};
    QVector2D m_velocity{};
    QList<QVector2D> m_directionsRight{};
    QList<QVector2D> m_directionsLeft{};

    QGraphicsRectItem *m_ballItem = nullptr;

    bool m_waitingToRespawn = false;
    bool m_collidingWithLeft = false;
    bool m_collidingWithRight = false;

    float m_baseSpeed = 300.0;
    float m_speed{};
    int m_index{};
    int m_maxRandomBound = 2;
    QPointF m_position{};
    QPointF m_relativePos{};
};

#endif // BALLMOVEMENT_H
