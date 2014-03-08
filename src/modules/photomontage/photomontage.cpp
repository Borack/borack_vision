#include "photomontage.hpp"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <converter.hpp>

#include <GCoptimization.h>


struct ForSmoothness
{
   cv::Mat* mat;
};

GCoptimization::EnergyTermType SmoothCostFn(GCoptimization::SiteID site1, GCoptimization::SiteID s2, GCoptimization::LabelID l1, GCoptimization::LabelID l2, void* forSmoothness)
{
   if(l1 == l2) return 0;
   else return 1;
}

//-----------------------------------------------------------------------------
PhotoMontage::PhotoMontage(const QPixmap &pixmap, QObject *parent)
   : m_inputSource(pixmap)
   , QObject(parent)
{
   setupGraphCut();
}

//-----------------------------------------------------------------------------
void PhotoMontage::setupGraphCut()
{
   QImage qImg = m_inputSource.toImage();
   cv::Mat cvMat = Converter::QImageToCvMat(qImg);
   cv::Mat colorMat;
   cv::resize(cvMat, colorMat, cv::Size(0,0), 0.25, 0.25);

   const int num_labels = 5;
   GCoptimizationGridGraph* gc = new GCoptimizationGridGraph(colorMat.cols, colorMat.rows, num_labels);
   gc->setVerbosity(2);
   qDebug() << "Graph is setup";

   cv::Mat gray;
   cv::cvtColor(colorMat, gray, CV_BGR2GRAY);

   const int num_pixels = gc->numSites();

   // setup the data cost!
   const float threshold = 255.0f / num_labels;
   for ( int i = 0; i < num_pixels; i++ )
   {

      for (int l = 0; l < num_labels; l++ )
      {
         int r = i / gray.cols;
         int c = i % gray.cols;
         uchar colValue = gray.at<uchar>(r,c);
         int properLabel = colValue / threshold;

         if(l == properLabel)    gc->setDataCost(i,l,0);
         else                    gc->setDataCost(i,l,1);

      }
   }

   ForSmoothness forSmoothness;
   forSmoothness.mat = &gray;

   gc->setSmoothCost(&SmoothCostFn, &forSmoothness);

   qDebug() << "\nBefore optimization energy is %d" << gc->compute_energy();
   gc->expansion(1);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
   qDebug() << "\nAfter optimization energy is %d" << gc->compute_energy();


   cv::Mat out(gray.size(), CV_8UC1);
   for ( int  i = 0; i < num_pixels; i++ )
   {
      int r = i / gray.cols;
      int c = i % gray.cols;
      int label = gc->whatLabel(i);
      out.at<uchar>(r,c) = label*threshold;
   }

   cv::imwrite("yees-a-gc-image.png", out);
}


