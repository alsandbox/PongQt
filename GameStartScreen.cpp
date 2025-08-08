#include "GameStartScreen.h"
#include "fonts/FontConfig.h"

GameStartScreen::GameStartScreen(QGraphicsScene *scene)
    : ScreenBase(scene) {
}

void GameStartScreen::addButtons() {
    if (!m_background) {
        m_background = m_scene->addRect(
            m_scene->sceneRect(),
            QPen(Qt::NoPen),
            QBrush(Qt::black)
        );
        m_background->setZValue(100);
    }

    if (!m_startProxyButton) {
        createSpecifiedButton(m_startButton, m_startProxyButton, "Start");
        m_startProxyButton->setZValue(101);

        connect(m_startButton, &QPushButton::pressed,
                this, &GameStartScreen::onStartButtonPressed);
    }

    createExitButton();
    if (m_exitProxyButton) {
        m_exitProxyButton->setZValue(101);
        connect(m_exitButton, &QPushButton::pressed,
                this, &GameStartScreen::onExitButtonPressed);
    }
}

void GameStartScreen::removeElements() {
    if (m_startProxyButton) {
        m_startProxyButton->hide();
        m_startButton->hide();
    }

    if (m_exitProxyButton) {
        m_exitProxyButton->hide();
        m_exitButton->hide();
    }

    if (m_background) {
        m_background->hide();
    }
}

void GameStartScreen::showEvent(QShowEvent *event) {
    ScreenBase::showEvent(event);
    addButtons();
}

void GameStartScreen::onStartButtonPressed() {
    emit startButtonPressed();
    removeElements();
}
