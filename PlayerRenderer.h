#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include <QGraphicsView>


class PlayerRenderer  {
public:
    explicit PlayerRenderer(QGraphicsScene *scene);
    void resizeEvent(QResizeEvent* event);
    void displayPlayer(QGraphicsRectItem* player, bool isLeft) const;

private:
    std::unique_ptr<QGraphicsRectItem> rightPlayer = nullptr;
    std::unique_ptr<QGraphicsRectItem> leftPlayer = nullptr;
    bool leftPlayerAdded = false;
    bool rightPlayerAdded = false;
    QGraphicsScene* m_scene;
    const double margin = 10;
};



#endif //PLAYERRENDERER_H
