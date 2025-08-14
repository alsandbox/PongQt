#include "ScoreRenderer.h"

#include <qfontmetrics.h>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include "../fonts/FontConfig.h"

ScoreRenderer::ScoreRenderer(QGraphicsScene* scene)
    : m_scene(scene) {
    m_leftScoreItem.item = std::make_unique<QGraphicsTextItem>();
    m_rightScoreItem.item = std::make_unique<QGraphicsTextItem>();

    m_scene->addItem(m_leftScoreItem.item.get());
    m_scene->addItem(m_rightScoreItem.item.get());
    m_leftScoreItem.added = true;
    m_rightScoreItem.added = true;

    updateText(ScoreSide::Left, "0");
    updateText(ScoreSide::Right, "0");
}

void ScoreRenderer::updateText(const ScoreSide side, const QString& text) const {
    auto& score = side == ScoreSide::Left ? m_leftScoreItem : m_rightScoreItem;
    if (score.item) score.item->setPlainText(text);
}

void ScoreRenderer::resizeEvent(QResizeEvent* event) const {
    displayScore(ScoreSide::Left, m_leftScoreItem);
    displayScore(ScoreSide::Right, m_rightScoreItem);
}

void ScoreRenderer::setMargin(const double margin) {
    m_margin = margin;
}

void ScoreRenderer::setBounds(const QRectF &bounds) {
    m_bounds = bounds;
}

void ScoreRenderer::displayScore(const ScoreSide side, const ScoreItem& score) const {
    if (!score.item) return;
    score.item->setDefaultTextColor(Qt::white);

    FontConfig::init();
    QFont customFont = FontConfig::font;

    constexpr double scaleFactor = 10.0;
    customFont.setPointSize(m_scene->sceneRect().height() / scaleFactor);
    score.item->setFont(customFont);

    const QRectF rect = m_scene->sceneRect();
    auto& scoreSide = side;

    const QFontMetricsF metrics(FontConfig::font);
    const qreal textWidth = metrics.boundingRect(score.item->toPlainText()).width();

    if (scoreSide == ScoreSide::Left) {
        score.item->setPos(m_bounds.center().x() - m_margin, rect.height() * 0.05);
    } else {
        score.item->setPos(m_bounds.center().x() + m_margin - textWidth, rect.height() * 0.05);
    }
}
