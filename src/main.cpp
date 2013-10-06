#include <QGuiApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine(QUrl("qrc:///qml/main.qml"));
//    engine.set

//    QQuickView viewer;

//    viewer.setSource(QUrl(()));
//    viewer.show();


    return app.exec();

}
