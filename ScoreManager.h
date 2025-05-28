#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H
#include "ScoreRenderer.h"


class ScoreManager {
    public:
    explicit ScoreManager(const std::shared_ptr<ScoreRenderer> &scoreRenderer);
    void addPoint(ScoreSide side, int score);

private:
    std::shared_ptr<ScoreRenderer> m_scoreRenderer;
    int m_scoreLeft{};
    int m_scoreRight{};
    const int m_maxScore = 11;
};



#endif //SCOREMANAGER_H
