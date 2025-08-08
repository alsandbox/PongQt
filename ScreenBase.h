#ifndef SCREENBASE_H
#define SCREENBASE_H
#include <QGraphicsView>
#include <QPushButton>


class ScreenBase : public QGraphicsView  {
public:
    explicit ScreenBase(QGraphicsScene *scene);
    virtual void addButtons() = 0;
    virtual void removeElements() = 0;

protected:
    void createSpecifiedButton(QPushButton *&pushButton, QGraphicsProxyWidget *&button, const QString &title) const;
    void createExitButton();
    static void onExitButtonPressed();

    QGraphicsScene *m_scene = nullptr;
    QGraphicsProxyWidget *m_exitProxyButton = nullptr;
    QPushButton *m_exitButton = nullptr;
    QString m_style;

    double m_width = 120;
    double m_height = 30;
    int m_pointSize = 14;
    double m_pointToPixels = m_pointSize * (96 / 72);
    double m_half = 2.0;
    QFont m_customFont;
};



#endif //SCREENBASE_H
