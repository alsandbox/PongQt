#include "ScreenBase.h"

#include <qcoreapplication.h>
#include <QFile>
#include <QGraphicsProxyWidget>

#include "fonts/FontConfig.h"


ScreenBase::ScreenBase(QGraphicsScene *scene) : m_scene(scene) {
    QFile file("../style/button_style.qss");
    file.open(QFile::ReadOnly);
    m_style = QLatin1String(file.readAll());

    FontConfig::init();
    m_customFont = FontConfig::font;
    m_customFont.setPointSize(m_pointSize);
}

void ScreenBase::createSpecifiedButton(QPushButton *&pushButton, QGraphicsProxyWidget *&button, const QString &title) const {
    pushButton = new QPushButton(title);
    button = m_scene->addWidget(pushButton);

    button->setMinimumSize(m_width, m_height);
    button->setPos(m_scene->sceneRect().width() / m_half - (m_width - m_pointToPixels) / m_half,
                                m_scene->sceneRect().height() / m_half - m_height / m_half - m_pointToPixels * m_half);

    pushButton->setFont(m_customFont);
    pushButton->setStyleSheet(m_style);
}

void ScreenBase::createExitButton() {
    if (!m_exitProxyButton) {
        m_exitButton = new QPushButton("Exit");
        m_exitProxyButton = m_scene->addWidget(m_exitButton);

        m_exitProxyButton->setMinimumSize(m_width, m_height);
        m_exitProxyButton->setPos(m_scene->sceneRect().width() / m_half - (m_width - m_pointToPixels) / m_half,
                                 m_scene->sceneRect().height() / m_half - m_height / m_half + m_pointToPixels);

        m_exitButton->setFont(m_customFont);
        m_exitButton->setStyleSheet(m_style);
    }
}

void ScreenBase::onExitButtonPressed() {
    QCoreApplication::exit(0);
}
