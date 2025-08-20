#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <QTimer>

#include "../screens/GameOverScreen.h"
#include "../gameplay/PlayerItem.h"

class GameManager : public QGraphicsView {
public:
    explicit GameManager(QGraphicsScene *scene, GameOverScreen* gameOverScreen);
    std::shared_ptr<PlayerItem> getLeftPlayer(){ return m_leftPlayer; }
    std::shared_ptr<PlayerItem>  getRightPlayer(){ return m_rightPlayer; }
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    [[nodiscard]] QTimer* getTimer() const { return m_timer; }
    float changeSpeedAfterResize(const QSize &size);

    void setGameOver(const bool gameOver){ isGameOver = gameOver;}
    bool getGameOver() const { return isGameOver; }
    void setGameStart(const bool gameStart){ isGameStart = gameStart; }
    bool getGameStart() const { return isGameStart; }

public slots:
    void updateFrame(std::function<void(qint64)> updateFunc);
    void stopFrame();

private:
    GameOverScreen* m_gameOverScreen = nullptr;
    std::shared_ptr<PlayerItem> m_rightPlayer = nullptr;
    std::shared_ptr<PlayerItem> m_leftPlayer = nullptr;
    QTimer* m_timer = nullptr;
    qint64 m_lastUpdate = 0;
    std::function<void(qint64)> m_updateFunc;
    bool m_isInitSize = false;
    int m_initialWidth = 0;
    bool isGameOver = false;
    bool isGameStart = false;
};


#endif //GAMEMANAGER_H
