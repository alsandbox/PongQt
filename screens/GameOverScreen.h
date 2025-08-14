#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include "../renderers/BallRenderer.h"
#include "../renderers/LineRenderer.h"
#include "ScreenBase.h"


class GameOverScreen final : public ScreenBase {
    Q_OBJECT

public:
    GameOverScreen(QGraphicsScene *scene, LineRenderer *lineRenderer, BallRenderer *ballRenderer);

    void removeElements() override;
    void addButtons() override;
    void updateLayout(const QSize &size) override;

private:
    void onRestartButtonPressed();

    LineRenderer *m_lineRenderer = nullptr;
    BallRenderer *m_ballRenderer = nullptr;
    QGraphicsProxyWidget *m_restartProxyButton = nullptr;
    QPushButton *m_restartButton = nullptr;
};


#endif //GAMEOVERSCREEN_H
