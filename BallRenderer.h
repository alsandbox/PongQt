#ifndef BALLRENDERER_H
#define BALLRENDERER_H
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QResizeEvent>

#include "IBoundable.h"

class BallRenderer : public QObject, public QGraphicsEllipseItem, public IBoundable {
    Q_OBJECT
public:
    explicit BallRenderer(QGraphicsScene *scene);
    void resizeEvent(const QResizeEvent* event) const;
    void displayBall(QSize newSize) const;
    void setBounds(const QRectF& bounds) override;
    [[nodiscard]] QGraphicsEllipseItem* getBall() const {
        return ball.get();
    }

private:
    QGraphicsScene* m_scene = nullptr;
    std::unique_ptr<QGraphicsEllipseItem> ball  = nullptr;
    QRectF m_bounds{};
};



#endif //BALLRENDERER_H
