#ifndef SCREENBASE_H
#define SCREENBASE_H
#include <QGraphicsView>
#include <QPushButton>


class ScreenBase : public QGraphicsView  {
public:
    ScreenBase();
    virtual void addButtons() = 0;

protected:
    static void onExitButtonPressed();

    QGraphicsProxyWidget *m_exitPushButton = nullptr;
    QPushButton *m_exitButton = nullptr;
    QString m_style;
};



#endif //SCREENBASE_H
