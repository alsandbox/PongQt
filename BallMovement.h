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
    BallMovement(const std::shared_ptr<BallRenderer>& ball, QGraphicsScene *scene, const PlayerItem* leftPlayer, const PlayerItem*  rightPlayer);
    BallMovement(const std::shared_ptr<BallRenderer> &ball, const std::shared_ptr<ScoreManager> &scoreManager, const PlayerItem *leftPlayer,
                 const PlayerItem *rightPlayer);
    void moveBall();
    void setBounds(const QRectF& bounds) override;
    void detectPlayer();

public slots:
    void updateFrame();

private:
    std::shared_ptr<BallRenderer> m_ball  = nullptr;
    QGraphicsScene * m_scene;
    std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
    QRectF m_bounds{};
    QPointF m_direction;
    qreal m_speed;
    QTimer* m_timer = nullptr;
    const PlayerItem* m_leftPlayer;
    const PlayerItem* m_rightPlayer;
};



#endif //BALLMOVEMENT_H
