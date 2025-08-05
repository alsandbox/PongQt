#include "RendererFactory.h"

#include "GameOverScreen.h"

std::shared_ptr<Renderer> RendererFactory::createRenderer(QGraphicsScene* scene, QWidget* parent) {
    auto lineRenderer = std::make_shared<LineRenderer>(scene);
    auto ballRenderer = std::make_shared<BallRenderer>(scene, lineRenderer);
    auto gameOverScreen = std::make_shared<GameOverScreen>(scene, lineRenderer, ballRenderer);
    auto gameManager = std::make_shared<GameManager>(scene, gameOverScreen);
    auto scoreRenderer = std::make_shared<ScoreRenderer>(scene);
    auto playerRenderer = std::make_shared<PlayerRenderer>(scene, gameManager);
    auto scoreManager = std::make_shared<ScoreManager>(scoreRenderer, gameManager);
    auto ballMovement = std::make_shared<BallMovement>(ballRenderer, scoreManager, gameManager);

    return std::make_shared<Renderer>(scene, gameManager, lineRenderer, playerRenderer, scoreRenderer, ballRenderer, scoreManager, ballMovement,gameOverScreen, parent);
}
