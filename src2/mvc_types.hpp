#ifndef MVC_TYPES_HPP
#define MVC_TYPES_HPP

#include <QVector>
#include <QPointF>

//#define MVC_DEBUG

#ifdef MVC_DEBUG
const int DEBUG_LENGTH=100;
#endif // MVC_DEBUG

namespace MVC{
typedef QVector<QPointF> Boundary;
}

#endif // MVC_TYPES_HPP
