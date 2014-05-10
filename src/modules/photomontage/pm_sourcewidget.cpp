#include "pm_sourcewidget.hpp"
#include "ui_pm_sourcewidget.h"

#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QSettings>
#include <QString>

#include <assert.h>

const QString PMSourceWidget::SETTINGS_LAST_PM_SOURCE_PATH("last_pm_source_path");

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

PixmapPointer PMSourceWidget::getPixmap()
{
   return m_pixmap;
}

void PMSourceWidget::setDataTermMode(EGraphCut_DataTerm gcMode)
{
   ui->brushComboBox->clear();
   switch (gcMode) {
      case EGraphCut_DataTerm_Minimum_Lumincance:
         ui->brushComboBox->insertItem(0, "MinLum Brush", EBrushType_Minimum_Luminance);
         break;
      default:
         break;
   }
}

const PMSourceScene::Strokes &PMSourceWidget::strokes() const
{
   assert(m_sScene);
   return m_sScene->strokes();
}

void PMSourceWidget::reset()
{
   m_sScene->reset();
}

void PMSourceWidget::on_loadBtn_clicked()
{

   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_PM_SOURCE_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image",  lastPath,"Images (*.png *.jpg *.jpeg)");

   if(!sourcePath.isEmpty())
   {
      m_pixmap.reset(new QPixmap(sourcePath));
      m_sScene.reset(new PMSourceScene(this));

      connect(m_sScene.data(),SIGNAL(runSource()), this, SLOT(on_runSource()));
      m_sScene->setPixmap(*m_pixmap);

      ui->graphicsView->setScene(m_sScene.data());
      ui->graphicsView->fitInView(QRectF(0,0,m_pixmap->width(), m_pixmap->height()), Qt::KeepAspectRatio);

      QSettings settings;
      settings.setValue(SETTINGS_LAST_PM_SOURCE_PATH, sourcePath);
   }
}

void PMSourceWidget::on_runSource()
{

   // NOTE: next steps:
   //       - get the strokes from the PM scene.
   //       - run the appropriate GC on the input images.
   //       - draw the composite into the target scene!
//   qDebug() << "On run on source PM";
}



void PMSourceWidget::on_brushComboBox_currentIndexChanged(int index)
{

}
