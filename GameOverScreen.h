#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include "BallRenderer.h"
#include "LineRenderer.h"
#include "ScreenBase.h"


class GameOverScreen final : public ScreenBase {
public:
    GameOverScreen(QGraphicsScene *scene, const std::shared_ptr<LineRenderer> &lineRenderer,
                   const std::shared_ptr<BallRenderer> &ballRenderer);

    void removeElements() const;
    void addButtons() override;

private:
    static void onRestartButtonPressed();

    QGraphicsScene *m_scene = nullptr;
    std::shared_ptr<LineRenderer> m_lineRenderer = nullptr;
    std::shared_ptr<BallRenderer> m_ballRenderer = nullptr;
    QGraphicsProxyWidget *m_restartPushButton = nullptr;
    QPushButton *m_restartButton = nullptr;
    QString m_style;
};


#endif //GAMEOVERSCREEN_H
