#ifndef GAMESTARTSCREEN_H
#define GAMESTARTSCREEN_H
#include "ScreenBase.h"
#include <QGraphicsProxyWidget>

class GameStartScreen : public ScreenBase {
    Q_OBJECT
public:
    explicit GameStartScreen(QGraphicsScene *scene);
    void addButtons() override;
    void removeElements() override;
    void showEvent(QShowEvent* event) override;

    signals:
        void startButtonPressed();

private:
    void onStartButtonPressed();

    QGraphicsRectItem *m_background = nullptr;
    QGraphicsProxyWidget *m_startProxyButton = nullptr;
    QPushButton *m_startButton = nullptr;
};


#endif //GAMESTARTSCREEN_H
