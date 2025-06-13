#ifndef RENDERER_H
#define RENDERER_H

#include "BallMovement.h"
#include "BallRenderer.h"
#include "LineRenderer.h"
#include "PlayerItem.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

class Renderer final : public QGraphicsView {
    Q_OBJECT
public:
    explicit Renderer(QGraphicsScene *scene, const std::shared_ptr<GameManager> &gameManager,
                      const std::shared_ptr<LineRenderer> &lineRenderer,
                      const std::shared_ptr<PlayerRenderer> &playerRenderer,
                      const std::shared_ptr<ScoreRenderer> &scoreRenderer,
                      const std::shared_ptr<BallRenderer> &ballRenderer,
                      const std::shared_ptr<ScoreManager> &scoreManager,
                      const std::shared_ptr<BallMovement> &ballMovement, QWidget *parent);
    void resizeEvent(QResizeEvent *event) override;
    [[nodiscard]] double getMargin() const { return m_margin; };
    void showEvent(QShowEvent* event) override;
    static std::shared_ptr<QGraphicsRectItem> createGameZone();
    void updateGameZoneRect(qreal x, qreal y, qreal width, qreal height) const;

private:
    std::shared_ptr<QGraphicsRectItem> m_gameZone = nullptr;
    std::shared_ptr<GameManager> m_gameManager = nullptr;
    std::shared_ptr<LineRenderer> m_lineRenderer = nullptr;
    std::shared_ptr<PlayerRenderer> m_playerRenderer = nullptr;
    std::shared_ptr<ScoreRenderer> m_scoreRenderer = nullptr;
    std::shared_ptr<BallRenderer> m_ballRenderer = nullptr;
    std::shared_ptr<BallMovement> m_ballMovement = nullptr;
    std::shared_ptr<ScoreManager> m_scoreManager = nullptr;

    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
};

#endif // RENDERER_H