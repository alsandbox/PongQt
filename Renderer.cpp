#include "Renderer.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

Renderer::Renderer(QGraphicsScene* scene, QWidget* parent)
    : QGraphicsView(scene, parent) {
    setScene(scene);
    setBackgroundBrush(Qt::black);
    setRenderHint(QPainter::Antialiasing);
    setResizeAnchor(AnchorViewCenter);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);

    m_lineRenderer = std::make_shared<LineRenderer>(scene);
    m_physicsManager = std::make_shared<PhysicsManager>();
    m_playerRenderer = std::make_unique<PlayerRenderer>(scene, this, m_physicsManager);
    m_scoreRenderer = std::make_shared<ScoreRenderer>(scene);
    m_ballRenderer = std::make_shared<BallRenderer>(scene, m_lineRenderer, m_physicsManager);
    m_scoreManager = std::make_shared<ScoreManager>(m_scoreRenderer);
    m_ballMovement = std::make_shared<BallMovement>(m_ballRenderer, m_scoreManager, m_physicsManager, m_leftPlayer, m_rightPlayer);
}

void Renderer::resizeEvent(QResizeEvent* event) {
    QGraphicsView::resizeEvent(event);

    const QRectF rect(QPointF(0, 0), QSizeF(size()));
    scene()->setSceneRect(rect);

    if (m_lineRenderer)
        m_lineRenderer->resizeEvent(event, rect);
    if (m_playerRenderer)
        m_playerRenderer->resizeEvent(event);
    if (m_scoreRenderer)
        m_scoreRenderer->resizeEvent(event);
    if (m_ballRenderer)
        m_ballRenderer->resizeEvent(event);
    if (m_ballMovement) {
        m_ballMovement->resizeEvent(event);
        m_ballMovement->setBounds(rect);
    }

    fitInView(rect, Qt::IgnoreAspectRatio);

    if (m_leftPlayer){
        qreal allowedOut = m_leftPlayer->boundingRect().height();
        QRectF extendedBounds = rect.adjusted(-allowedOut, -allowedOut, allowedOut, allowedOut);
        m_leftPlayer->setBounds(extendedBounds);
    }
    if (m_rightPlayer) {
        qreal allowedOut = m_rightPlayer->boundingRect().height();
        QRectF extendedBounds = rect.adjusted(-allowedOut, -allowedOut, allowedOut, allowedOut);
        m_rightPlayer->setBounds(extendedBounds);
    }

}

void Renderer::keyPressEvent(QKeyEvent* event) {
    if (m_leftPlayer)
        m_leftPlayer->keyPressEvent(event);
    if (m_rightPlayer)
        m_rightPlayer->keyPressEvent(event);
}

void Renderer::keyReleaseEvent(QKeyEvent* event) {
    QGraphicsView::keyReleaseEvent(event);
}

void Renderer::setLeftPlayer(PlayerItem* player) {
    m_leftPlayer = player;
}

void Renderer::setRightPlayer(PlayerItem* player) {
    m_rightPlayer = player;
}
