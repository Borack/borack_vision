#ifndef MEANVALUE_SEAMLESS_CLONING_HPP
#define MEANVALUE_SEAMLESS_CLONING_HPP

#include <QObject>
#include <QPixmap>
#include <QPointF>

#include <opencv2/core/core.hpp>

#include "mvc_types.hpp"

class MeanValueSeamlessCloning : public QObject
{
   Q_OBJECT
public:
   explicit MeanValueSeamlessCloning(const QPixmap &pixmap, const MVC::Boundary & _b, const QPixmap &tPixmap, const QPointF &clickLoc, QObject *parent = 0);
   void startComputation();

signals:
   void targetContourCalculated(MVC::Boundary contour);

public slots:


private:

   typedef std::vector<double> Weights;
   typedef Weights MVCoord;
   typedef std::vector<std::pair<cv::Point, MVCoord> > AllMVCoords;

   MVCoord calculateMVCValues(const cv::Point &interiorPoint);
   MVC::Boundary getBoundary(const std::vector<cv::Point> &contour);


   // inputs
   const QPixmap m_inputSource;
   const MVC::Boundary m_sourceBoundary;
   const QPixmap m_inputTarget;
   const QPointF m_targetClickLocation;

   cv::Mat m_cvSourceFull;
   cv::Mat m_inputSub;
   cv::Mat m_cvTargetFull;

   std::vector<cv::Point> m_contour;           //! This is the original contour in the source image
   std::vector<cv::Point> m_translatedContour; //! This is the translated contour in the convex hull space.
   std::vector<cv::Point> m_targetContour;     //! This is the contour in the target image. Based on the clicked location.
   cv::Mat m_patch;

   AllMVCoords m_patchMVCCoords;
};

#endif // MEANVALUE_SEAMLESS_CLONING_HPP
