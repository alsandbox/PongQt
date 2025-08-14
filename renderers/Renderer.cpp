#include "Renderer.h"

#include "PlayerRenderer.h"
#include "ScoreRenderer.h"


Renderer::Renderer(QGraphicsScene *scene, GameManager* gameManager,
             LineRenderer* lineRenderer,
             const std::shared_ptr<PlayerRenderer> &playerRenderer,
             const std::shared_ptr<ScoreRenderer> &scoreRenderer,
             BallRenderer* ballRenderer,
             const std::shared_ptr<ScoreManager> &scoreManager,
             BallMovement* ballMovement,
             GameOverScreen* gameOverScreen,
             GameStartScreen* gameStartScreen,
             QWidget *parent) : QGraphicsView(scene, parent), m_gameManager(gameManager),
                                      m_lineRenderer(lineRenderer),
                                      m_playerRenderer(playerRenderer), m_scoreRenderer(scoreRenderer),
                                      m_ballRenderer(ballRenderer),
                                      m_ballMovement(ballMovement), m_scoreManager(scoreManager),
                                      m_gameOverScreen(gameOverScreen), m_gameStartScreen(gameStartScreen) {
    setBackgroundBrush(Qt::black);
    setRenderHint(QPainter::Antialiasing);
    setResizeAnchor(AnchorViewCenter);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    setViewportUpdateMode(FullViewportUpdate);

    m_gameZone = createGameZone();
    scene->addItem(m_gameZone.get());

    m_rightPlayer = m_gameManager->getRightPlayer();
    m_leftPlayer = m_gameManager->getLeftPlayer();

    m_resizeTimer.setSingleShot(true);
    connect(&m_resizeTimer, &QTimer::timeout, this, &Renderer::handleResizeFinished);
}

void Renderer::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);

    m_gamePaused = true;
    m_resizeTimer.start(50);

    const QRectF rect(QPointF(0, 0), QSizeF(size()));
    scene()->setSceneRect(rect);
    fitInView(rect, Qt::IgnoreAspectRatio);

    constexpr double totalParts = 6.0;
    const double margin = rect.width() / totalParts;
    constexpr double gameZoneWidthRatio = 4.0;
    updateGameZoneRect(rect.x() + margin, rect.y(), margin * gameZoneWidthRatio, rect.height());

    m_gameStartScreen ? void() : throw std::runtime_error("Game Start Screen is null");
    m_gameStartScreen->updateLayout(event->size());

    m_gameOverScreen ? void() : throw std::runtime_error("Game Start Screen is null");
    m_gameOverScreen->updateLayout(event->size());


    if (m_lineRenderer && !m_gameManager->getGameOver()) {
        m_lineRenderer->displayLine(rect);
    }
    if (m_playerRenderer) {
        m_playerRenderer->setBounds(m_gameZone->sceneBoundingRect());
        m_playerRenderer->resizeEvent(event);
    }
    if (m_scoreRenderer) {
        m_scoreRenderer->setMargin(margin);
        m_scoreRenderer->setBounds(m_gameZone->sceneBoundingRect());
        m_scoreRenderer->resizeEvent(event);
    }
    if (m_ballRenderer && !m_gameManager->getGameOver()){
        m_ballRenderer->resizeEvent(event);
    }

    m_gameManager ? void() : throw std::runtime_error("GameManager is null");

    const QSize size = event->size();
    const float scaleRatio = m_gameManager->changeSpeedAfterResize(size);

    if (m_ballMovement) {
        m_ballMovement->setBounds(rect);
        m_ballMovement->resizeEvent(event, scaleRatio);
    }

    constexpr float defaultScaleRatio = 1.0f;
    constexpr int verticalMarginFactor = 2.0f;
    if (m_leftPlayer) {

        const qreal allowedOut = m_leftPlayer->boundingRect().height() * verticalMarginFactor;
        const QRectF extendedBounds = rect.adjusted(0, -allowedOut, 0, allowedOut);

        m_leftPlayer->setBounds(extendedBounds);
        if (scaleRatio != defaultScaleRatio)
            m_leftPlayer->resizeEvent(event, scaleRatio);
    }

    if (m_rightPlayer) {
        const qreal allowedOut = m_rightPlayer->boundingRect().height() * verticalMarginFactor;
        const QRectF extendedBounds = rect.adjusted(0, -allowedOut, 0, allowedOut);

        m_rightPlayer->setBounds(extendedBounds);
        if (scaleRatio != defaultScaleRatio)
            m_rightPlayer->resizeEvent(event, scaleRatio);
    }
}

void Renderer::handleResizeFinished() {
    m_gamePaused = false;
}

void Renderer::onStartGame() const {
    m_gameManager ? void() : throw std::runtime_error("GameManager is null");
    m_gameManager->setGameStart(true);

    if (m_leftPlayer && m_rightPlayer) {
        if (!m_gameManager->getTimer()->isActive()) {
                m_gameManager->updateFrame([this](const qint64 deltaMs) {
                if (m_gamePaused)
                    return;

                m_ballMovement->moveBall(deltaMs);
                m_leftPlayer->movePlayer(deltaMs);
                m_rightPlayer->movePlayer(deltaMs);
            });
        }
    }
}

void Renderer::showEvent(QShowEvent *event) {
    m_gameStartScreen ? void() : throw std::runtime_error("GameStartScreen is null");
    m_gameStartScreen->showEvent(event);

    if (m_ballMovement)
        m_ballMovement->showEvent(event);

    m_ballRenderer ? void() : throw std::runtime_error("BallRenderer is null");
    m_ballRenderer->showEvent(event);
}

std::shared_ptr<QGraphicsRectItem> Renderer::createGameZone() {
    constexpr int size = 1;
    auto gameZone = std::make_shared<QGraphicsRectItem>(QRectF(0, 0, size, size));
    gameZone->setPen(Qt::NoPen);
    gameZone->setBrush(Qt::NoBrush);

    return gameZone;
}

void Renderer::updateGameZoneRect(const qreal x, const qreal y, const qreal width, const qreal height) const {
    if (m_gameZone) {
        m_gameZone->setRect(QRectF(x, y, width, height));
    }
}

void Renderer::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        QApplication::quit();
        return;
    }
    QGraphicsView::keyPressEvent(event);
    m_gameManager->keyPressEvent(event);
}

void Renderer::keyReleaseEvent(QKeyEvent *event) {
    QGraphicsView::keyReleaseEvent(event);
    m_gameManager->keyReleaseEvent(event);
}