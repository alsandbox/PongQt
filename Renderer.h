#ifndef RENDERER_H
#define RENDERER_H

#include "BallMovement.h"
#include "BallRenderer.h"
#include "LineRenderer.h"
#include "PlayerItem.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

class PlayerRenderer;

class Renderer final : public QGraphicsView {
    Q_OBJECT
public:
    explicit Renderer(QGraphicsScene *scene, QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent *event) override;
    [[nodiscard]] double getMargin() const { return m_margin; };

private:
    std::shared_ptr<GameManager> m_gameManager;
    std::shared_ptr<LineRenderer> m_lineRenderer;
    std::unique_ptr<PlayerRenderer> m_playerRenderer;
    std::shared_ptr<ScoreRenderer> m_scoreRenderer;
    std::shared_ptr<BallRenderer> m_ballRenderer;
    std::shared_ptr<BallMovement> m_ballMovement;
    std::shared_ptr<ScoreManager> m_scoreManager;
    PlayerItem* m_leftPlayer = nullptr;
    PlayerItem* m_rightPlayer = nullptr;
};

#endif // RENDERER_H