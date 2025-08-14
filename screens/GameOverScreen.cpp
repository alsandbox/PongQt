#include "GameOverScreen.h"
#include <QGraphicsProxyWidget>
#include <QPushButton>

GameOverScreen::GameOverScreen(QGraphicsScene *scene, LineRenderer* lineRenderer,
                              BallRenderer* ballRenderer) : ScreenBase(scene),
    m_lineRenderer(lineRenderer),
    m_ballRenderer(ballRenderer) {
}

void GameOverScreen::removeElements() {
    m_lineRenderer->setVisible(false);
    m_ballRenderer->setVisible(false);
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
    else {
        m_restartProxyButton->show();
    }

    if (!m_exitProxyButton) {
        createExitButton();

        m_buttons.append(m_exitButton);
        m_proxyButtons.append(m_exitProxyButton);
        m_layout->addItem(m_exitProxyButton);
        connect(m_exitButton, &QPushButton::pressed, this, &GameOverScreen::onExitButtonPressed);
    }
    else {
        m_exitProxyButton->show();
    }

    m_layout->setAlignment(m_restartProxyButton, Qt::AlignHCenter);
    m_layout->setAlignment(m_exitProxyButton, Qt::AlignHCenter);
    m_buttonContainer->adjustSize();

    updateLayout(m_scene->sceneRect().size().toSize());
}

void GameOverScreen::onRestartButtonPressed() {
    m_lineRenderer->setVisible(true);
    m_ballRenderer->setVisible(true);

    m_restartProxyButton->hide();
    m_exitProxyButton->hide();
    emit startButtonPressed();
}

void GameOverScreen::updateLayout(const QSize &size) {
    ScreenBase::updateLayout(size);
}
