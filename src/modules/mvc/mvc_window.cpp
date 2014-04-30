#include "mvc_window.hpp"

#include "ui_mvc_window.h"

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


const QString MvcWindow::SETTINGS_LAST_SOURCE_PATH("last_img_source_path");
const QString MvcWindow::SETTINGS_LAST_TARGET_PATH("last_img_target_path");

//-----------------------------------------------------------------------------
MvcWindow::MvcWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MvcWindow)
 , m_sScene(0)
 , m_tScene(0)
{
   ui->setupUi(this);
   setup();
}

//-----------------------------------------------------------------------------
MvcWindow::~MvcWindow()
{
   delete ui;
}

//-----------------------------------------------------------------------------
void MvcWindow::on_actionOpen_source_triggered()
{
   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_SOURCE_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image", lastPath,"Images (*.png *.jpg)");
   loadSourceImg(sourcePath);
}

//-----------------------------------------------------------------------------
void MvcWindow::on_actionOpen_target_triggered()
{
   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_TARGET_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString targetPath  = QFileDialog::getOpenFileName(this,"Open target image", lastPath,"Images (*.png *.jpg)");
   loadTargetImg(targetPath);
}

//-----------------------------------------------------------------------------
void MvcWindow::on_runSource()
{
   if(m_mode == EMode_MVC)
   {
      assert(m_mvcCloning);
      m_mvcCloning->startSourceComputation(dynamic_cast<MVCSourceScene*>(m_sScene)->getBoundary());
   }
}

//-----------------------------------------------------------------------------
void MvcWindow::on_runTarget()
{
   if(m_mode == EMode_MVC)
   {
      assert(m_mvcCloning);
      // could be called within a new thread
      m_mvcCloning->startTargetComputation(dynamic_cast<MVCTargetScene*>(m_tScene)->clickLocation());
   }
}


//-----------------------------------------------------------------------------
void MvcWindow::setup()
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

   // since this is not the default we disable the counter from here.
   ui->spinBox->hide();

}

//-----------------------------------------------------------------------------
void MvcWindow::loadSourceImg(const QString &path)
{

   if(!path.isEmpty())
   {
      QPixmap sourceImage(path);


      // delete old instance if we already have one.
      if(m_sScene)
      {
         delete m_sScene;
      }

      if(m_mode == EMode_MVC)
      {
         m_sScene = new MVCSourceScene(this);
      }
      else
      {
         qFatal("Mode %d doees not provide a souce scene.", m_mode);
      }
      assert(m_sScene);


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
void MvcWindow::loadTargetImg(const QString &path)
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
      else
      {
         qFatal("Mode %d doees not provide a target scene.", m_mode);
      }
      assert(m_tScene);

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
void MvcWindow::tryToLoadMVCInstance()
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
void MvcWindow::on_buttonBox_clicked(QAbstractButton *button)
{
   if(ui->buttonBox->button(QDialogButtonBox::Close) == button)
   {
      QApplication::quit();
   }
}

//-----------------------------------------------------------------------------
void MvcWindow::on_reset()
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
void MvcWindow::on_sourceZoom_sliderMoved(int position)
{
   float scale = static_cast<float>(position)/100.0f;
   ui->sourceView->resetMatrix();
   ui->sourceView->scale(scale, scale);
}

//-----------------------------------------------------------------------------
void MvcWindow::on_targetZoom_sliderMoved(int position)
{
   float scale = static_cast<float>(position)/100.0f;
   ui->targetView->resetMatrix();
   ui->targetView->scale(scale, scale);
}

//-----------------------------------------------------------------------------
void MvcWindow::on_mvcSelected(bool enabled)
{
   qDebug() << "On mvc enabled" << enabled;
   if(enabled)
   {
      //resetting
      on_reset();
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

