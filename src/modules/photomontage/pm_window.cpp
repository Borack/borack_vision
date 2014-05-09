#include "pm_window.hpp"
#include "ui_pm_window.h"

#include <QComboBox>
#include <QDebug>
#include <QSharedPointer>
#include <QString>
#include <QTabBar>
#include <QTabWidget>
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
   std::vector<QSharedPointer<cv::Mat> > mats;
};

GCoptimization::EnergyTermType SmoothCostFn(GCoptimization::SiteID site1, GCoptimization::SiteID site2, GCoptimization::LabelID l1, GCoptimization::LabelID l2, void* forSmoothness)
{
   if(l1 == l2) return 0;


   // Matching color
   GCoptimization::EnergyTermType energy = 0;
   ForSmoothness* smoothnessStruct = static_cast<ForSmoothness*>(forSmoothness);
   assert(l1 < smoothnessStruct->mats.size());
   assert(l2 < smoothnessStruct->mats.size());

   QSharedPointer<cv::Mat> mat1 = smoothnessStruct->mats.at(l1);
   QSharedPointer<cv::Mat> mat2 = smoothnessStruct->mats.at(l2);
   assert(mat1->cols == mat2->cols);
   assert(mat1->rows == mat2->rows);

   const int width = mat1->cols;
   const int height = mat1->rows;

   cv::Point s1(site1%width, site1/width);
   cv::Point s2(site2%width, site2/width);

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
   addANewTab();
   addANewTab();
   ui->tabWidget->setCurrentIndex(0);
   setupComboboxes();
}

PmWindow::~PmWindow()
{
   delete ui;
}

void PmWindow::on_runButton_clicked()
{

   const int numTabs = ui->tabWidget->count();
   PMVector allInput;
   for(int i = 0; i< numTabs-1;i++)
   {
      PMSourceWidget* pmSourceWidget = dynamic_cast<PMSourceWidget*>(ui->tabWidget->widget(i));
      if(pmSourceWidget && pmSourceWidget->getPixmap())
      {
         allInput.push_back(PMPair(pmSourceWidget->getPixmap(), pmSourceWidget->strokes()));
      }

     // as soon as there are more then 2 images in the list, make sure all images have the same size.
      if(allInput.size() > 1)
      {
         const int latest = allInput.size() - 1;
         if(allInput[latest].first->width() != allInput[latest-1].first->width() ||
               allInput[latest].first->height() != allInput[latest-1].first->height() )
         {
            qFatal("Uhuh, All input images need to have the same size. :-/");
            return;
         }
      }
   }


   qDebug() << "Everything is fine";

   switch (m_gcDataTermMode) {
      case EGraphCut_DataTerm_Minimum_Lumincance:
         runLuminance(allInput, true);
         break;
      case EGraphCut_DataTerm_Maximum_Lumincance:
         runLuminance(allInput, false);
         break;
      default:
         break;
   }
}

void PmWindow::on_dataComboBox_currentIndexChanged(int index)
{
   m_gcDataTermMode = static_cast<EGraphCut_DataTerm>(ui->dataComboBox->itemData(index).toInt());

   const int numTabs = ui->tabWidget->count();
   for(int i = 0; i<numTabs-1;i++)// last tab is the '+' tab, do not modify this.
   {
      PMSourceWidget* pmSourceWidget = dynamic_cast<PMSourceWidget*>(ui->tabWidget->widget(i));
      if(pmSourceWidget)  pmSourceWidget->setDataTermMode(m_gcDataTermMode);
      else qDebug() << "Error, cannot cast to PMSourceWidget";
   }

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

void PmWindow::addANewTab()
{
   // never show latest tab!
   const int numTabs = ui->tabWidget->count();
   QString tabName("Source ");
   tabName.append(QString::number(numTabs));
   ui->tabWidget->insertTab(numTabs-1,new PMSourceWidget,tabName);
   dynamic_cast<PMSourceWidget*>(ui->tabWidget->widget(numTabs-1))->setDataTermMode(m_gcDataTermMode);
   ui->tabWidget->setCurrentIndex(numTabs-1);
}

void PmWindow::runLuminance(const PMVector &allInput, bool isMinimum)
{

   // See here for some implementation details: http://grail.cs.washington.edu/projects/photomontage/release/
   const int num_labels = allInput.size(); // ==num of images!
   if(num_labels == 0)
   {
      qWarning("Error: No images specified.");
       return;
   }

   std::vector<cv::Mat> grayMats;

   foreach(PMPair pair, allInput)
   {
      cv::Mat gray;
      cv::cvtColor(Converter::QPixmapToCvMat(*pair.first),gray,CV_BGR2GRAY);
      grayMats.push_back(gray);
   }


   const int width = allInput[0].first->width();
   const int height = allInput[0].first->height();

   GCoptimizationGridGraph* gc = new GCoptimizationGridGraph(width, height, num_labels);

   assert(gc->numSites() == width*height);



   // Setup the DataCosts
   ForSmoothness forSmoothness;

   // Setup the Data Costs
   foreach(PMPair pair, allInput)
   {

      QSharedPointer<cv::Mat> matPtr;
      matPtr.reset(new cv::Mat(Converter::QPixmapToCvMat(*pair.first)));
      forSmoothness.mats.push_back(matPtr);


      int counterPointsInImage= 0;
      PMSourceScene::Strokes imageStrokes = pair.second;
      foreach (PMSourceScene::Stroke stroke, imageStrokes)
      {
         foreach (QPointF point, stroke)
         {
            counterPointsInImage++;

            const int x = static_cast<int>(round(point.x()));
            const int y = static_cast<int>(round(point.y()));
            const int site = y*width + x;

            int valueToCompare = grayMats[0].at<uchar>(y,x);

            // get the minimum / maximum luminance
            for(int i = 1; i< num_labels;i++)
            {
               if(isMinimum)
               {
                  valueToCompare = std::min<uchar>(valueToCompare, grayMats[i].at<uchar>(y,x));
               }
               else
               {
                  valueToCompare = std::max<uchar>(valueToCompare, grayMats[i].at<uchar>(y,x));
               }
            }

            // calculate the actual data cost
            for(int i = 0; i< num_labels;i++)
            {
               const uchar matLum = grayMats[i].at<uchar>(y,x);
               const int energy = (matLum-valueToCompare)*(matLum-valueToCompare);
               gc->setDataCost(site,i,energy);
            }
         }
      }

      qDebug() << "Total points in Image " << counterPointsInImage;
   }

   gc->setSmoothCost(&SmoothCostFn, &forSmoothness);

   qDebug() << "\nBefore optimization energy is " << gc->compute_energy();
      gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
//   gc->swap(num_labels);
   qDebug() << "\nAfter optimization energy is " << gc->compute_energy();


   cv::Mat out(cv::Size(width,height), CV_8UC4);
   for (int  i = 0; i < gc->numSites(); i++)
   {
      int r = i / width;
      int c = i % width;
      int label = gc->whatLabel(i);

      out.at<cv::Vec4b>(r,c) = forSmoothness.mats[label]->at<cv::Vec4b>(r,c);
   }

   QPixmap pixmap = Converter::CvMatToQPixmap(out);
   m_tScene.reset(new PMTargetScene());
   m_tScene->setPixmap(pixmap);
   ui->graphicsView->setScene(m_tScene.data());
}

void PmWindow::on_tabWidget_currentChanged(int index)
{
   const int numTabs = ui->tabWidget->count();
   if(index == numTabs-1)
   {
      addANewTab();
   }
}
