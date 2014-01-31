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

void MainWindow::on_runMVCComputation()
{
   m_mvcCloning.reset(new MeanValueSeamlessCloning(m_sScene->getPixmap(), m_sScene->getBoundary(), m_tScene->getPixmap(), m_tScene->clickLocation()));
   connect(m_mvcCloning.data(),SIGNAL(targetContourCalculated(MVC::Boundary)), m_tScene ,SLOT(drawContour(MVC::Boundary)));
   connect(m_mvcCloning.data(), SIGNAL(displayFinalPatch(QImage)), m_tScene, SLOT(drawFinalPatch(QImage)));
   // could be called within a new thread
   m_mvcCloning->startComputation();
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

   ui->pushButton->addAction(resetAction);
}

void MainWindow::loadSourceImg(const QString &path)
{

   if(!path.isEmpty())
   {
      QPixmap sourceImage(path);


      m_sScene = new SourceScene(this);
      m_sScene->setPixmap(sourceImage);

      ui->graphicsView_3->scale(0.5,0.5);
      ui->graphicsView_3->setScene(m_sScene);

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

      ui->graphicsView_4->scale(0.5,0.5);
      ui->graphicsView_4->setScene(m_tScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_TARGET_PATH, path);
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
