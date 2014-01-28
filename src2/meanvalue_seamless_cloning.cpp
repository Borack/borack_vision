#include "meanvalue_seamless_cloning.hpp"
#include "converter.hpp"


#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include <cmath>

MeanValueSeamlessCloning::MeanValueSeamlessCloning(const QPixmap &pixmap, const MVC::Boundary &b, const QPixmap &tPixmap, const QPointF &clickLoc, QObject *parent)
   : QObject(parent)
   , m_inputSource(pixmap)
   , m_sourceBoundary(b)
   , m_inputTarget(tPixmap)
   , m_targetClickLocation(clickLoc)
{
}

void MeanValueSeamlessCloning::startComputation()
{
   //! Convert to cv::Mat
   QImage img = m_inputSource.toImage();
   m_cvSourceFull = Converter::QImageToCvMat(img);


   //! Get a cv contour
   std::vector<std::vector<cv::Point> > contours;

   foreach (QPointF point, m_sourceBoundary)
   {
      m_contour.push_back(cv::Point(point.x(), point.y()));
   }
   contours.push_back(m_contour);


   //! Create mask for patch
   cv::Mat mask = cv::Mat::zeros(m_cvSourceFull.size(), CV_8UC1);
   cv::drawContours(mask,contours,-1,cv::Scalar(255), CV_FILLED);

   //! Copy to full image but only where mask is
   cv::Mat roiInFullContext;
   m_cvSourceFull.copyTo(roiInFullContext,mask);

   //! Get convex hull of the contour
   //! Create the patch;
   cv::Rect boundingBox = cv::boundingRect(m_contour);
   m_patch = roiInFullContext(boundingBox);


   assert(m_patch.cols > 0 && m_patch.rows > 0);
   assert(m_contour.size() > 0);


   m_translatedContour.reserve(m_contour.size());
   for(int boundaryVerPos = 0; boundaryVerPos < m_contour.size(); boundaryVerPos++)
   {
      cv::Point p(m_contour[boundaryVerPos].x-boundingBox.x, m_contour[boundaryVerPos].y-boundingBox.y);
      assert(p.x >= 0);
      assert(p.y >= 0);
      assert(p.x < boundingBox.width);
      assert(p.y < boundingBox.height);
      m_translatedContour.push_back(p);
   }
   assert(m_contour.size() == m_translatedContour.size());

   //! calculate mv coordinates for each interior coordinate.
   m_patchMVCCoords.reserve(m_sourceBoundary.size());
   for(int c = 0; c< m_patch.cols; c++)
   {
      for(int r = 0; r< m_patch.rows; r++)
      {
         cv::Point interiorPoint(c+boundingBox.x,r+boundingBox.y);
         if(cv::pointPolygonTest(m_contour,interiorPoint,false) > 0) //! returns positive when inside, negative when outside and zero if on edge.
         {
            MVCoord mvcoord = calculateMVCValues(interiorPoint);
            m_patchMVCCoords.push_back(std::make_pair(interiorPoint, mvcoord));
         }

      }
   }


   cv::namedWindow( "Source BB", cv::WINDOW_AUTOSIZE );
   cv::imshow("Source BB", m_patch);
//   cv::waitKey(0);
//   cv::destroyWindow("Source BB");



   //////////////////////////////////////////////////////////////////////////////////////
   //!! Up to here it was pre-processing. From here on it depends on the target image ///
   //////////////////////////////////////////////////////////////////////////////////////


   QImage imgT = m_inputTarget.toImage();
   m_cvTargetFull = Converter::QImageToCvMat(imgT);

   assert(m_contour.size() == m_translatedContour.size());
   m_targetContour.reserve(m_translatedContour.size());
   for(int boundaryVerPos = 0; boundaryVerPos < m_translatedContour.size(); boundaryVerPos++)
   {
      cv::Point p(m_translatedContour[boundaryVerPos].x+m_targetClickLocation.x(), m_translatedContour[boundaryVerPos].y+m_targetClickLocation.y());


      if(p.x < 0)
         p.x = 0;
      else if(p.y < 0)
         p.y = 0;

      if(p.x >= m_cvTargetFull.cols)
         p.x = m_cvTargetFull.cols-1;
      else if(p.y >= m_cvTargetFull.rows)
         p.y = m_cvTargetFull.rows-1;

      m_targetContour.push_back(p);
   }
   assert(m_translatedContour.size() == m_targetContour.size());

   emit targetContourCalculated(getBoundary(m_targetContour));

   cv::Mat targetMask = cv::Mat::zeros(m_cvTargetFull.size(),CV_8UC1);
   std::vector<std::vector<cv::Point> > tmp;
   tmp.push_back(m_targetContour);

   cv::drawContours(targetMask,tmp,-1 ,cv::Scalar(255), CV_FILLED);
   cv::Mat onlyMaskCopied;
   m_cvTargetFull.copyTo(onlyMaskCopied,targetMask);

   cv::Rect targetBB = cv::boundingRect(m_targetContour);

   cv::Mat targetPatch = onlyMaskCopied(targetBB);


   cv::namedWindow( "Target BB", cv::WINDOW_AUTOSIZE );
   cv::imshow("Target BB", targetPatch);
   cv::waitKey(0);
   cv::destroyAllWindows();

}

MeanValueSeamlessCloning::MVCoord MeanValueSeamlessCloning::calculateMVCValues(const cv::Point &interiorPoint)
{

   const Eigen::Vector2f point(interiorPoint.x, interiorPoint.y);

   Weights weights;
   weights.reserve(m_translatedContour.size());  //! contains the w_i
   assert(weights.size() == 0);
   double w_total = 0.0f;

   for(int boundaryVerPos = 0; boundaryVerPos < m_translatedContour.size(); boundaryVerPos++)
   {
      int boundaryVerPos_before = boundaryVerPos == 0 ? m_translatedContour.size()-1 : boundaryVerPos - 1;
      int boundaryVerPos_after = boundaryVerPos == m_translatedContour.size()-1 ? 0 : boundaryVerPos + 1;

      Eigen::Vector2f boundaryVertex_i(m_translatedContour[boundaryVerPos].x, m_translatedContour[boundaryVerPos].y);
      Eigen::Vector2f boundaryVertex_i_minus_1(m_translatedContour[boundaryVerPos_before].x, m_translatedContour[boundaryVerPos_before].y);
      Eigen::Vector2f boundaryVertex_i_plus_1(m_translatedContour[boundaryVerPos_after].x, m_translatedContour[boundaryVerPos_after].y);

//      qDebug() << "boundaryVertex_i" << boundaryVertex_i(0) << " " << boundaryVertex_i(1);
//      qDebug() << "boundaryVertex_i_minus_1" << boundaryVertex_i_minus_1(0) << " " << boundaryVertex_i_minus_1(1);
//      qDebug() << "point" << point(0) << " " << point(1);

      Eigen::Vector2f vec_i_plus_1 = (point - boundaryVertex_i_plus_1).normalized();
      Eigen::Vector2f vec_i = (point - boundaryVertex_i).normalized();
      Eigen::Vector2f vec_i_minus_1 = (point - boundaryVertex_i_minus_1).normalized();

      double a1 = std::acos(vec_i_plus_1.dot(vec_i));
      double a2 = std::acos(vec_i_minus_1.dot(vec_i));

      double angle = (std::tan(a1/2.0) + std::tan(a2/2.0));
      double normedDist = (point - boundaryVertex_i).norm();

      double w_i = angle / normedDist;
      weights.push_back(w_i);

      w_total += w_i;

//      qDebug() << "The angle1 is: " << a1;
//      qDebug() << "The angle2 is: " << a2;
//      qDebug() << "The total angle is: " << angle;
//      qDebug() << "The normedDist is: " << normedDist;
//      qDebug() << "The weight is: " << w_i;
   }

   MVCoord mvc;
   mvc.reserve(m_translatedContour.size());
   for(int boundaryVerPos = 0; boundaryVerPos < m_translatedContour.size(); boundaryVerPos++)
   {
      mvc.push_back(weights[boundaryVerPos] / w_total);
   }
   assert(mvc.size() == m_translatedContour.size());
   return mvc;
}

MVC::Boundary MeanValueSeamlessCloning::getBoundary(const std::vector<cv::Point> &contour)
{
   MVC::Boundary out;
   out.reserve(contour.size());
   for(int i = 0; i< contour.size(); i++)
   {
      out.push_back(QPointF(contour[i].x, contour[i].y));
   }
   assert(out.size() == contour.size());
   return out;
}
