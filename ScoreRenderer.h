#ifndef SCORERENDERER_H
#define SCORERENDERER_H

#include <QGraphicsTextItem>
#include <QResizeEvent>
#include <qfont.h>

#include "IBoundable.h"

enum class ScoreSide { Left, Right };

struct ScoreItem {
    std::unique_ptr<QGraphicsTextItem> item;
    double scale;
    bool added = false;
};

class ScoreRenderer : public IBoundable {
    public:
    explicit ScoreRenderer(QGraphicsScene *scene);
    void updateText(ScoreSide side, const QString& text) const;
    void resizeEvent(QResizeEvent* event);
    void setMargin(double margin);
    void setBounds(const QRectF& bounds) override;
    void displayScore(ScoreSide side, const ScoreItem &score);

private:
    ScoreItem m_leftScoreItem { nullptr, 0.20 };
    ScoreItem m_rightScoreItem { nullptr, 0.75 };
    QGraphicsScene* m_scene = nullptr;
    QFont m_font;
    double m_margin{};
    QRectF m_bounds{};
};



#endif //SCORERENDERER_H
