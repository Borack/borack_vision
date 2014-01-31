#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <QImage>
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
     * @brief QImageToCvMat conversion functions. Allocates new memory
     *
     */
    static QImage CvMatToQImage(const cv::Mat& cvMat);


    static Eigen::Vector3i CvVec3bToEigenVec3i(const cv::Vec3b &vec);
    static Eigen::Vector3f CvVec3bToEigenVec3f(const cv::Vec3b &vec);

};

#endif // CONVERTER_HPP
