#ifndef RENDERER_H
#define RENDERER_H

#include "../BallMovement.h"
#include "../managers/ScoreManager.h"
#include "BallRenderer.h"
#include "../screens/GameOverScreen.h"
#include "../screens/GameStartScreen.h"
#include "LineRenderer.h"
#include "../PlayerItem.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

class Renderer final : public QGraphicsView {
    Q_OBJECT
public:
    Renderer(QGraphicsScene *scene, GameManager* gameManager,
             LineRenderer* lineRenderer,
             const std::shared_ptr<PlayerRenderer> &playerRenderer,
             const std::shared_ptr<ScoreRenderer> &scoreRenderer,
             BallRenderer* ballRenderer,
             const std::shared_ptr<ScoreManager> &scoreManager,
             BallMovement* ballMovement,
             GameOverScreen* gameOverScreen,
             GameStartScreen* gameStartScreen,
             QWidget *parent);
    void resizeEvent(QResizeEvent *event) override;
    void showEvent(QShowEvent* event) override;
    static std::shared_ptr<QGraphicsRectItem> createGameZone();
    void updateGameZoneRect(qreal x, qreal y, qreal width, qreal height) const;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void handleResizeFinished();

public slots:
    void onStartGame() const;

private:
    std::shared_ptr<QGraphicsRectItem> m_gameZone;
    GameManager* m_gameManager = nullptr;
    LineRenderer* m_lineRenderer = nullptr;
    std::shared_ptr<PlayerRenderer> m_playerRenderer;
    std::shared_ptr<ScoreRenderer> m_scoreRenderer;
    BallRenderer* m_ballRenderer = nullptr;
    BallMovement* m_ballMovement = nullptr;
    std::shared_ptr<ScoreManager> m_scoreManager;
    GameOverScreen* m_gameOverScreen = nullptr;
    GameStartScreen* m_gameStartScreen = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer;
    std::shared_ptr<PlayerItem> m_leftPlayer;

    QTimer m_resizeTimer;
    bool m_gamePaused = false;
};

#endif // RENDERER_H