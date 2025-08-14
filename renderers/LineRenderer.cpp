#include "LineRenderer.h"
#include <QGraphicsScene>
#include <qpen.h>

LineRenderer::LineRenderer(QGraphicsScene *scene) : m_scene(scene) {
}

void LineRenderer::displayLine(const QRectF &rect) {
    constexpr qreal half = 2;
    constexpr int scalingFactor = 150;
    const int penWidth = rect.width() / scalingFactor;

    QPen pen(Qt::white);
    pen.setWidth(penWidth);
    pen.setStyle(Qt::DashLine);

    if (!lineItem) {
        lineItem = m_scene->addLine(QLineF(rect.width() / half, 0, rect.width() / half, rect.height()), pen);
    } else {
        lineItem->setLine(QLineF(rect.width() / half, 0, rect.width() / half, rect.height()));
        lineItem->setPen(pen);
    }
}

void LineRenderer::hideLine() const {
    if (lineItem) {
        lineItem->hide();
    }
}
