#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include "GameManager.h"

class PlayerRenderer {
public:
    PlayerRenderer(QGraphicsScene *scene, const std::shared_ptr<GameManager> &gameManager);
    void resizeEvent(QResizeEvent* event);
    void displayPlayer(PlayerItem* player, bool isLeft) const;

private:
    std::shared_ptr<GameManager> m_gameManager = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    bool m_leftPlayerAdded = false;
    bool m_rightPlayerAdded = false;
    QGraphicsScene* m_scene = nullptr;
    const double margin = 10;
};



#endif //PLAYERRENDERER_H
