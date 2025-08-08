#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include "BallRenderer.h"
#include "LineRenderer.h"
#include "ScreenBase.h"


class GameOverScreen final : public ScreenBase {
public:
    GameOverScreen(QGraphicsScene *scene, LineRenderer *lineRenderer, BallRenderer *ballRenderer);

    void removeElements() override;
    void addButtons() override;

private:
    static void onRestartButtonPressed();

    LineRenderer *m_lineRenderer = nullptr;
    BallRenderer *m_ballRenderer = nullptr;
    QGraphicsProxyWidget *m_restartPushButton = nullptr;
    QPushButton *m_restartButton = nullptr;
};


#endif //GAMEOVERSCREEN_H
