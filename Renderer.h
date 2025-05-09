#ifndef RENDERER_H
#define RENDERER_H

#include <QGraphicsTextItem>

#include "BallRenderer.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"


class Renderer : public QGraphicsView {
    Q_OBJECT
public:
    explicit Renderer(QGraphicsScene* scene, QWidget* parent = nullptr);
    void resizeEvent(QResizeEvent* event) override;
    void displayLine(const QRectF &rect);

private:
    QGraphicsLineItem* lineItem = nullptr;

    std::unique_ptr<PlayerRenderer> playerRenderer;
    std::unique_ptr<ScoreRenderer> scoreRenderer;
    std::unique_ptr<BallRenderer> ballRenderer;
};




#endif //RENDERER_H
