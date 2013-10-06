#include <QGuiApplication>
#include <QQuickView>
#include <QQmlApplicationEngine>


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);


    QQmlApplicationEngine engine(QUrl("qrc:///qml/main.qml"));
    return app.exec();

}
