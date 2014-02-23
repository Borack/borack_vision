#ifndef CONVERTER_HPP
#define CONVERTER_HPP

#include <QImage>
#include <opencv2/core/core.hpp>

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
};

#endif // CONVERTER_HPP
