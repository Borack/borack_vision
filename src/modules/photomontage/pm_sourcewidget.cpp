#include "pm_sourcewidget.hpp"
#include "ui_pm_sourcewidget.h"

#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QPixmap>
#include <QSettings>
#include <QString>

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

void PMSourceWidget::on_loadBtn_clicked()
{

   QSettings settings;
   QString lastPath = QFileInfo(settings.value(SETTINGS_LAST_PM_SOURCE_PATH).toString()).absolutePath() + "/aslkjf"; // workaround;
   QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image",  lastPath,"Images (*.png *.jpg)");

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
   qDebug() << "On run on source PM";
}
