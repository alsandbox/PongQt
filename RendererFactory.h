#ifndef RENDERERFACTORY_H
#define RENDERERFACTORY_H
#include "Renderer.h"


class RendererFactory {
public:
    static std::shared_ptr<Renderer> createRenderer(QGraphicsScene* scene, QWidget* parent = nullptr);
};




#endif //RENDERERFACTORY_H
