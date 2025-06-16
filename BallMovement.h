#ifndef BALLMOVEMENT_H
#define BALLMOVEMENT_H

#include <QObject>
#include <memory>
#include "BallRenderer.h"
#include "IBoundable.h"
#include "PlayerItem.h"
#include "ScoreManager.h"


class BallMovement : public QObject, public IBoundable {
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
    QVector2D setNewAngle();
    void calculateDirectionVectors();

    std::shared_ptr<GameManager> m_gameManager = nullptr;
    std::shared_ptr<BallRenderer> m_ball = nullptr;
    std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    QRectF m_bounds{};
    QVector2D m_direction;
    qreal m_speed;
    QTimer* m_timer = nullptr;
    QSize m_size;
    QVector2D m_velocity;
    QList<QVector2D> m_directionsRight;
    QList<QVector2D> m_directionsLeft;
    bool m_waitingToRespawn = false;
};



#endif //BALLMOVEMENT_H
