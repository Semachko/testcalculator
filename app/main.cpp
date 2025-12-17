#include "gui.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char* argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    Gui gui{};
    engine.rootContext()->setContextProperty("calculator", &gui);
    engine.loadFromModule("Gui", "Main");

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}