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

Eigen::Vector3i Converter::CvVec3bToEigenVec3i(const cv::Vec3b &vec)
{
   Eigen::Vector3i out;
   out[0] = vec[0];
   out[1] = vec[1];
   out[2] = vec[2];
   return out;
}

Eigen::Vector3f Converter::CvVec3bToEigenVec3f(const cv::Vec3b &vec)
{
   Eigen::Vector3f out;
   out[0] = vec[0];
   out[1] = vec[1];
   out[2] = vec[2];
   return out;

}
