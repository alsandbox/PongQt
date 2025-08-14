#ifndef LINERENDERER_H
#define LINERENDERER_H

#include "../PlayerItem.h"


class LineRenderer final : public QGraphicsLineItem{
    public:
    explicit LineRenderer(QGraphicsScene *scene);
    void resizeEvent(QResizeEvent* event, const QRectF& rect);
    [[nodiscard]] QGraphicsLineItem* getLine() const {
        return lineItem;
    }
    void hideLine() const;
    void displayLine(const QRectF &rect);

    private:
    void displayLine(const QRectF &rect);

    QGraphicsLineItem* lineItem = nullptr;
    QGraphicsScene* m_scene = nullptr;
};



#endif //LINERENDERER_H
