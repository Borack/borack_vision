#ifndef MEANVALUE_SEAMLESS_CLONING_HPP
#define MEANVALUE_SEAMLESS_CLONING_HPP

#include <QObject>
#include <QPixmap>

#include <opencv2/core/core.hpp>

#include "mvc_types.hpp"

class MeanValueSeamlessCloning : public QObject
{
   Q_OBJECT
public:
   explicit MeanValueSeamlessCloning(const QPixmap &pixmap, const MVC::Boundary & _b, QObject *parent = 0);
   void startComputation();

signals:

public slots:


private:

   void calculateMVCValues();

   const QPixmap m_inputSource;
   const MVC::Boundary m_sourceBoundary;

   cv::Mat m_cvInputFull;
   cv::Mat m_inputSub;
   cv::Mat m_patch;

};

#endif // MEANVALUE_SEAMLESS_CLONING_HPP
