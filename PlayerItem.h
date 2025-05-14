#ifndef PLAYERITEM_H
#define PLAYERITEM_H
#include <QGraphicsRectItem>


class PlayerItem : public QGraphicsRectItem {
public:
    PlayerItem(Qt::Key upKey, Qt::Key downKey);

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    Qt::Key m_upKey, m_downKey;
};




#endif //PLAYERITEM_H
