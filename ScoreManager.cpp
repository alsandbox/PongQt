#include "ScoreManager.h"


ScoreManager::ScoreManager(const std::shared_ptr<ScoreRenderer> &scoreRenderer,
                           const std::shared_ptr<GameManager> &gameManager) : m_scoreRenderer(scoreRenderer),
                                                                              m_gameManager(gameManager) {
}

void ScoreManager::addPoint(const ScoreSide side, const int score) {
    int& targetScore = side == ScoreSide::Left ? m_scoreLeft : m_scoreRight;

    if (targetScore < m_maxScore)
        targetScore += score;

    if (targetScore == m_maxScore) {
        m_gameManager->stopFrame();
    }

    m_scoreRenderer->updateText(side, QString::number(targetScore));
}
