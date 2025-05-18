#ifndef RENDERER_H
#define RENDERER_H

#include "BallMovement.h"
#include "BallRenderer.h"
#include "PlayerItem.h"
#include "PlayerRenderer.h"
#include "ScoreRenderer.h"

class PlayerRenderer;

class Renderer : public QGraphicsView {
    Q_OBJECT
public:
    explicit Renderer(QGraphicsScene* scene, QWidget* parent = nullptr);
    void resizeEvent(QResizeEvent* event) override;
    void displayLine(const QRectF &rect);
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void setLeftPlayer(PlayerItem* player);
    void setRightPlayer(PlayerItem* player);

private:
    QGraphicsLineItem* lineItem = nullptr;

    std::unique_ptr<PlayerRenderer> playerRenderer;
    std::unique_ptr<ScoreRenderer> scoreRenderer;
    std::shared_ptr<BallRenderer> ballRenderer;
    std::unique_ptr<BallMovement> ballMovement;

    PlayerItem* leftPlayer = nullptr;
    PlayerItem* rightPlayer = nullptr;
};




#endif //RENDERER_H
