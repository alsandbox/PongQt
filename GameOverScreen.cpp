#include "GameOverScreen.h"
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QPushButton>

GameOverScreen::GameOverScreen(QGraphicsScene *scene, LineRenderer* lineRenderer,
                              BallRenderer* ballRenderer) : ScreenBase(scene),
    m_lineRenderer(lineRenderer),
    m_ballRenderer(ballRenderer) {
}

void GameOverScreen::removeElements() {
    m_lineRenderer->eraseLine();
    m_ballRenderer->eraseBall();
}

void GameOverScreen::addButtons()  {
    if (!m_restartPushButton) {
        createSpecifiedButton(m_restartButton, m_restartPushButton, "Restart");
    }
    createExitButton();

    connect(m_restartButton, &QPushButton::pressed, this, &GameOverScreen::onRestartButtonPressed);
    connect(m_exitButton, &QPushButton::pressed, this, &GameOverScreen::onExitButtonPressed);
}

void GameOverScreen::onRestartButtonPressed() {

}
