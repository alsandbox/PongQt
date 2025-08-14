#include "RendererFactory.h"

#include "../screens/GameOverScreen.h"
#include "../screens/GameStartScreen.h"

Renderer *RendererFactory::createRenderer(QGraphicsScene *scene, QWidget *parent) {
    const auto gameStartScreen = new GameStartScreen(scene);
    const auto lineRenderer = new LineRenderer(scene);
    const auto ballRenderer = new BallRenderer(scene, lineRenderer);
    const auto gameOverScreen = new GameOverScreen(scene, lineRenderer, ballRenderer);

    auto gameManager = new GameManager(scene, gameOverScreen);
    auto scoreRenderer = std::make_shared<ScoreRenderer>(scene);
    const auto playerRenderer = std::make_shared<PlayerRenderer>(scene, gameManager);
    const auto scoreManager = std::make_shared<ScoreManager>(scoreRenderer, gameManager);
    const auto ballMovement = new BallMovement(ballRenderer, scoreManager, gameManager);

    const auto renderer = new Renderer(scene, gameManager, lineRenderer, playerRenderer,
                                       scoreRenderer, ballRenderer, scoreManager,
                                       ballMovement, gameOverScreen, gameStartScreen, parent);

    QObject::connect(gameStartScreen, &GameStartScreen::startButtonPressed,
                     renderer, &Renderer::onStartGame);

    return renderer;
}
