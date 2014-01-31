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
      m_contourSourceSpace.push_back(cv::Point(point.x(), point.y()));
   }
   contours.push_back(m_contourSourceSpace);


   //! Create mask for patch
   cv::Mat mask = cv::Mat::zeros(m_cvSourceFull.size(), CV_8UC1);
   cv::drawContours(mask,contours,-1,cv::Scalar(255), CV_FILLED);

   //! Copy to full image but only where mask is
   cv::Mat roiInFullContext;
   m_cvSourceFull.copyTo(roiInFullContext,mask);

   //! Get convex hull of the contour
   //! Create the patch;
   cv::Rect boundingBox = cv::boundingRect(m_contourSourceSpace);
   m_sourcePatch = roiInFullContext(boundingBox);


   assert(m_sourcePatch.cols > 0 && m_sourcePatch.rows > 0);
   assert(m_contourSourceSpace.size() > 0);


   m_contourPatchSpace.reserve(m_contourSourceSpace.size());
   for(int boundaryVerPos = 0; boundaryVerPos < m_contourSourceSpace.size(); boundaryVerPos++)
   {
      cv::Point p(m_contourSourceSpace[boundaryVerPos].x-boundingBox.x, m_contourSourceSpace[boundaryVerPos].y-boundingBox.y);
      assert(p.x >= 0);
      assert(p.y >= 0);
      assert(p.x < boundingBox.width);
      assert(p.y < boundingBox.height);
      m_contourPatchSpace.push_back(p);
   }
   assert(m_contourSourceSpace.size() == m_contourPatchSpace.size());

   //! calculate mv coordinates for each interior coordinate.
   for(int c = 0; c< m_sourcePatch.cols; c++)
   {
      for(int r = 0; r< m_sourcePatch.rows; r++)
      {
         cv::Point interiorPoint(c,r);
         if(cv::pointPolygonTest(m_contourPatchSpace,interiorPoint,false) > 0) //! returns positive when inside, negative when outside and zero if on edge.
         {
            MVCoord mvcoord = calculateMVCValues(interiorPoint);
            m_patchMVCCoords.push_back(std::make_pair(interiorPoint, mvcoord));
         }

      }
   }


   cv::namedWindow( "Source BB", cv::WINDOW_AUTOSIZE );
   cv::imshow("Source BB", m_sourcePatch);
//   cv::waitKey(0);
//   cv::destroyWindow("Source BB");



   //////////////////////////////////////////////////////////////////////////////////////
   //!! Up to here it was pre-processing. From here on it depends on the target image ///
   //////////////////////////////////////////////////////////////////////////////////////


   QImage imgT = m_inputTarget.toImage();
   m_cvTargetFull = Converter::QImageToCvMat(imgT);

   assert(m_contourSourceSpace.size() == m_contourPatchSpace.size());
   m_contourTargetSpace.reserve(m_contourPatchSpace.size());
   for(int boundaryVerPos = 0; boundaryVerPos < m_contourPatchSpace.size(); boundaryVerPos++)
   {
      cv::Point p(m_contourPatchSpace[boundaryVerPos].x+m_targetClickLocation.x(), m_contourPatchSpace[boundaryVerPos].y+m_targetClickLocation.y());

      if(p.x < 0)
         p.x = 0;
      else if(p.y < 0)
         p.y = 0;

      if(p.x >= m_cvTargetFull.cols)
         p.x = m_cvTargetFull.cols-1;
      else if(p.y >= m_cvTargetFull.rows)
         p.y = m_cvTargetFull.rows-1;

      m_contourTargetSpace.push_back(p);
   }
   assert(m_contourPatchSpace.size() == m_contourTargetSpace.size());

   emit targetContourCalculated(getBoundary(m_contourTargetSpace));

   cv::Mat targetMask = cv::Mat::zeros(m_cvTargetFull.size(),CV_8UC1);
   std::vector<std::vector<cv::Point> > tmp;
   tmp.push_back(m_contourTargetSpace);

   cv::drawContours(targetMask,tmp,-1 ,cv::Scalar(255), CV_FILLED);
   cv::Mat onlyMaskCopied;
   m_cvTargetFull.copyTo(onlyMaskCopied,targetMask);

   cv::Rect targetBB = cv::boundingRect(m_contourTargetSpace);

   cv::Mat targetPatch = onlyMaskCopied(targetBB);


   cv::namedWindow( "Target BB", cv::WINDOW_AUTOSIZE );
   cv::imshow("Target BB", targetPatch);
   cv::waitKey(0);
   cv::destroyAllWindows();


   //! Compute the differences along the boundary.
   assert(m_contourTargetSpace.size() == m_contourSourceSpace.size());
   assert(m_contourTargetSpace.size() == m_contourPatchSpace.size());
   m_colorDifferences.reserve(m_contourTargetSpace.size());
   for(int i = 0; i < m_contourSourceSpace.size(); i++ )
   {
      Eigen::Vector3i sourceIntensity = Converter::CvVec3bToEigenVec3i( m_cvSourceFull.at<cv::Vec3b>(m_contourSourceSpace[i]));
      Eigen::Vector3i targetIntensity = Converter::CvVec3bToEigenVec3i(m_cvTargetFull.at<cv::Vec3b>(m_contourTargetSpace[i]));

      Eigen::Vector3i sourcePatchIntensity = Converter::CvVec3bToEigenVec3i(m_sourcePatch.at<cv::Vec3b>(m_contourPatchSpace[i]));
      Eigen::Vector3i targetPatchIntensity = Converter::CvVec3bToEigenVec3i(targetPatch.at<cv::Vec3b>(m_contourPatchSpace[i]));


      Eigen::Vector3i diff = targetIntensity - sourceIntensity;
      Eigen::Vector3i diff2 = targetPatchIntensity - sourcePatchIntensity;
      assert(diff == diff2); // FIXME: the two differences are not the same. We should fix this!

      m_colorDifferences.push_back(diff);
   }
   assert(m_colorDifferences.size() == m_contourPatchSpace.size());

   //! calculate mv coordinates for each interior coordinate.
   cv::Mat finalPatch = targetPatch.clone();
   for(int i = 0; i< m_patchMVCCoords.size(); i++)
   {
      const cv::Point& pointInPatchSpace = m_patchMVCCoords[i].first;

      Eigen::Vector3f r;
      for(int v=0; v<m_contourPatchSpace.size();v++)
      {
         for(int channel = 0; channel <3; channel++)
         {
            r[channel] += m_patchMVCCoords[i].second[v] * m_colorDifferences[v][channel];
         }
      }

      Eigen::Vector3f sourceIntensity = Converter::CvVec3bToEigenVec3f(m_sourcePatch.at<cv::Vec3b>(pointInPatchSpace));

      Eigen::Vector3f finalColor = sourceIntensity + r;

      finalPatch.at<cv::Vec3b>(pointInPatchSpace)[0] = finalColor[0];
      finalPatch.at<cv::Vec3b>(pointInPatchSpace)[1] = finalColor[1];
      finalPatch.at<cv::Vec3b>(pointInPatchSpace)[2] = finalColor[2];

   }

   cv::namedWindow( "Final Patch", cv::WINDOW_AUTOSIZE );
   cv::imshow("Final Patch", finalPatch);
   cv::waitKey(0);
   cv::destroyAllWindows();

}

MeanValueSeamlessCloning::MVCoord MeanValueSeamlessCloning::calculateMVCValues(const cv::Point &interiorPoint)
{

   const Eigen::Vector2f point(interiorPoint.x, interiorPoint.y);

   Weights weights;
   weights.reserve(m_contourPatchSpace.size());  //! contains the w_i
   assert(weights.size() == 0);
   double w_total = 0.0f;

   for(int boundaryVerPos = 0; boundaryVerPos < m_contourPatchSpace.size(); boundaryVerPos++)
   {
      int boundaryVerPos_before = boundaryVerPos == 0 ? m_contourPatchSpace.size()-1 : boundaryVerPos - 1;
      int boundaryVerPos_after = boundaryVerPos == m_contourPatchSpace.size()-1 ? 0 : boundaryVerPos + 1;

      Eigen::Vector2f boundaryVertex_i(m_contourPatchSpace[boundaryVerPos].x, m_contourPatchSpace[boundaryVerPos].y);
      Eigen::Vector2f boundaryVertex_i_minus_1(m_contourPatchSpace[boundaryVerPos_before].x, m_contourPatchSpace[boundaryVerPos_before].y);
      Eigen::Vector2f boundaryVertex_i_plus_1(m_contourPatchSpace[boundaryVerPos_after].x, m_contourPatchSpace[boundaryVerPos_after].y);

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
   mvc.reserve(m_contourPatchSpace.size());
   for(int boundaryVerPos = 0; boundaryVerPos < m_contourPatchSpace.size(); boundaryVerPos++)
   {
      mvc.push_back(weights[boundaryVerPos] / w_total);
   }
   assert(mvc.size() == m_contourPatchSpace.size());
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
