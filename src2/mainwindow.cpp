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



const QString MainWindow::SETTINGS_LAST_SOURCE_PATH("last_img_source_path");
const QString MainWindow::SETTINGS_LAST_TARGET_PATH("last_img_target_path");

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow)
 , m_mvcCloning(0)
 , m_sScene(0)
 , m_tScene(0)
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

void MainWindow::on_runMVCComputation()
{
   m_mvcCloning.reset(new MeanValueSeamlessCloning(m_sScene->getPixmap(), m_sScene->getBoundary(), m_tScene->getPixmap(), m_tScene->clickLocation()));
   connect(m_mvcCloning.data(),SIGNAL(targetContourCalculated(MVC::Boundary)), m_tScene ,SLOT(drawContour(MVC::Boundary)) );
   // could be called within a new thread
   m_mvcCloning->startComputation();
   qDebug() << "Start running mvc";
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


      m_sScene = new SourceScene(this);
      m_sScene->setPixmap(sourceImage);

      ui->graphicsView->scale(0.5,0.5);
      ui->graphicsView->setScene(m_sScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_SOURCE_PATH, path);
   }

}

void MainWindow::loadTargetImg(const QString &path)
{
   if(!path.isEmpty())
   {
      QPixmap targetImage(path);

      m_tScene = new TargetScene(this);
      connect(m_tScene,SIGNAL(runMVCComputation()), this, SLOT(on_runMVCComputation()));
      m_tScene->setPixmap(targetImage);

      ui->graphicsView_2->scale(0.5,0.5);
      ui->graphicsView_2->setScene(m_tScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_TARGET_PATH, path);
   }
}
