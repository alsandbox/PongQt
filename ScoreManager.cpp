#include "ScoreManager.h"

ScoreManager::ScoreManager(const std::shared_ptr<ScoreRenderer> &scoreRenderer) : m_scoreRenderer(scoreRenderer) {}

void ScoreManager::addPoint(const ScoreSide side, const int score) {
    int& targetScore = side == ScoreSide::Left ? m_scoreLeft : m_scoreRight;

    if (targetScore < m_maxScore)
        targetScore += score;
    if (targetScore > m_maxScore)
        targetScore = m_maxScore;

    m_scoreRenderer->updateText(side, QString::number(targetScore));
}
