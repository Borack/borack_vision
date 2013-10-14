#include <QGuiApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>

#include "common_handler.hpp"
#include "image_provider.hpp"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ImageProvider* imageProvider = new ImageProvider;
    CommonHandler cH(imageProvider);

    QQmlApplicationEngine engine;
    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("_commonHandler", &cH);

    engine.addImageProvider(QLatin1String("imageprovider"), imageProvider);


    engine.load(QUrl("qrc:///qml/main.qml"));

    return app.exec();

}
