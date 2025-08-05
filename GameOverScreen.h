#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include <QGraphicsView>
#include <QPushButton>
#include "BallRenderer.h"
#include "LineRenderer.h"


class GameOverScreen : public QGraphicsView {
public:
    GameOverScreen(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer,
                   const std::shared_ptr<BallRenderer> &ballRenderer);
    void removeElements();
    void addRestartButton();

private:
    std::shared_ptr<LineRenderer> m_lineRenderer;
    std::shared_ptr<BallRenderer> m_ballRenderer;
    QGraphicsProxyWidget *m_pushButton;
    QGraphicsScene *m_scene;
    QPushButton* button;
    QString style;
};


#endif //GAMEOVERSCREEN_H
