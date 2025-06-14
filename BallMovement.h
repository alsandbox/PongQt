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
    BallMovement(const std::shared_ptr<BallRenderer> &ball, const std::shared_ptr<ScoreManager> &scoreManager, const PlayerItem *leftPlayer,
                 const PlayerItem *rightPlayer);
    void resizeEvent(const QResizeEvent* event);
    void showEvent(QShowEvent *event);
    void moveBall();
    qreal addPlayerSpeed() const;
    void setBounds(const QRectF &bounds) override;

public slots:
    void updateFrame();

private:
    void detectPlayer(const std::shared_ptr<PlayerItem> &player);
    bool handleOutOfBounds(qreal ballLeft, qreal ballRight);
    std::shared_ptr<BallRenderer> m_ball = nullptr;
    std::shared_ptr<ScoreManager> m_scoreManager = nullptr;
    QRectF m_bounds{};
    QVector2D m_direction;
    qreal m_speed;
    QTimer* m_timer = nullptr;
    const PlayerItem* m_leftPlayer;
    const PlayerItem* m_rightPlayer;
    QSize m_size;
    bool m_waitingToRespawn = false;
};



#endif //BALLMOVEMENT_H
