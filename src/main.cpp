#include <QGuiApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>

#include "common_handler.hpp"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    CommonHandler cH;

    QQmlApplicationEngine engine(QUrl("qrc:///qml/main.qml"));

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("_commonHandler", &cH);

    return app.exec();

}
