#ifndef BALLRENDERER_H
#define BALLRENDERER_H
#include <QGraphicsScene>
#include <QResizeEvent>

class BallRenderer {
public:
    explicit BallRenderer(QGraphicsScene *scene);
    void resizeEvent(const QResizeEvent* event) const;
    void displayBall(QSize newSize) const;

    private:
    QGraphicsScene* m_scene = nullptr;
    std::unique_ptr<QGraphicsEllipseItem> ball  = nullptr;
};



#endif //BALLRENDERER_H
