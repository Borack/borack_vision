#include "pm_window.hpp"
#include "ui_pm_window.h"

#include <pm_sourcewidget.hpp>

#include <QComboBox>
#include <QDebug>
#include <QVariant>

PmWindow::PmWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::pm_window)
{
   ui->setupUi(this);
   setupCombobox();
}

PmWindow::~PmWindow()
{
   delete ui;
}

void PmWindow::on_runButton_clicked()
{
   PixmapPointer pix1 = ui->pmWidget->getPixmap();
   PixmapPointer pix2 = ui->pmWidget_2->getPixmap();

   if(!pix1 || !pix2)
   {
      qDebug() << "Either input image 1 or 2 is not defined.";
      return;
   }

   if(pix1->width()  != pix2->width()
         || pix1->height()  != pix2->height())
   {
      qDebug() << "The input images do not have the same size.";
      return;
   }

   qDebug() << "Everything is fine";

   switch (m_gcMode) {
      case EGraphCut_Objective_Minimum_Lumincance:
         runLuminance(true);
         break;
      case EGraphCut_Objective_Maximum_Lumincance:
         runLuminance(false);
         break;
      default:
         break;
   }
}

void PmWindow::on_comboBox_currentIndexChanged(int index)
{
   m_gcMode = static_cast<EGraphCut_Objective>(ui->comboBox->itemData(index).toInt());
   ui->pmWidget->setMode(m_gcMode);
   ui->pmWidget_2->setMode(m_gcMode);

   qDebug() << "New gc mode is " << m_gcMode;
}

void PmWindow::setupCombobox()
{
   this->ui->comboBox->insertItem(0, "Minimum Luminance", EGraphCut_Objective_Minimum_Lumincance);
   this->ui->comboBox->insertItem(1, "Maximum Luminance", EGraphCut_Objective_Maximum_Lumincance);

   this->ui->comboBox->setCurrentIndex(0);
}

void PmWindow::runLuminance(bool isMinimum)
{

}
