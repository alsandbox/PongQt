#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QGraphicsView>
#include <QTimer>

#include "PlayerItem.h"

class GameManager : public QGraphicsView {
public:
    explicit GameManager(QGraphicsScene *scene);
    std::shared_ptr<PlayerItem> getLeftPlayer(){ return m_leftPlayer; }
    std::shared_ptr<PlayerItem>  getRightPlayer(){ return m_rightPlayer; }
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    float changeSpeedAfterResize(const QSize &size, const QSize &oldSize);

public slots:
    void updateFrame(const std::function<void()> &func);

private:
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    QTimer *m_timer = nullptr;
    std::function<void()> m_updateFunc;
};


#endif //GAMEMANAGER_H
