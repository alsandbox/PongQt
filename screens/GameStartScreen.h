#ifndef GAMESTARTSCREEN_H
#define GAMESTARTSCREEN_H
#include "ScreenBase.h"
#include <QGraphicsProxyWidget>

class GameStartScreen : public ScreenBase {
    Q_OBJECT
public:
    explicit GameStartScreen(QGraphicsScene *scene);

    void addBackground();
    void addButtons() override;
    void updateLayout(const QSize &size) override;
    void removeElements() override;
    void showEvent(QShowEvent* event) override;

private:
    void onStartButtonPressed();

    QGraphicsRectItem *m_background = nullptr;
    QGraphicsProxyWidget *m_startProxyButton = nullptr;
    QPushButton *m_startButton = nullptr;
};


#endif //GAMESTARTSCREEN_H
