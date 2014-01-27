#include "meanvalue_seamless_cloning.hpp"
#include "converter.hpp"


#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <cmath>

MeanValueSeamlessCloning::MeanValueSeamlessCloning(const QPixmap &pixmap, const MVC::Boundary &b, QObject *parent)
   :  QObject(parent)
   ,  m_inputSource(pixmap)
   , m_sourceBoundary(b)
{

}

void MeanValueSeamlessCloning::startComputation()
{
   //! Convert to cv::Mat
   QImage img = m_inputSource.toImage();
   m_cvInputFull = Converter::QImageToCvMat(img);


   //! Get a cv contour
   std::vector<std::vector<cv::Point> > contours;

   foreach (QPointF point, m_sourceBoundary)
   {
      m_contour.push_back(cv::Point(point.x(), point.y()));
   }
   contours.push_back(m_contour);


   //! Create mask for patch
   cv::Mat mask = cv::Mat::zeros(m_cvInputFull.size(), CV_8UC1);
   cv::drawContours(mask,contours,-1,cv::Scalar(255), CV_FILLED);

   //! Get convex hull of the contour
   cv::Mat roiInFullContext;
   m_cvInputFull.copyTo(roiInFullContext,mask);
   cv::Rect convexHull = cv::boundingRect(m_contour);

   //! Create the patch;
   m_patch = roiInFullContext(convexHull);



   assert(m_patch.cols > 0 && m_patch.rows > 0);
   assert(m_contour.size() > 0);

   for(int c = 0; c< m_patch.cols; c++)
   {
      for(int r = 0; r< m_patch.rows; r++)
      {
         cv::Point interiorPoint(c,r);
         if(!cv::pointPolygonTest(m_contour,interiorPoint,false))
         {
            continue;
         }

         calculateMVCValues(interiorPoint);
      }
   }

   Eigen::Vector2f a(0,1);
   Eigen::Vector2f b(1,0);

   float angle = std::acos(b.dot(a));
   qDebug() << "The angle is: " << angle ;

   qDebug() << "Normed combination: " << (a+b).norm();


   cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
   cv::imshow("Display window", m_patch);
   cv::waitKey(0);
   cv::destroyAllWindows();


   //! Compute all the pixels inside the patch
}

void MeanValueSeamlessCloning::calculateMVCValues(const cv::Point &interiorPoint)
{

   const Eigen::Vector2f point(interiorPoint.x, interiorPoint.y);

   for(int boundaryVerPos = 0; boundaryVerPos < m_contour.size(); boundaryVerPos++)
   {
      int boundaryVerPos_before = boundaryVerPos == 0 ? m_contour.size()-1 : boundaryVerPos - 1;

      Eigen::Vector2f boundaryVertex_i(m_contour[boundaryVerPos].x, m_contour[boundaryVerPos].y);
      Eigen::Vector2f boundaryVertex_i_minus_1(m_contour[boundaryVerPos_before].x, m_contour[boundaryVerPos_before].y);

      float w_i = (std::atan(std::acos(boundaryVertex_i_minus_1.dot(point))/2.0f) + std::atan(std::acos(boundaryVertex_i.dot(point))/2.0f)) / (point - boundaryVertex_i).norm();
      qDebug() << "The weight is: " << w_i;
   }
}
