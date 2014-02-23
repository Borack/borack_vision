#ifndef MEANVALUE_SEAMLESS_CLONING_HPP
#define MEANVALUE_SEAMLESS_CLONING_HPP

#include <QObject>
#include <QPixmap>
#include <QPointF>

#include <eigen3/Eigen/Core>

#include <opencv2/core/core.hpp>

#include "mvc_types.hpp"
#include "mesh2d.hpp"

class MeanValueSeamlessCloning : public QObject
{
   Q_OBJECT
public:
//   explicit MeanValueSeamlessCloning(const QPixmap &pixmap, const MVC::Boundary & b, const QPixmap &tPixmap, const QPointF &clickLoc, QObject *parent = 0);
   explicit MeanValueSeamlessCloning(const QPixmap &pixmap, const QPixmap &tPixmap, QObject *parent = 0);

   void startSourceComputation(const MVC::Boundary & b);
   void startTargetComputation(const QPointF &clickLoc);

signals:
   void targetContourCalculated(MVC::Boundary contour);
   void displayFinalPatch(QImage finalPatch);
   void displayMesh(MVC::Mesh2d::Segments vertices);

public slots:


private:

   typedef std::vector<double> Weights;
   typedef Weights MVCoord;
   typedef std::vector<std::pair<cv::Point, MVCoord> > AllMVCoords;

   MVCoord calculateMVCValues(const cv::Point &interiorPoint);
   MVC::Boundary getBoundary(const std::vector<cv::Point> &contour);


   // inputs
   const QPixmap m_inputSource;
   const QPixmap m_inputTarget;

   MVC::Boundary m_sourceBoundary;
   QPointF m_targetClickLocation;

   cv::Mat m_cvSourceFull;
   cv::Mat m_inputSub;
   cv::Mat m_cvTargetFull;

   MVC::Contour m_contourSourceSpace;           //! This is the original contour in the source image
   MVC::Contour m_contourPatchSpace; //! This is the translated contour in the convex hull space.
   MVC::Contour m_contourTargetSpace;     //! This is the contour in the target image. Based on the clicked location.
   cv::Mat m_sourcePatch;

   AllMVCoords m_patchMVCCoords;

   std::vector<Eigen::Vector4i> m_colorDifferences;
};

#endif // MEANVALUE_SEAMLESS_CLONING_HPP
