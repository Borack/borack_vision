#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QCloseEvent>
#include <QSettings>

#include <mvc_window.hpp>
#include <pm_window.hpp>

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

void MainWindow::on_mvcButton_clicked()
{
   if(m_moduleWindow)
   {
      m_moduleWindow->close();
   }
   m_moduleWindow = new MvcWindow;
   m_moduleWindow->show();
}

void MainWindow::on_pmButton_clicked()
{
   if(m_moduleWindow)
   {
      m_moduleWindow->close();
   }

   m_moduleWindow = new PmWindow;
   m_moduleWindow->show();

}
