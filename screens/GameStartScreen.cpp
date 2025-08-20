#include "GameStartScreen.h"

#include "../font/FontConfig.h"

GameStartScreen::GameStartScreen(QGraphicsScene *scene)
    : ScreenBase(scene) {
}

void GameStartScreen::addBackground() {
    const QRectF sceneRect = m_scene->sceneRect();
    constexpr qreal margin = 20;
    const QRectF expandedRect(sceneRect.left() - margin, sceneRect.top() - margin,
                              sceneRect.width() + m_half * margin, sceneRect.height() + m_half * margin);

    if (!m_background) {
        m_background = m_scene->addRect(expandedRect, QPen(Qt::NoPen), QBrush(Qt::black));
        m_background->setZValue(100);
    } else {
        m_background->setRect(expandedRect);
    }
}

void GameStartScreen::addButtons() {
    ScreenBase::addButtons();
    addBackground();
    if (!m_startProxyButton) {
        createSpecifiedButton(m_startButton, m_startProxyButton, "Start");
        m_buttons.append(m_startButton);
        m_proxyButtons.append(m_startProxyButton);
        m_layout->addItem(m_startProxyButton);
        connect(m_startButton, &QPushButton::pressed, this, &GameStartScreen::onStartButtonPressed);
    }

    createExitButton();
    if (m_exitProxyButton) {
        m_buttons.append(m_exitButton);
        m_proxyButtons.append(m_exitProxyButton);
        m_layout->addItem(m_exitProxyButton);
        connect(m_exitButton, &QPushButton::pressed, this, &GameStartScreen::onExitButtonPressed);
    }

    m_layout->setAlignment(m_startProxyButton, Qt::AlignHCenter);
    m_layout->setAlignment(m_exitProxyButton, Qt::AlignHCenter);
    m_buttonContainer->adjustSize();
}

void GameStartScreen::updateLayout(const QSize &size) {
    ScreenBase::updateLayout(size);
    if (m_background) {
        m_background->setRect(m_scene->sceneRect());
    } else {
        addBackground();
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
    updateLayout(m_scene->sceneRect().size().toSize());
}

void GameStartScreen::onStartButtonPressed() {
    removeElements();
    emit startButtonPressed();

}
