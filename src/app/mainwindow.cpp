#include "mainwindow.hpp"

#include "ui_mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QGLWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QSettings>
#include <QString>
#include <QToolButton>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>


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

void MainWindow::on_runMVCSource()
{
   m_mvcCloning->startSourceComputation(m_sScene->getBoundary());
}

void MainWindow::on_runMVCTarget()
{
   // could be called within a new thread
   m_mvcCloning->startTargetComputation(m_tScene->clickLocation());
   qDebug() << "Start running mvc";
}


void MainWindow::setup()
{
   QSettings settings;
   loadSourceImg(settings.value(SETTINGS_LAST_SOURCE_PATH).toString());
   loadTargetImg(settings.value(SETTINGS_LAST_TARGET_PATH).toString());

   QAction* resetAction = new QAction("Reset",this);
   resetAction->setShortcut(Qt::CTRL+Qt::Key_R);

   connect(resetAction, SIGNAL(triggered(bool)), this, SLOT(on_reset()));
   connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_reset()));

   ui->pushButton->addAction(resetAction);
}

void MainWindow::loadSourceImg(const QString &path)
{

   if(!path.isEmpty())
   {
      QPixmap sourceImage(path);


      if(m_sScene)
      {
         delete m_sScene;
      }
      m_sScene = new SourceScene(this);
      // delete old instance if we already have one.


      connect(m_sScene,SIGNAL(runMVCSource()), this, SLOT(on_runMVCSource()));
      m_sScene->setPixmap(sourceImage);

      float currentScale = ui->sourceZoom->value()/100.0f;
      ui->sourceView->scale(currentScale,currentScale);
      ui->sourceView->setScene(m_sScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_SOURCE_PATH, path);
      tryToLoadMVCInstance();
   }

}

void MainWindow::loadTargetImg(const QString &path)
{
   if(!path.isEmpty())
   {
      QPixmap targetImage(path);

      // delete old instance if we already have one.
      if(m_tScene)
      {
         delete m_tScene;
      }
      m_tScene = new TargetScene(this);
      connect(m_tScene,SIGNAL(runMVCComputation()), this, SLOT(on_runMVCTarget()));
      m_tScene->setPixmap(targetImage);


      float currentScale = ui->targetZoom->value()/100.0f;
      ui->targetView->scale(currentScale,currentScale);
      ui->targetView->setScene(m_tScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_TARGET_PATH, path);
      tryToLoadMVCInstance();
   }
}

void MainWindow::tryToLoadMVCInstance()
{
   // FIXME check if null
   if(m_sScene && m_tScene &&
         ! (m_sScene->getPixmap().isNull() || m_tScene->getPixmap().isNull()))
   {
      m_mvcCloning.reset(new MeanValueSeamlessCloning(m_sScene->getPixmap(), m_tScene->getPixmap()));

      connect(m_mvcCloning.data(),SIGNAL(displayMesh(MVC::Mesh2d::Segments)), m_sScene, SLOT(drawMesh(MVC::Mesh2d::Segments)));

      connect(m_mvcCloning.data(),SIGNAL(targetContourCalculated(MVC::Boundary)), m_tScene ,SLOT(drawContour(MVC::Boundary)));
      connect(m_mvcCloning.data(), SIGNAL(displayFinalPatch(QImage)), m_tScene, SLOT(drawFinalPatch(QImage)));
   }
}

void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
   if(ui->buttonBox->button(QDialogButtonBox::Close) == button)
   {
      QApplication::quit();
   }
}

void MainWindow::on_reset()
{
   qDebug() << "Reset triggered";
   m_sScene->reset();
   m_tScene->reset();
}


void MainWindow::on_sourceZoom_sliderMoved(int position)
{
   float scale = static_cast<float>(position)/100.0f;
   ui->sourceView->resetMatrix();
   ui->sourceView->scale(scale, scale);
}

void MainWindow::on_targetZoom_sliderMoved(int position)
{
   float scale = static_cast<float>(position)/100.0f;
   ui->targetView->resetMatrix();
   ui->targetView->scale(scale, scale);
}
