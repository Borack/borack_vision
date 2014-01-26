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


#include "sourcescene.hpp"
#include "targetscene.hpp"


const QString MainWindow::SETTINGS_LAST_SOURCE_PATH("last_img_source_path");
const QString MainWindow::SETTINGS_LAST_TARGET_PATH("last_img_target_path");

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   setup();
}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::on_actionOpen_source_triggered()
{
   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_SOURCE_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image", lastPath,"Images (*.png *.jpg)");
   loadSourceImg(sourcePath);
}

void MainWindow::on_actionOpen_target_triggered()
{
   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_TARGET_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString targetPath  = QFileDialog::getOpenFileName(this,"Open target image", lastPath,"Images (*.png *.jpg)");
   loadTargetImg(targetPath);
}


void MainWindow::setup()
{
   QSettings settings;
   loadSourceImg(settings.value(SETTINGS_LAST_SOURCE_PATH).toString());
   loadTargetImg(settings.value(SETTINGS_LAST_TARGET_PATH).toString());
}

void MainWindow::loadSourceImg(const QString &path)
{

   if(!path.isEmpty())
   {
      QPixmap sourceImage(path);


      SourceScene* scene = new SourceScene(this);
      scene->setPixmap(sourceImage);

      ui->graphicsView->scale(0.25,0.25);
      ui->graphicsView->setScene(scene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_SOURCE_PATH, path);
   }

}

void MainWindow::loadTargetImg(const QString &path)
{
   if(!path.isEmpty())
   {
      QPixmap targetImage(path);

      TargetScene* scene = new TargetScene(this);
      scene->setPixmap(targetImage);

      ui->graphicsView_2->scale(0.25,0.25);
      ui->graphicsView_2->setScene(scene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_TARGET_PATH, path);
   }
}
