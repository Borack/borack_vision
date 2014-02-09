#ifndef MVC_TYPES_HPP
#define MVC_TYPES_HPP

#include <QVector>
#include <QPointF>


#include <opencv2/core/core.hpp>
//#define MVC_DEBUG

#ifdef MVC_DEBUG
const int DEBUG_LENGTH=100;
#endif // MVC_DEBUG

namespace MVC{
typedef QVector<QPointF> Boundary;
typedef std::vector<cv::Point> Contour;
typedef std::vector<Contour> Contours;
}

#endif // MVC_TYPES_HPP
