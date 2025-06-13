#include "RendererFactory.h"

std::shared_ptr<Renderer> RendererFactory::createRenderer(QGraphicsScene* scene, QWidget* parent) {
    auto gameManager = std::make_shared<GameManager>(scene);
    auto lineRenderer = std::make_shared<LineRenderer>(scene);
    auto scoreRenderer = std::make_shared<ScoreRenderer>(scene);
    auto playerRenderer = std::make_shared<PlayerRenderer>(scene, gameManager);
    auto ballRenderer = std::make_shared<BallRenderer>(scene, lineRenderer);
    auto scoreManager = std::make_shared<ScoreManager>(scoreRenderer);
    auto ballMovement = std::make_shared<BallMovement>(ballRenderer, scoreManager, gameManager);

    return std::make_shared<Renderer>(scene, gameManager, lineRenderer, playerRenderer, scoreRenderer, ballRenderer, scoreManager, ballMovement, parent);
}