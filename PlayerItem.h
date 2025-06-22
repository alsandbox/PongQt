#ifndef PLAYERITEM_H
#define PLAYERITEM_H

#include <QGraphicsRectItem>
#include <qset.h>

#include "IBoundable.h"


class PlayerItem final : public QGraphicsRectItem, public IBoundable {
public:
    PlayerItem(Qt::Key upKey, Qt::Key downKey, QGraphicsScene *scene);
    void setBounds(const QRectF& bounds) override;
    void keyPressEvent(QKeyEvent* event) override;
    void movePlayer();
    [[nodiscard]] const std::vector<double>& getPartitions() const {
        return m_playerPartitions;
    }
    void setPlayerPartitions();
private:
    Qt::Key m_upKey;
    Qt::Key m_downKey;
    QGraphicsScene* m_scene = nullptr;
    QRectF m_bounds;
    float m_moveStep = 2;
    float m_speed = 20.0f;
    std::vector<double> m_playerPartitions;
    QSet<int> keysPressed;
};




#endif //PLAYERITEM_H
