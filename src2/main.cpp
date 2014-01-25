#include <QApplication>

#include "mainwindow.hpp"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOrganizationName("Borack");
    app.setApplicationName("Borack Vision");
    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}

