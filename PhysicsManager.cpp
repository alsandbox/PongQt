#include "PhysicsManager.h"

#include <iostream>

#include "PlayerItem.h"
#include <qpoint.h>


PhysicsManager::PhysicsManager(){
    const b2WorldDef world = b2DefaultWorldDef();
    m_worldId = b2CreateWorld(&world);
}

void PhysicsManager::createBallShape(const QGraphicsEllipseItem* ball){
    const float radiusPixels = ball->rect().width() / 2.0f;
    const float radiusMeters = radiusPixels / m_pixelsPerMeter;

    b2Circle shape = b2Circle();
    shape.radius = radiusMeters;

    const QPointF posPixels = ball->pos();
    const b2Vec2 posMeters = {
        static_cast<float>(posPixels.x() / m_pixelsPerMeter),
        static_cast<float>(posPixels.y() / m_pixelsPerMeter)
    };

    b2BodyDef def = b2DefaultBodyDef();
    def.type = b2_dynamicBody;
    def.position = posMeters;

    const b2ShapeDef shapeDef = b2DefaultShapeDef();
    m_ballBodyId = b2CreateBody(m_worldId, &def);
    const b2ShapeId shapeId = b2CreateCircleShape(m_ballBodyId, &shapeDef, &shape);

    b2Shape_SetFriction(shapeId, 1.0f);
}

void PhysicsManager::destroyBall() {
    if (b2Body_IsValid(m_ballBodyId)) {
        b2DestroyBody(m_ballBodyId);
        m_ballBodyId = b2_nullBodyId;
    }
}

void PhysicsManager::createBoxShape(PlayerItem *player, bool isLeft) {
    const float halfWidthPixels = player->rect().width() / 2;
    const float halfHeightPixels = player->rect().height() / 2;

    const float halfWidthMeters = halfWidthPixels / m_pixelsPerMeter;
    const float halfHeightMeters = halfHeightPixels / m_pixelsPerMeter;

    const b2ShapeDef shapeDef = b2DefaultShapeDef();
    const b2Polygon boxShape = b2MakeBox(halfWidthMeters, halfHeightMeters);

    const QPointF posPixels = player->pos();
    const b2Vec2 posMeters = {
        static_cast<float>(posPixels.x() / m_pixelsPerMeter),
        static_cast<float>(posPixels.y() / m_pixelsPerMeter)
    };

    b2BodyDef def = b2DefaultBodyDef();
    def.type = b2_kinematicBody;
    def.position = posMeters;
    def.fixedRotation = true;

    const b2BodyId bodyId = b2CreateBody(m_worldId, &def);

    if (isLeft)
        m_leftPlayerBodyId = bodyId;
    else
        m_rightPlayerBodyId = bodyId;

    player->setBodyId(bodyId);
    const b2ShapeId shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &boxShape);
    b2Shape_SetFriction(shapeId, 1.0f);
}

void PhysicsManager::movePlayer(const b2BodyId bodyId, const float dy) {
    b2Vec2 position = b2Body_GetPosition(bodyId);
    const b2Rot rotation = b2Body_GetRotation(bodyId);
    position.y += dy;
    b2Body_SetTransform(bodyId, position, rotation);
}

void PhysicsManager::moveBall(const b2Vec2 velocity) const {
    b2Body_SetLinearVelocity(m_ballBodyId, velocity);
}

void PhysicsManager::reverseBallYDirection() const {
    b2Vec2 velocity = b2Body_GetLinearVelocity(m_ballBodyId);
    velocity.y = -velocity.y;
    b2Body_SetLinearVelocity(m_ballBodyId, velocity);
}

void PhysicsManager::resetBallPosition(const QPointF& pos) const {
    const b2Vec2 b2pos = {
        static_cast<float>(pos.x() / m_pixelsPerMeter),
        static_cast<float>(pos.y() / m_pixelsPerMeter)
    };
    b2Body_SetTransform(m_ballBodyId, b2pos, b2Body_GetRotation(m_ballBodyId));
}

void PhysicsManager::step(const b2BodyId bodyId, QGraphicsItem *item) const {
    if (!b2Body_IsValid(bodyId)) {
        std::cerr << "Error: Invalid body ID in PhysicsManager::step()\n";
        return;
    }

    constexpr int subStepCount = 4;
    constexpr float timeStep = 1.0f / 60.0f;
    b2World_Step(m_worldId, timeStep, subStepCount);

    auto [x, y] = b2Body_GetPosition(bodyId);
    item->setPos(x * m_pixelsPerMeter, y * m_pixelsPerMeter);
}

PhysicsManager::~PhysicsManager() {
    b2DestroyWorld(m_worldId);
}
