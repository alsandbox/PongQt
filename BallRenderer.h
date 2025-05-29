#ifndef BALLRENDERER_H
#define BALLRENDERER_H
#include <QGraphicsScene>

#include "IBoundable.h"
#include "LineRenderer.h"

class BallRenderer : public QObject, public QGraphicsEllipseItem, public IBoundable {
    Q_OBJECT
public:
    explicit BallRenderer(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer);
    void spawnBall(QSize newSize);
    void resizeEvent(const QResizeEvent* event);
    void displayBall(QSize newSize) const;
    void setBounds(const QRectF& bounds) override;
    [[nodiscard]] QGraphicsEllipseItem* getBall() const {
        return ball.get();
    }

private:
    QGraphicsScene* m_scene = nullptr;
    std::shared_ptr<LineRenderer> m_line = nullptr;
    std::unique_ptr<QGraphicsEllipseItem> ball  = nullptr;
    QRectF m_bounds{};
    QRectF m_lineBounds{};
    QSize newSize{};
    int m_buffer = 50;
};



#endif //BALLRENDERER_H
