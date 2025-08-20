#include <QApplication>
#include "renderers/Renderer.h"
#include "renderers/RendererFactory.h"


int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":/icon/pong.png"));

    QGraphicsScene scene(0, 0, 200, 100);

    const auto renderer = RendererFactory::createRenderer(&scene);
    renderer->show();

    return QApplication::exec();
}

