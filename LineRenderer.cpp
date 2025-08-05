#include "LineRenderer.h"
#include <QGraphicsScene>
#include <qpen.h>

LineRenderer::LineRenderer(QGraphicsScene *scene) : m_scene(scene) {
}

void LineRenderer::resizeEvent(QResizeEvent* event, const QRectF& rect) {
    if (!lineItem) {
         displayLine(rect);
    }
}

void LineRenderer::displayLine(const QRectF &rect) {
    constexpr qreal half = 2;
    if (!lineItem) {
        QPen pen(Qt::white);
        constexpr qreal penWidth = 2;
        pen.setWidth(penWidth);
        pen.setStyle(Qt::DashLine);
        lineItem = m_scene->addLine(QLineF(rect.width() / half, 0, rect.width() / half, rect.height()), pen);
    } else {
        lineItem->setLine(QLineF(rect.width() / half, 0, rect.width() / half, rect.height()));
    }
}

void LineRenderer::eraseLine() {
    if (lineItem) {
        m_scene->removeItem(lineItem);
        delete lineItem;
        lineItem = nullptr;
    }
}