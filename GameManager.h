#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QGraphicsView>
#include <QTimer>

#include "GameOverScreen.h"
#include "PlayerItem.h"

class GameManager : public QGraphicsView {
public:
    explicit GameManager(QGraphicsScene *scene, const std::shared_ptr<GameOverScreen> &gameOverScreen);
    std::shared_ptr<PlayerItem> getLeftPlayer(){ return m_leftPlayer; }
    std::shared_ptr<PlayerItem>  getRightPlayer(){ return m_rightPlayer; }
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    [[nodiscard]] QTimer* getTimer() const { return m_timer.get(); }
    float changeSpeedAfterResize(const QSize &size);

    void setGameOver(const bool gameOver){ isGameOver = gameOver;};
    bool getGameOver(){ return isGameOver; }

public slots:
    void updateFrame(std::function<void(qint64)> updateFunc);
    void stopFrame();

private:
    std::shared_ptr<GameOverScreen> m_gameOverScreen = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    std::unique_ptr<QTimer> m_timer = nullptr;
    qint64 m_lastUpdate = 0;
    std::function<void(qint64)> m_updateFunc;
    bool m_isInitSize = false;
    int m_initialWidth = 0;
    bool isGameOver = false;
};


#endif //GAMEMANAGER_H
