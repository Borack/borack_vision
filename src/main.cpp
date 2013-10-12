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

    QQmlApplicationEngine engine(QUrl("qrc:///qml/main.qml"));

    engine.addImageProvider(QLatin1String("imageprovider"), imageProvider);

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("_commonHandler", &cH);

    return app.exec();

}
