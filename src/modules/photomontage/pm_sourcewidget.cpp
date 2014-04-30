#include "pm_sourcewidget.hpp"
#include "ui_pm_sourcewidget.h"

#include <QFileDialog>
#include <QPixmap>
#include <QString>

#include <assert.h>

PMSourceWidget::PMSourceWidget(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::PMSourceWidget)
 , m_sScene(0)
{
   ui->setupUi(this);
}

PMSourceWidget::~PMSourceWidget()
{
   delete ui;
}

void PMSourceWidget::on_loadBtn_clicked()
{

   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image",  QString(),"Images (*.png *.jpg)");

   if(!sourcePath.isEmpty())
   {
      QPixmap sourceImage(sourcePath);


      // delete old instance if we already have one.
      if(m_sScene)
      {
         delete m_sScene;
      }

      m_sScene = new PMSourceScene(this);


      assert(m_sScene);


//      connect(m_sScene,SIGNAL(runSource()), this, SLOT(on_runSource()));
      m_sScene->setPixmap(sourceImage);

 //     float currentScale = ui->sourceZoom->value()/100.0f;
 //     ui->sourceView->scale(currentScale,currentScale);
//      ui->sourceView->setScene(m_sScene);

      ui->graphicsView->setScene(m_sScene);
      ui->graphicsView->fitInView(QRectF(0,0,sourceImage.width(), sourceImage.height()), Qt::KeepAspectRatio);

//      QSettings settings;
//      settings.setValue(SETTINGS_LAST_SOURCE_PATH, path);
//      tryToLoadMVCInstance();
   }
}
