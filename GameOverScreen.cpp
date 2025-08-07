#include "GameOverScreen.h"
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QWidget>

#include "fonts/FontConfig.h"

GameOverScreen::GameOverScreen(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer,
                               const std::shared_ptr<BallRenderer> &ballRenderer) : m_lineRenderer(lineRenderer),
                                                                                    m_ballRenderer(ballRenderer),
                                                                                    m_scene(scene){
}

void GameOverScreen::removeElements() const {
    m_lineRenderer->eraseLine();
    m_ballRenderer->eraseBall();
}

void GameOverScreen::addButtons()  {
    constexpr double width = 120;
    constexpr double height = 30;
    constexpr int pointSize = 14;
    constexpr double pointToPixels = pointSize * (96 / 72);
    constexpr double half = 2.0;
    FontConfig::init();
    QFont customFont = FontConfig::font;
    customFont.setPointSize(pointSize);

    if (!m_restartPushButton) {
        m_restartButton = new QPushButton("Restart");
        m_restartPushButton = m_scene->addWidget(m_restartButton);

        m_restartPushButton->setMinimumSize(width, height);
        m_restartPushButton->setPos(m_scene->sceneRect().width() / half - (width - pointToPixels) / half,
                                    m_scene->sceneRect().height() / half - height / half - pointToPixels * half);

        m_restartButton->setFont(customFont);
        m_restartButton->setStyleSheet(m_style);
    }

    if (!m_exitPushButton) {
        m_exitButton = new QPushButton("Exit");
        m_exitPushButton = m_scene->addWidget(m_exitButton);

        m_exitPushButton->setMinimumSize(width, height);
        m_exitPushButton->setPos(m_scene->sceneRect().width() / half - (width - pointToPixels) / half,
                                 m_scene->sceneRect().height() / half - height / half + pointToPixels);

        m_exitButton->setFont(customFont);
        m_exitButton->setStyleSheet(m_style);
    }

    connect(m_restartButton, &QPushButton::pressed, this, &GameOverScreen::onRestartButtonPressed);
    connect(m_exitButton, &QPushButton::pressed, this, &GameOverScreen::onExitButtonPressed);
}

void GameOverScreen::onRestartButtonPressed() {

}
