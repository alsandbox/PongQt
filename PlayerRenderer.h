#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include <QGraphicsView>
#include "Renderer.h"

class Renderer;

class PlayerRenderer {
public:
    explicit PlayerRenderer(QGraphicsScene *scene, Renderer* renderer);
    void resizeEvent(QResizeEvent* event);
    void displayPlayer(QGraphicsRectItem* player, bool isLeft) const;

private:
    std::unique_ptr<PlayerItem> rightPlayer = nullptr;
    std::unique_ptr<PlayerItem> leftPlayer = nullptr;
    bool leftPlayerAdded = false;
    bool rightPlayerAdded = false;
    QGraphicsScene* m_scene = nullptr;
    const double margin = 10;
};



#endif //PLAYERRENDERER_H
