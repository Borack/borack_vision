#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>

#include <QImage>
#include <QPixmap>

#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/nonfree.hpp>


typedef std::vector<QImage> QImages;
typedef std::vector<QPixmap> QPixmaps;
typedef std::vector<cv::Mat> Mats;
typedef std::vector<cv::KeyPoint> KeyPoints;
typedef std::vector<KeyPoints> VectorOfKeypoints;


#endif // TYPES_HPP
