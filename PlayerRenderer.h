#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include <QGraphicsView>
#include "Renderer.h"

class Renderer;

class PlayerRenderer {
public:
    PlayerRenderer(QGraphicsScene *scene, Renderer* renderer, const std::shared_ptr<PhysicsManager>& physicsManager);
    void resizeEvent(QResizeEvent* event);
    void displayPlayer(PlayerItem* player, bool isLeft) const;

private:
    std::unique_ptr<PlayerItem> rightPlayer = nullptr;
    std::unique_ptr<PlayerItem> leftPlayer = nullptr;
    bool leftPlayerAdded = false;
    bool rightPlayerAdded = false;
    QGraphicsScene* m_scene = nullptr;
    const double margin = 10;
    std::shared_ptr<PhysicsManager> m_physicsManager = nullptr;
};



#endif //PLAYERRENDERER_H
