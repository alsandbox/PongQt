#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include <QObject>
#include <QTimer>
#include <memory>
#include "BallRenderer.h"
#include "IBoundable.h"
#include "PlayerItem.h"
#include "ScoreManager.h"
#include "GameManager.h"

class BallMovement final : public QObject, public IBoundable {
    Q_OBJECT
public:
    BallMovement(const std::shared_ptr<BallRenderer> &ballRenderer,
                 const std::shared_ptr<ScoreManager> &scoreManager,
                 const std::shared_ptr<GameManager> &gameManager);
    void resizeEvent(const QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void moveBall();
    void setBounds(const QRectF &bounds) override;
    void calculateDirectionVelocity();

public slots:
    void updateFrame();

private:
    void detectPlayer(const std::shared_ptr<PlayerItem> &player);
    bool handleOutOfBounds(qreal ballLeft, qreal ballRight);
    void scheduleRespawn();
    QVector2D setNewAngle();
    void calculateDirectionVectors();

    std::shared_ptr<GameManager> m_gameManager = nullptr;
    std::shared_ptr<BallRenderer> m_ball = nullptr;
    std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;

    QRectF m_bounds{};
    QSize m_size{};

    QVector2D m_direction;
    QVector2D m_velocity;
    QList<QVector2D> m_directionsRight;
    QList<QVector2D> m_directionsLeft;

    QTimer *m_timer = nullptr;

    QGraphicsEllipseItem *m_ballItem = nullptr;

    bool m_waitingToRespawn = false;
    bool m_collidingWithLeft = false;
    bool m_collidingWithRight = false;

    float m_speed = 4.0;
    int m_index{};
};

#endif // BALLMOVEMENT_H
