#include "meanvalue_seamless_cloning.hpp"
#include "converter.hpp"

#include <QDebug>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

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
   std::vector<cv::Point> aContour;

   foreach (QPointF point, m_sourceBoundary)
   {
      aContour.push_back(cv::Point(point.x(), point.y()));
   }
   contours.push_back(aContour);


   //! Create mask for patch
   cv::Mat mask = cv::Mat::zeros(m_cvInputFull.size(), CV_8UC1);

   cv::drawContours(mask,contours,-1,cv::Scalar(255), CV_FILLED);

   //! Get convex hull of the contour
   cv::Rect convexHull = cv::boundingRect(aContour);


   cv::namedWindow( "Display window", cv::WINDOW_AUTOSIZE );
   cv::imshow("Display window", mask);
   cv::waitKey(0);
   cv::destroyAllWindows();


   //! Compute all the pixels inside the patch
}
