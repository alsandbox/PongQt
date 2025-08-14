#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#include "GameManager.h"
#include "../renderers/ScoreRenderer.h"


class ScoreManager {
    public:
    ScoreManager(const std::shared_ptr<ScoreRenderer> &scoreRenderer, GameManager* gameManager);
    void addPoint(ScoreSide side, int score);
    void resetScore();

private:
    std::shared_ptr<ScoreRenderer> m_scoreRenderer;
    GameManager* m_gameManager;
    int m_scoreLeft{};
    int m_scoreRight{};
    const int m_maxScore = 11;
};



#endif //SCOREMANAGER_H
