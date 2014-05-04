#include "pm_window.hpp"
#include "ui_pm_window.h"

#include <pm_sourcewidget.hpp>

#include <QComboBox>
#include <QDebug>
#include <QVariant>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <converter.hpp>

#include <GCoptimization.h>

#include <assert.h>
#include <math.h>

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
   // FIXME: for now everything is hardcoded to 2 input images => 2 labels
   const int num_labels = 2;

   PixmapPointer pix1 = ui->pmWidget->getPixmap();
   PixmapPointer pix2 = ui->pmWidget_2->getPixmap();

   assert(pix1);
   assert(pix2);
   assert(pix1->width() == pix2->width());
   assert(pix1->height() == pix2->height());


   std::vector<PMSourceScene::Strokes> allImages;
   allImages.push_back(ui->pmWidget->strokes());
   allImages.push_back(ui->pmWidget_2->strokes());

   cv::Mat mat1 = Converter::QPixmapToCvMatToCvMat(*pix1);
   cv::Mat gray1;
   cv::cvtColor(mat1, gray1, CV_BGR2GRAY);
   cv::Mat mat2 = Converter::QPixmapToCvMatToCvMat(*pix2);
   cv::Mat gray2;
   cv::cvtColor(mat2, gray2, CV_BGR2GRAY);

   assert(gray1.cols == gray2.cols && gray1.rows == gray2.rows);

   GCoptimizationGridGraph* gc = new GCoptimizationGridGraph(mat1.cols, mat1.rows, num_labels);

   assert(gc->numSites() == gray1.cols*gray1.rows);

   // TODO:
   // 1) find for each point the minimum(maximum) luminance color
   // 2) Assign to each pixel at the strokes position the data cost.
   // 3) SmoothCost
   // 4) Run GC and generate composite.

   // See here for some implementation details: http://grail.cs.washington.edu/projects/photomontage/release/

   foreach(PMSourceScene::Strokes imageStrokes, allImages)
   {
      foreach (PMSourceScene::Stroke stroke, imageStrokes)
      {
         qDebug() << "A new stroke: ";
         foreach (QPointF point, stroke)
         {
            const int x = static_cast<int>(std::round(point.x()));
            const int y = static_cast<int>(std::round(point.y()));
            const int site = y*gray1.cols + x;

            const int lum1 = gray1.at<uchar>(x,y);
            const int lum2 = gray2.at<uchar>(x,y);

            if(lum1 < lum2)
            {
               gc->setDataCost(site,0,0);
               gc->setDataCost(site,1,std::abs(lum2-lum1));
            }
            else
            {
               gc->setDataCost(site,0,std::abs(lum1-lum2));
               gc->setDataCost(site,1,0);
            }


            qDebug() << "Point: "  << point;
         }
      }
   }
}
