#include "pm_window.hpp"
#include "ui_pm_window.h"

#include <pm_sourcewidget.hpp>

#include <QComboBox>
#include <QDebug>
#include <QVariant>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <converter.hpp>

#include <GCoptimization.h>

#include <assert.h>
#include <cmath>


struct ForSmoothness
{
   std::vector<cv::Mat*> mats;
};

GCoptimization::EnergyTermType SmoothCostFn(GCoptimization::SiteID site1, GCoptimization::SiteID site2, GCoptimization::LabelID l1, GCoptimization::LabelID l2, void* forSmoothness)
{
   if(l1 == l2) return 0;


   // Matching color
   GCoptimization::EnergyTermType energy = 0;
   ForSmoothness* smoothnessStruct = static_cast<ForSmoothness*>(forSmoothness);
   assert(l1 < smoothnessStruct->mats.size());
   assert(l2 < smoothnessStruct->mats.size());

   cv::Mat* mat1 = smoothnessStruct->mats.at(l1);
   cv::Mat* mat2 = smoothnessStruct->mats.at(l2);
   assert(mat1->cols == mat2->cols);
   assert(mat1->rows == mat2->rows);

   const int width = mat1->cols;
   const int height = mat1->rows;

   cv::Point s1(site1%width, std::floor<int>(site1/width));
   cv::Point s2(site2%width, std::floor<int>(site2/width));

   assert(mat1->channels() == 4);
   assert(mat2->channels() == 4);

   cv::Vec4b pixelPInMat1 = mat1->at<cv::Vec4b>(s1);
   cv::Vec4b pixelPInMat2 = mat2->at<cv::Vec4b>(s1);

   cv::Vec4b pixelQInMat1 = mat1->at<cv::Vec4b>(s2);
   cv::Vec4b pixelQInMat2 = mat2->at<cv::Vec4b>(s2);

   energy += std::sqrt(
               std::pow(pixelPInMat1[0] - pixelPInMat2[0], 2.0) +
               std::pow(pixelPInMat1[1] - pixelPInMat2[1], 2.0) +
               std::pow(pixelPInMat1[2] - pixelPInMat2[2], 2.0));

   energy += std::sqrt(
               std::pow(pixelQInMat1[0] - pixelQInMat2[0], 2.0) +
               std::pow(pixelQInMat1[1] - pixelQInMat2[1], 2.0) +
               std::pow(pixelQInMat1[2] - pixelQInMat2[2], 2.0));

   return energy;

}

PmWindow::PmWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::pm_window)
{
   ui->setupUi(this);
   setupComboboxes();
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

   switch (m_gcDataTermMode) {
      case EGraphCut_DataTerm_Minimum_Lumincance:
         runLuminance(true);
         break;
      case EGraphCut_DataTerm_Maximum_Lumincance:
         runLuminance(false);
         break;
      default:
         break;
   }
}

void PmWindow::on_dataComboBox_currentIndexChanged(int index)
{
   m_gcDataTermMode = static_cast<EGraphCut_DataTerm>(ui->dataComboBox->itemData(index).toInt());
   ui->pmWidget->setDataTermMode(m_gcDataTermMode);
   ui->pmWidget_2->setDataTermMode(m_gcDataTermMode);

   qDebug() << "New gc data term mode is " << m_gcDataTermMode;
}

void PmWindow::on_smoothnessComboBox_currentIndexChanged(int index)
{
   m_gcSmoothnessTermMode = static_cast<EGraphCut_SmoothnessTerm>(ui->smoothnessComboBox->itemData(index).toInt());

   qDebug() << "New gc smoothness term mode is " << m_gcSmoothnessTermMode;
}

void PmWindow::setupComboboxes()
{
   // Smootness Term
   this->ui->smoothnessComboBox->insertItem(0, "Matching Color", EGraphCut_SmoothnessTerm_Color);
   this->ui->smoothnessComboBox->insertItem(1, "Matching Gradients", EGraphCut_SmoothnessTerm_Gradients);

   this->ui->smoothnessComboBox->setCurrentIndex(0);

 // Data term
   this->ui->dataComboBox->insertItem(0, "Minimum Luminance", EGraphCut_DataTerm_Minimum_Lumincance);
   this->ui->dataComboBox->insertItem(1, "Maximum Luminance", EGraphCut_DataTerm_Maximum_Lumincance);

   this->ui->dataComboBox->setCurrentIndex(0);


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

   cv::Mat mat1 = Converter::QPixmapToCvMat(*pix1);
   cv::Mat gray1;
   cv::cvtColor(mat1, gray1, CV_BGR2GRAY);
   cv::Mat mat2 = Converter::QPixmapToCvMat(*pix2);
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

   // Setup the Data Costs
   foreach(PMSourceScene::Strokes imageStrokes, allImages)
   {
      int counterPointsInImage= 0;
      foreach (PMSourceScene::Stroke stroke, imageStrokes)
      {
         foreach (QPointF point, stroke)
         {
            counterPointsInImage++;

            const int x = static_cast<int>(round(point.x()));
            const int y = static_cast<int>(round(point.y()));
            const int site = y*gray1.cols + x;

            const uchar lum1 = gray1.at<uchar>(y,x);
            const uchar lum2 = gray2.at<uchar>(y,x);

#if 0
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
#else
       gc->setDataCost(site, 0, lum1*lum1);
       gc->setDataCost(site, 1, lum2*lum2);

#endif
//            qDebug() << "Point: "  << point;
         }
      }
      qDebug() << "Total points in Image " << counterPointsInImage;
   }

   // Setup the DataCosts
   ForSmoothness forSmoothness;
   forSmoothness.mats.push_back(&mat1);
   forSmoothness.mats.push_back(&mat2);

   gc->setSmoothCost(&SmoothCostFn, &forSmoothness);

   qDebug() << "\nBefore optimization energy is %d" << gc->compute_energy();
//   gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
   gc->swap(num_labels);
   qDebug() << "\nAfter optimization energy is %d" << gc->compute_energy();


   int counter0 = 0;
   int counter1 = 0;
   cv::Mat out(mat1.size(), CV_8UC4);
   for (int  i = 0; i < gc->numSites(); i++)
   {
      int r = i / mat1.cols;
      int c = i % mat1.cols;
      int label = gc->whatLabel(i);

      if(label == 0)
      {
         counter0++;
         out.at<cv::Vec4b>(r,c) = mat1.at<cv::Vec4b>(r,c);
      }
      else if(label == 1)
      {
         counter1++;
         out.at<cv::Vec4b>(r,c) = mat2.at<cv::Vec4b>(r,c);
      }
      else
      {
         qDebug() << "ERROR: Not a proper Label!";
      }
   }

//   Converter::CvMatToQImage()

   qDebug() << "Label0 == " << counter0;
   qDebug() << "Label1 == " << counter1;
   cv::imwrite("yees-a-gc-image.png", out);
}

