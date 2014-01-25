#include "customview.hpp"
#include <QGLWidget>

CustomView::CustomView(QWidget* parent)
   : QGraphicsView(parent)
{
   setupViewport(new QGLWidget(this));
}
