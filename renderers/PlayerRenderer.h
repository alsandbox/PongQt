#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include "../managers/GameManager.h"

class PlayerRenderer final : public IBoundable {
public:
    PlayerRenderer(QGraphicsScene *scene, GameManager* gameManager);
    void resizeEvent(QResizeEvent* event);
    void setBounds(const QRectF& bounds) override;
    void displayPlayer(PlayerItem* player, bool isLeft) const;

private:
    GameManager* m_gameManager = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    bool m_leftPlayerAdded = false;
    bool m_rightPlayerAdded = false;
    QGraphicsScene* m_scene = nullptr;
    QRectF m_bounds{};
};



#endif //PLAYERRENDERER_H
