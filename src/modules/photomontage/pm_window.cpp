#include "pm_window.hpp"
#include "ui_pm_window.h"

#include <pm_sourcewidget.hpp>

#include <QDebug>

PmWindow::PmWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::pm_window)
{
   ui->setupUi(this);
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
}
