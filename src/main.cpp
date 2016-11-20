#include <QApplication>
#include <Box2D/Box2d.h>

#include "MainWindow.h"


b2Vec2 gravity(0.0f, -10.0f);

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow* window = new MainWindow();
    return app.exec();
}
