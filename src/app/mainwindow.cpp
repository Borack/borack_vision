#include "mainwindow.hpp"

#include "ui_mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QActionGroup>
#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QGLWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QString>
#include <QToolButton>
#include <QVBoxLayout>
#include <QVariant>
#include <QWidget>


//! @note   Consider to use boost::statechart here!
//!
//! @note   Consider to use a commong interface for all the modules.
//!         Although most likely this is not very applicable since not all the modules need the same input parameters.
//!         Providing dummy parameters for the ones that are required is an option - however this is not nice.


const QString MainWindow::SETTINGS_LAST_SOURCE_PATH("last_img_source_path");
const QString MainWindow::SETTINGS_LAST_TARGET_PATH("last_img_target_path");

//-----------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , m_sScene(0)
 , m_tScene(0)
{
   ui->setupUi(this);
   setup();
}

//-----------------------------------------------------------------------------
MainWindow::~MainWindow()
{
   delete ui;
}

//-----------------------------------------------------------------------------
void MainWindow::on_actionOpen_source_triggered()
{
   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_SOURCE_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image", lastPath,"Images (*.png *.jpg)");
   loadSourceImg(sourcePath);
}

//-----------------------------------------------------------------------------
void MainWindow::on_actionOpen_target_triggered()
{
   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_TARGET_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString targetPath  = QFileDialog::getOpenFileName(this,"Open target image", lastPath,"Images (*.png *.jpg)");
   loadTargetImg(targetPath);
}

//-----------------------------------------------------------------------------
void MainWindow::on_runSource()
{
   if(m_mode == EMode_MVC)
   {
      assert(m_mvcCloning);
      m_mvcCloning->startSourceComputation(dynamic_cast<MVCSourceScene*>(m_sScene)->getBoundary());
   }
   else if(m_mode == EMode_PhotoMontage)
   {
      assert(m_photoMontage);
   }
}

//-----------------------------------------------------------------------------
void MainWindow::on_runTarget()
{
   if(m_mode == EMode_MVC)
   {
      assert(m_mvcCloning);
      // could be called within a new thread
      m_mvcCloning->startTargetComputation(dynamic_cast<MVCTargetScene*>(m_tScene)->clickLocation());
   }
   else if(m_mode == EMode_PhotoMontage)
   {
      assert(m_photoMontage);
   }
}


//-----------------------------------------------------------------------------
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

   QActionGroup* actionGroup = new QActionGroup(ui->menuMode);
   actionGroup->setExclusive(true);

   // MVC module
   QAction* mvcAction = new QAction("MVC",this);
   mvcAction->setCheckable(true);
   connect(mvcAction, SIGNAL(triggered(bool)), this, SLOT(on_mvcSelected(bool)));
   mvcAction->setChecked(true);
   mvcAction->setActionGroup(actionGroup);
   ui->menuMode->addAction(mvcAction);

   // PhotoMontage module
   QAction* photoMontageAction = new QAction("PhotoMontage",this);
   photoMontageAction->setCheckable(true);
   connect(photoMontageAction, SIGNAL(triggered(bool)), this, SLOT(on_photoMontageSelected(bool)));
   photoMontageAction->setActionGroup(actionGroup);
   ui->menuMode->addAction(photoMontageAction);

   // since this is not the default we disable the counter from here.
   ui->spinBox->hide();

}

//-----------------------------------------------------------------------------
void MainWindow::loadSourceImg(const QString &path)
{

   if(!path.isEmpty())
   {
      QPixmap sourceImage(path);


      if(m_sScene)
      {
         delete m_sScene;
      }

      if(m_mode == EMode_MVC)
      {
         m_sScene = new MVCSourceScene(this);
      }
      else if(m_mode == EMode_PhotoMontage)
      {
         m_sScene = new PhotomontageSourceScene(this);
      }
      else
      {
         qFatal("Mode %d doees not provide a souce scene.", m_mode);
      }
      // delete old instance if we already have one.


      connect(m_sScene,SIGNAL(runSource()), this, SLOT(on_runSource()));
      m_sScene->setPixmap(sourceImage);

      float currentScale = ui->sourceZoom->value()/100.0f;
      ui->sourceView->scale(currentScale,currentScale);
      ui->sourceView->setScene(m_sScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_SOURCE_PATH, path);
      tryToLoadMVCInstance();
   }

}

//-----------------------------------------------------------------------------
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

      if(m_mode == EMode_MVC)
      {
         m_tScene = new MVCTargetScene(this);
      }
      else if(m_mode == EMode_PhotoMontage)
      {
//         m_sScene = new
      }
      else
      {
         qFatal("Mode %d doees not provide a target scene.", m_mode);
      }
      connect(m_tScene,SIGNAL(runTarget()), this, SLOT(on_runTarget()));
      m_tScene->setPixmap(targetImage);


      float currentScale = ui->targetZoom->value()/100.0f;
      ui->targetView->scale(currentScale,currentScale);
      ui->targetView->setScene(m_tScene);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_TARGET_PATH, path);
      tryToLoadMVCInstance();
   }
}

//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
void MainWindow::on_buttonBox_clicked(QAbstractButton *button)
{
   if(ui->buttonBox->button(QDialogButtonBox::Close) == button)
   {
      QApplication::quit();
   }
}

//-----------------------------------------------------------------------------
void MainWindow::on_reset()
{
   qDebug() << "Reset triggered";
   m_sScene->reset();
   m_tScene->reset();
   if(m_mvcCloning)
   {
      m_mvcCloning->resetCoords();
   }
}


//-----------------------------------------------------------------------------
void MainWindow::on_sourceZoom_sliderMoved(int position)
{
   float scale = static_cast<float>(position)/100.0f;
   ui->sourceView->resetMatrix();
   ui->sourceView->scale(scale, scale);
}

//-----------------------------------------------------------------------------
void MainWindow::on_targetZoom_sliderMoved(int position)
{
   float scale = static_cast<float>(position)/100.0f;
   ui->targetView->resetMatrix();
   ui->targetView->scale(scale, scale);
}

//-----------------------------------------------------------------------------
void MainWindow::on_mvcSelected(bool enabled)
{
   qDebug() << "On mvc enabled" << enabled;
   if(enabled)
   {
      //resetting
      on_reset();
      m_photoMontage.reset();
      tryToLoadMVCInstance();

      //logic changes
      m_mode = EMode_MVC;

      //ui changes
      ui->spinBox->hide();

      QSettings settings;
      loadSourceImg(settings.value(SETTINGS_LAST_SOURCE_PATH).toString());
      loadTargetImg(settings.value(SETTINGS_LAST_TARGET_PATH).toString());
   }
}

//-----------------------------------------------------------------------------
void MainWindow::on_photoMontageSelected(bool enabled)
{
   qDebug() << "On photomontage enabled" << enabled;
   if(enabled)
   {
      // reseting
      on_reset();
      m_mvcCloning.reset();
      m_photoMontage.reset(new PhotoMontage(m_sScene->getPixmap(),this));

      //logic changes
      m_mode = EMode_PhotoMontage;

      //ui changes
      ui->spinBox->show();

      QSettings settings;
      loadSourceImg(settings.value(SETTINGS_LAST_SOURCE_PATH).toString());
      loadTargetImg(settings.value(SETTINGS_LAST_TARGET_PATH).toString());
   }
}
