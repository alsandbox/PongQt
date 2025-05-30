#ifndef SCORERENDERER_H
#define SCORERENDERER_H

#include <qfont.h>
#include <QGraphicsTextItem>
#include <QResizeEvent>

enum class ScoreSide { Left, Right };

struct ScoreItem {
    std::unique_ptr<QGraphicsTextItem> item;
    double scale;
    bool added = false;
};

class ScoreRenderer {
    public:
    explicit ScoreRenderer(QGraphicsScene *scene);
    void updateText(ScoreSide side, const QString& text) const;
    void resizeEvent(QResizeEvent* event);
    void displayScore(const ScoreItem& score);

private:
    ScoreItem leftScoreItem { nullptr, 0.20 };
    ScoreItem rightScoreItem { nullptr, 0.75 };
    QGraphicsScene* m_scene = nullptr;
    QFont m_font;
};



#endif //SCORERENDERER_H
