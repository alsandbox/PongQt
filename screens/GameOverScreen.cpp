#include "GameOverScreen.h"
#include <QGraphicsProxyWidget>
#include <QPushButton>

GameOverScreen::GameOverScreen(QGraphicsScene *scene, LineRenderer* lineRenderer,
                              BallRenderer* ballRenderer) : ScreenBase(scene),
    m_lineRenderer(lineRenderer),
    m_ballRenderer(ballRenderer) {
}

void GameOverScreen::removeElements() {
    m_lineRenderer->hideLine();
    m_ballRenderer->hideBall();
}

void GameOverScreen::addButtons()  {
    ScreenBase::addButtons();

    if (!m_restartProxyButton) {
        createSpecifiedButton(m_restartButton, m_restartProxyButton, "Restart");
        m_buttons.append(m_restartButton);
        m_proxyButtons.append(m_restartProxyButton);
        m_layout->addItem(m_restartProxyButton);
        connect(m_restartButton, &QPushButton::pressed, this, &GameOverScreen::onRestartButtonPressed);
    }

    createExitButton();
    if (m_exitProxyButton) {
        m_buttons.append(m_exitButton);
        m_proxyButtons.append(m_exitProxyButton);
        m_layout->addItem(m_exitProxyButton);
        connect(m_exitButton, &QPushButton::pressed, this, &GameOverScreen::onExitButtonPressed);
    }

    m_layout->setAlignment(m_restartProxyButton, Qt::AlignHCenter);
    m_layout->setAlignment(m_exitProxyButton, Qt::AlignHCenter);
    m_buttonContainer->adjustSize();

    updateLayout(m_scene->sceneRect().size().toSize());
}

void GameOverScreen::onRestartButtonPressed() {

}

void GameOverScreen::updateLayout(const QSize &size) {
    ScreenBase::updateLayout(size);
}
