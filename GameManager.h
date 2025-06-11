#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QGraphicsView>

#include "BallMovement.h"
#include "PlayerItem.h"


class GameManager : public QGraphicsView {
public:
    explicit GameManager(QGraphicsScene *scene);

    void showEvent(QShowEvent *event) override;

    std::shared_ptr<PlayerItem> getLeftPlayer(){ return m_leftPlayer; }
    std::shared_ptr<PlayerItem>  getRightPlayer(){ return m_rightPlayer; }
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

private:
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    std::shared_ptr<BallMovement> m_ballMovement;
};



#endif //GAMEMANAGER_H
