#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QGLWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QSettings>
#include <QString>
#include <QVariant>
#include <QVBoxLayout>
#include <QWidget>
#include <QFileInfo>
#include <QDebug>
#include "customscene.hpp"


const QString MainWindow::SETTINGS_LAST_IMG_PATH("last_img_path");

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QVBoxLayout *layout = new QVBoxLayout;
   ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_actionOpen_source_triggered()
{
   QSettings settings;
   QString lastPath = settings.value(SETTINGS_LAST_IMG_PATH).toString() + "/aslkjf"; // workaround;
   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image", lastPath,"Images (*.png *.jpg)");

   if(!sourcePath.isEmpty())
   {
      QPixmap sourceImage(sourcePath);

      CustomScene* scene = new CustomScene(this);
      scene->addPixmap(sourceImage);

      ui->graphicsView->scale(0.25,0.25);
      ui->graphicsView->setScene(scene);
      saveToSettings(sourcePath);
   }
}

void MainWindow::on_actionOpen_target_triggered()
{
   QSettings settings;
   QString lastPath = settings.value(SETTINGS_LAST_IMG_PATH).toString() + "/aslkjf"; // workaround;
   QString targetPath  = QFileDialog::getOpenFileName(this,"Open target image", lastPath,"Images (*.png *.jpg)");

   if(!targetPath.isEmpty())
   {
      QPixmap targetImage(targetPath);



      CustomScene* scene = new CustomScene(this);
      scene->addPixmap(targetImage);

      ui->graphicsView_2->scale(0.25,0.25);
      ui->graphicsView_2->setScene(scene);

      saveToSettings(targetPath);
   }
}

void MainWindow::saveToSettings(const QString &path)
{
   // prepare for next time and save the current path in the settings
   QFileInfo info(path);

   QSettings settings;
   settings.setValue(SETTINGS_LAST_IMG_PATH,info.absolutePath());
}
