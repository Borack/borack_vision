#include "customview.hpp"
#include <QGLWidget>

#include <QDebug>
#include <QMouseEvent>

CustomView::CustomView(QWidget* parent)
   : QGraphicsView(parent)
{
   setupViewport(new QGLWidget(this));
}

void CustomView::resizeEvent(QResizeEvent *event)
{
   QGraphicsView::resizeEvent(event);
   fitInView(sceneRect(), Qt::KeepAspectRatio);
}

