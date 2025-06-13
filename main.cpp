#include <QApplication>
#include "Renderer.h"
#include "RendererFactory.h"


int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QGraphicsScene scene(0, 0, 200, 100);

    const auto renderer = RendererFactory::createRenderer(&scene);
    renderer->show();

    return QApplication::exec();
}

