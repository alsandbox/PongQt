#include "GameOverScreen.h"
#include <QFile>
#include <QGraphicsProxyWidget>
#include <QPushButton>
#include <QWidget>

#include "fonts/FontConfig.h"

GameOverScreen::GameOverScreen(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer,
                               const std::shared_ptr<BallRenderer> &ballRenderer) : m_lineRenderer(lineRenderer),
                                                                                    m_ballRenderer(ballRenderer), m_scene(scene) {
    QFile file("../button_style.qss");
    file.open(QFile::ReadOnly);
    style = QLatin1String(file.readAll());
}


void GameOverScreen::removeElements()  {
    m_lineRenderer->eraseLine();
    m_ballRenderer->eraseBall();
    addRestartButton();
}

void GameOverScreen::addRestartButton()  {
    if (!m_pushButton) {
        button = new QPushButton("Restart");
        m_pushButton = m_scene->addWidget(button);
        m_pushButton->setMinimumSize(120, 30);
        m_pushButton->setPos(m_scene->sceneRect().width() / 2.0 - 25, m_scene->sceneRect().height() / 2.0 - 25);

        FontConfig::init();
        QFont customFont = FontConfig::font;
        customFont.setPointSize(14);
        button->setFont(customFont);
        button->setStyleSheet(style);
    }
}
