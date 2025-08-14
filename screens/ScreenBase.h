#ifndef SCREENBASE_H
#define SCREENBASE_H
#include <QGraphicsLinearLayout>
#include <QGraphicsView>
#include <QPushButton>


class ScreenBase : public QGraphicsView {
    Q_OBJECT
public:
    explicit ScreenBase(QGraphicsScene *scene);
    virtual void removeElements() = 0;
    void resizeEvent(QResizeEvent *event) override;
    void updateButton(QPushButton *&pushButton, QGraphicsProxyWidget *&button);

    signals:
    void startButtonPressed();

protected:
    void createSpecifiedButton(QPushButton *&pushButton, QGraphicsProxyWidget *&button, const QString &title) const;
    void createExitButton();
    virtual void addButtons();
    QSize calculateButtonSize(const QString &text);
    static void onExitButtonPressed();
    static double m_pointToPixels(const int pointSize) { return pointSize * (96 / 72); }
    virtual void updateLayout(const QSize &size);

    QList<QPushButton *> m_buttons;
    QList<QGraphicsProxyWidget *> m_proxyButtons;
    QGraphicsWidget *m_buttonContainer = nullptr;
    QGraphicsLinearLayout *m_layout = nullptr;
    QGraphicsRectItem *m_background = nullptr;
    QGraphicsScene *m_scene = nullptr;
    QGraphicsProxyWidget *m_exitProxyButton = nullptr;
    QPushButton *m_exitButton = nullptr;
    QString m_style;

    double m_width = 120;
    double m_height = 30;
    int m_pointSize = 14;

    double m_half = 2.0;
    QFont m_customFont;
};


#endif //SCREENBASE_H
