#ifndef RENDERER_H
#define RENDERER_H

#include "BallMovement.h"
#include "BallRenderer.h"
#include "LineRenderer.h"
#include "PhysicsManager.h"
#include "PlayerItem.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

class PlayerRenderer;

class Renderer final : public QGraphicsView {
    Q_OBJECT
public:
    explicit Renderer(QGraphicsScene* scene, QWidget* parent = nullptr);
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void setLeftPlayer(PlayerItem* player);
    void setRightPlayer(PlayerItem* player);

private:
    std::shared_ptr<LineRenderer> m_lineRenderer;
    std::unique_ptr<PlayerRenderer> m_playerRenderer;
    std::shared_ptr<ScoreRenderer> m_scoreRenderer;
    std::shared_ptr<BallRenderer> m_ballRenderer;
    std::shared_ptr<BallMovement> m_ballMovement;
    std::shared_ptr<ScoreManager> m_scoreManager;
    PlayerItem* m_leftPlayer = nullptr;
    PlayerItem* m_rightPlayer = nullptr;
    std::shared_ptr<PhysicsManager> m_physicsManager = nullptr;
};

#endif // RENDERER_H