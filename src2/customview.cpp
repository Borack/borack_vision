#include "customview.hpp"
#include <QGLWidget>

#include <QDebug>
#include <QMouseEvent>

CustomView::CustomView(QWidget* parent)
   : QGraphicsView(parent)
{
   setupViewport(new QGLWidget(this));
}

void CustomView::mousePressEvent(QMouseEvent *mouseEvent)
{
   QGraphicsView::mousePressEvent(mouseEvent);

//   qDebug() << "Button down pos: " << mouseEvent->pos();
////   qDebug() << "Button down scene pos: " << mouseEvent->buttonDownScenePos(Qt::AllButtons);
//   qDebug() << "Button down screen pos: " << mouseEvent->screenPos();
//   qDebug() << "\n";
}
