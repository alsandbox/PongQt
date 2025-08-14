#include "ScreenBase.h"

#include <qcoreapplication.h>
#include <QFile>
#include <QGraphicsProxyWidget>

#include "../fonts/FontConfig.h"


ScreenBase::ScreenBase(QGraphicsScene *scene) : m_scene(scene) {
    QFile file("../style/button_style.qss");
    file.open(QFile::ReadOnly);
    m_style = QLatin1String(file.readAll());

    FontConfig::init();
    m_customFont = FontConfig::font;
}

void ScreenBase::addButtons() {
    if (!m_buttonContainer) {
        m_buttonContainer = new QGraphicsWidget();
        m_scene->addItem(m_buttonContainer);

        m_layout = new QGraphicsLinearLayout(Qt::Vertical);
        m_layout->setContentsMargins(0, 0, 0, 0);

        m_buttonContainer->setLayout(m_layout);
        m_layout->setAlignment(m_buttonContainer, Qt::AlignHCenter);
        m_buttonContainer->setZValue(1000);
    }
}

void ScreenBase::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
}

QSize ScreenBase::calculateButtonSize(const QString &text) {
    constexpr double fontScalingFactor = 15.0;
    m_customFont.setPointSize(m_scene->sceneRect().height() / fontScalingFactor);
    const QFontMetrics fm(m_customFont);

    constexpr int margin = 10;
    const int width = fm.horizontalAdvance(text) + margin * m_half;
    const int height = fm.height() + margin;

    return QSize(width, height);
}

void ScreenBase::createSpecifiedButton(QPushButton *&pushButton, QGraphicsProxyWidget *&button,
                                       const QString &title) const {
    pushButton = new QPushButton(title);
    pushButton->setFont(m_customFont);
    pushButton->setStyleSheet(m_style);
    button = m_scene->addWidget(pushButton);
}

void ScreenBase::createExitButton() {
    if (!m_exitProxyButton) {
        m_exitButton = new QPushButton("Exit");
        m_exitButton->setFont(m_customFont);
        m_exitButton->setStyleSheet(m_style);
        m_exitProxyButton = m_scene->addWidget(m_exitButton);
    }
}

void ScreenBase::updateButton(QPushButton *&pushButton, QGraphicsProxyWidget *&button) {
    if (pushButton && button) {
        const QSize size = calculateButtonSize(pushButton->text());

        button->resize(size);
        pushButton->setFixedSize(size);
        button->setPreferredSize(size);
        pushButton->setFont(m_customFont);
    }
}

void ScreenBase::onExitButtonPressed() {
    QCoreApplication::exit(0);
}

void ScreenBase::updateLayout(const QSize &size) {
    if (m_layout) m_layout->invalidate();

    for (int i = 0; i < m_buttons.size(); ++i) {
        updateButton(m_buttons[i], m_proxyButtons[i]);
    }
    if (m_buttonContainer && m_layout) {
        const QSizeF preferredSize = m_layout->effectiveSizeHint(Qt::PreferredSize);

        const int buttonHeight = m_buttons[0]->height();
        constexpr int buttonScalingFactor = 3;
        const int dynamicSpacing = buttonHeight / buttonScalingFactor;
        m_layout->setSpacing(dynamicSpacing);

        m_buttonContainer->setPreferredSize(preferredSize);
        m_layout->activate();
        m_buttonContainer->adjustSize();
        QRectF sceneRect = m_scene->sceneRect();
        m_buttonContainer->setPos(
            sceneRect.center().x() - preferredSize.width() / m_half,
            sceneRect.center().y() - preferredSize.height() / m_half
        );
    }
}
