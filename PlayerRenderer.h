#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include "GameManager.h"

class PlayerRenderer {
public:
    PlayerRenderer(QGraphicsScene *scene, const std::shared_ptr<GameManager> &gameManager);
    void resizeEvent(QResizeEvent* event);
    void displayPlayer(PlayerItem* player, bool isLeft) const;

private:
    std::unique_ptr<PlayerItem> rightPlayer = nullptr;
    std::unique_ptr<PlayerItem> leftPlayer = nullptr;
    bool leftPlayerAdded = false;
    bool rightPlayerAdded = false;
    std::shared_ptr<GameManager> m_gameManager = nullptr;
    QGraphicsScene* m_scene = nullptr;
    const double margin = 10;
};



#endif //PLAYERRENDERER_H
