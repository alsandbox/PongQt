#include "ScoreRenderer.h"
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

ScoreRenderer::ScoreRenderer(QGraphicsScene* scene)
    : m_scene(scene) {
    leftScore = std::make_unique<QGraphicsTextItem>("0");
    rightScore = std::make_unique<QGraphicsTextItem>("0");
}

void ScoreRenderer::resizeEvent(QResizeEvent* event) {
    if (leftScore && !leftScoreAdded) {
        m_scene->addItem(leftScore.get());
        leftScoreAdded = true;
    }
    if (rightScore && !rightScoreAdded) {
        m_scene->addItem(rightScore.get());
        rightScoreAdded = true;
    }
    displayScore(leftScore.get(), 0.20);
    displayScore(rightScore.get(), 0.75);
}

void ScoreRenderer::displayScore(QGraphicsTextItem* score, const double scale) const {
    if (!score) return;
    score->setDefaultTextColor(Qt::white);

    const int id = QFontDatabase::addApplicationFont("../fonts/bit5x3.ttf");
    const QString family = QFontDatabase::applicationFontFamilies(id).at(0);

    QFont font(family);
    font.setPointSizeF(m_scene->sceneRect().height() / 10.0);
    score->setFont(font);

    const QRectF rect = m_scene->sceneRect();
    score->setPos(rect.width() * scale, rect.height() * 0.05);
}
