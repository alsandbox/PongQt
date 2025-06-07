#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H
#include <box2d/box2d.h>

#include "QGraphicsEllipseItem"

class PlayerItem;

class PhysicsManager {
public:
    PhysicsManager();
    ~PhysicsManager();
    void createBallShape(const QGraphicsEllipseItem* ball);
    void destroyBall();
    void createBoxShape(PlayerItem *player, bool isLeft);

    static void movePlayer(b2BodyId bodyId, float dy);
    void moveBall(b2Vec2 velocity) const;
    void resetBallPosition(const QPointF& pos) const;
    void reverseBallYDirection() const;
    void step(b2BodyId bodyId, QGraphicsItem *item) const;
    b2BodyId getBallId() const {return m_ballBodyId;}

private:
    b2WorldId m_worldId{};
    b2BodyId m_ballBodyId{};
    b2BodyId m_leftPlayerBodyId{};
    b2BodyId m_rightPlayerBodyId{};
    const float m_pixelsPerMeter = 100.0f;
};



#endif //PHYSICSMANAGER_H
