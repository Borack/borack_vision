#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QCloseEvent>
#include <QSettings>

const int UI_VERSION = 1;

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QSettings settings;
   restoreGeometry(settings.value("geometry").toByteArray());
   restoreState(settings.value("state").toByteArray(),UI_VERSION);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
   QSettings settings;
   settings.setValue("geometry", saveGeometry());
   settings.setValue("state", saveState(UI_VERSION));
   event->accept();
}

void MainWindow::on_quitButton_clicked()
{
   QApplication::closeAllWindows();
   QApplication::quit();
}
