#ifndef SCORERENDERER_H
#define SCORERENDERER_H

#include <QGraphicsTextItem>
#include <QResizeEvent>


class ScoreRenderer {
    public:
    explicit ScoreRenderer(QGraphicsScene *scene);
    void updateText(const QString& newText) const {
        //rightScore->setPlainText(newText);
    }
    void resizeEvent(QResizeEvent* event);
    void displayScore(QGraphicsTextItem* score, const double scale) const;

private:
    std::unique_ptr<QGraphicsTextItem> rightScore = nullptr;
    std::unique_ptr<QGraphicsTextItem> leftScore = nullptr;
    bool leftScoreAdded = false;
    bool rightScoreAdded = false;
    QGraphicsScene* m_scene = nullptr;
};



#endif //SCORERENDERER_H
