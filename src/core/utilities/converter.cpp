#include "converter.hpp"
#include <QDebug>


cv::Mat Converter::QImageToCvMat(QImage &qImage)
{
    switch(qImage.depth())
    {
    case 32:
    {
        // just a wrapper around the data pointer around qImage
        cv::Mat tmp(qImage.height(), qImage.width(), CV_8UC4);
        tmp.step = qImage.bytesPerLine();
        tmp.data = qImage.bits();

        // Deep copy the data and return the cv::mat.
        return tmp.clone();
        break;
    }
    default:
    {
        qWarning() << "Conversion for this image depth not yet implemented." << Q_FUNC_INFO;
        return cv::Mat();
    }
    }

}

cv::Mat Converter::QPixmapToCvMatToCvMat(QPixmap &qPixmap)
{
   QImage qImage = qPixmap.toImage();
   return QImageToCvMat(qImage);
}

QImage Converter::CvMatToQImage(const cv::Mat &cvMat)
{
    if(cvMat.depth() == CV_8U
            && cvMat.channels() == 4)
    {
        // Same procedure here. First a wrapper around the data in cvMat
        QImage tmp(cvMat.data, cvMat.cols, cvMat.rows, cvMat.step, QImage::Format_ARGB32);

        // And then clone the data and return that QImage:
        return tmp.copy();
    }
    else
    {
        qWarning() << "Conversion for this image depth not yet implemented." << Q_FUNC_INFO;
        return QImage();
    }
}

Eigen::Vector4i Converter::CvVec4bToEigenVec4i(const cv::Vec4b &vec)
{
   Eigen::Vector4i out;
   out[0] = vec[0];
   out[1] = vec[1];
   out[2] = vec[2];
   out[3] = vec[3];
   return out;
}

Eigen::Vector4f Converter::CvVec4sbToEigenVec4f(const cv::Vec4b &vec)
{
   Eigen::Vector4f out;
   out[0] = vec[0];
   out[1] = vec[1];
   out[2] = vec[2];
   out[3] = vec[3];
   return out;

}
