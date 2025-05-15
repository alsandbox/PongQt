#ifndef PLAYERITEM_H
#define PLAYERITEM_H
#include <QGraphicsRectItem>


class PlayerItem : public QGraphicsRectItem {
public:
    PlayerItem(Qt::Key upKey, Qt::Key downKey, QGraphicsScene *scene);
    void setBounds(const QRectF& bounds);
    void keyPressEvent(QKeyEvent* event) override;


private:
    Qt::Key m_upKey;
    Qt::Key m_downKey;
    QGraphicsScene* m_scene = nullptr;
    QRectF m_bounds;
};




#endif //PLAYERITEM_H
