#ifndef PLAYERITEM_H
#define PLAYERITEM_H
#include <QGraphicsRectItem>

#include "IBoundable.h"


class PlayerItem final : public QGraphicsRectItem, public IBoundable {
public:
    PlayerItem(Qt::Key upKey, Qt::Key downKey, QGraphicsScene *scene);
    void setBounds(const QRectF& bounds) override;
    void keyPressEvent(QKeyEvent* event) override;
    [[nodiscard]] const std::vector<double>& getPartitions() const {
        return m_playerPartitions;
    }
    void setPlayerPartitions();
private:
    Qt::Key m_upKey;
    Qt::Key m_downKey;
    QGraphicsScene* m_scene = nullptr;
    QRectF m_bounds;
    int m_moveStep = 3;
    float m_speed = 10.0f;
    std::vector<double> m_playerPartitions;
};




#endif //PLAYERITEM_H
