#include "LineRenderer.h"
#include <QGraphicsScene>
#include <qpen.h>

LineRenderer::LineRenderer(QGraphicsScene *scene) : m_scene(scene) {
}

void LineRenderer::resizeEvent(QResizeEvent* event, const QRectF& rect) {
    displayLine(rect);
}

void LineRenderer::displayLine(const QRectF &rect) {
    if (!lineItem) {
        QPen pen(Qt::white);
        pen.setStyle(Qt::DashLine);
        pen.setWidth(5);
        lineItem = m_scene->addLine(QLineF(rect.width() / 2, 0, rect.width() / 2, rect.height()), pen);
    } else {
        lineItem->setLine(QLineF(rect.width() / 2, 0, rect.width() / 2, rect.height()));
    }
}