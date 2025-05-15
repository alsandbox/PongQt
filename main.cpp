#include <QApplication>
#include "PlayerRenderer.h"
#include "Renderer.h"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QGraphicsScene scene(0, 0, 200, 100);
    Renderer renderer(&scene);
    renderer.show();

    return QApplication::exec();
}
