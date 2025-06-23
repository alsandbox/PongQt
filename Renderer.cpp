#include "Renderer.h"

#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

Renderer::Renderer(QGraphicsScene *scene, const std::shared_ptr<GameManager> &gameManager,
                   const std::shared_ptr<LineRenderer> &lineRenderer,
                   const std::shared_ptr<PlayerRenderer> &playerRenderer,
                   const std::shared_ptr<ScoreRenderer> &scoreRenderer,
                   const std::shared_ptr<BallRenderer> &ballRenderer,
                   const std::shared_ptr<ScoreManager> &scoreManager, const std::shared_ptr<BallMovement> &ballMovement,
                   QWidget *parent) : QGraphicsView(scene, parent), m_gameManager(gameManager),
                                      m_lineRenderer(lineRenderer),
                                      m_playerRenderer(playerRenderer), m_scoreRenderer(scoreRenderer),
                                      m_ballRenderer(ballRenderer),
                                      m_ballMovement(ballMovement), m_scoreManager(scoreManager) {
    setScene(scene);
    setBackgroundBrush(Qt::black);
    setRenderHint(QPainter::Antialiasing);
    setResizeAnchor(AnchorViewCenter);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    m_gameZone = createGameZone();
    scene->addItem(m_gameZone.get());
    m_rightPlayer = m_gameManager->getRightPlayer();
    m_leftPlayer = m_gameManager->getLeftPlayer();
}

void Renderer::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);

    const QRectF rect(QPointF(0, 0), QSizeF(size()));
    scene()->setSceneRect(rect);
    fitInView(rect, Qt::IgnoreAspectRatio);

    constexpr double totalParts = 6.0;
    const double margin = rect.width() / totalParts;
    constexpr double gameZoneWidthRatio = 4.0;
    updateGameZoneRect(rect.x() + margin, rect.y(), margin * gameZoneWidthRatio, rect.height());

    if (m_lineRenderer) {
        m_lineRenderer->resizeEvent(event, rect);
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
    if (m_ballRenderer) {
        m_ballRenderer->resizeEvent(event);
    }

    m_gameManager ? void() : throw std::runtime_error("GameManager is null");

    const QSize size = event->size();
    const QSize oldSize = event->oldSize();
    const float scaleRatio = m_gameManager->changeSpeedAfterResize(size, oldSize);

    if (m_ballMovement) {
        m_ballMovement->setBounds(rect);

        if (scaleRatio != 1.0f)
            m_ballMovement->resizeEvent(event, scaleRatio);
    }

    constexpr float defaultScaleRatio = 1.0f;
    if (m_leftPlayer) {
        constexpr int doubleHeight = 2;
        const qreal allowedOut = m_leftPlayer->boundingRect().height() * doubleHeight;
        const QRectF extendedBounds = rect.adjusted(0, -allowedOut, 0, allowedOut);

        m_leftPlayer->setBounds(extendedBounds);
        if (scaleRatio != defaultScaleRatio)
            m_leftPlayer->resizeEvent(event, scaleRatio);
    }

    if (m_rightPlayer) {
        const qreal allowedOut = m_rightPlayer->boundingRect().height();
        const QRectF extendedBounds = rect.adjusted(0, -allowedOut, 0, allowedOut);

        m_rightPlayer->setBounds(extendedBounds);
        if (scaleRatio != defaultScaleRatio)
            m_rightPlayer->resizeEvent(event, scaleRatio);
    }
}

void Renderer::showEvent(QShowEvent *event) {
    if (m_ballMovement)
        m_ballMovement->showEvent(event);

    if (m_gameManager && m_leftPlayer && m_rightPlayer) {
        m_gameManager->updateFrame([this]() {
            m_ballMovement->moveBall();
            m_leftPlayer->movePlayer();
            m_rightPlayer->movePlayer();
        });
    }

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
    QGraphicsView::keyPressEvent(event);
    m_gameManager->keyPressEvent(event);
}

void Renderer::keyReleaseEvent(QKeyEvent *event) {
    QGraphicsView::keyReleaseEvent(event);
    m_gameManager->keyReleaseEvent(event);
}
