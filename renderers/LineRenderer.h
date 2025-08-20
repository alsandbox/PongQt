#ifndef LINERENDERER_H
#define LINERENDERER_H

#include "../gameplay/PlayerItem.h"


class LineRenderer final : public QGraphicsLineItem{
    public:
    explicit LineRenderer(QGraphicsScene *scene);
    [[nodiscard]] QGraphicsLineItem* getLine() const {
        return lineItem;
    }
    void setVisible(bool visible) const;
    void displayLine(const QRectF &rect);

    private:
    QGraphicsLineItem* lineItem = nullptr;
    QGraphicsScene* m_scene = nullptr;
};



#endif //LINERENDERER_H
