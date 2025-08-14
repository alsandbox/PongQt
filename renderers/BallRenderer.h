#ifndef BALLRENDERER_H
#define BALLRENDERER_H

#include "../IBoundable.h"
#include "LineRenderer.h"


class BallRenderer final : public QObject, public QGraphicsRectItem, public IBoundable {
    Q_OBJECT

public:
    explicit BallRenderer(QGraphicsScene *scene, LineRenderer* lineRenderer);
    void setBounds(const QRectF &bounds) override;
    void spawnBall() const;
    void resizeEvent(const QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void displayBall() const;

    void setVisible(bool visible) const;
    [[nodiscard]] QGraphicsRectItem *getBall() const {
        return ball.get();
    }

private:
    QGraphicsScene *m_scene = nullptr;
    LineRenderer* m_line = nullptr;
    std::unique_ptr<QGraphicsRectItem> ball;
    QRectF m_bounds{};
    QRectF m_lineBounds{};
    QSize m_size{};
    int m_buffer = 50;
};


#endif //BALLRENDERER_H
