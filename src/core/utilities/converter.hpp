#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>

#include <Eigen/Core>

class Converter
{
public:

    /**
     * @brief QImageToCvMat conversion functions. Allocates new memory
     */
    static cv::Mat QImageToCvMat(QImage &qImage);

    /**
     * @brief QPixmapToCvMat conversion functions. Allocates new memory
     */
    static cv::Mat QPixmapToCvMat(QPixmap &qPixmap);


    /**
     * @brief CvMatToQImage conversion functions. Allocates new memory
     *
     */
    static QImage CvMatToQImage(const cv::Mat& cvMat);

    /**
     * @brief CvMatToQPixmap conversion functions. Allocates new memory
     *
     */
    static QPixmap CvMatToQPixmap(const cv::Mat& cvMat);


    static Eigen::Vector4i CvVec4bToEigenVec4i(const cv::Vec4b &vec);
    static Eigen::Vector4f CvVec4sbToEigenVec4f(const cv::Vec4b &vec);

};

#endif // CONVERTER_HPP
