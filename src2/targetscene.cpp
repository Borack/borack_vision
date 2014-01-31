#include "targetscene.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

TargetScene::TargetScene(QObject *parent)
 : CustomScene(parent)
 , m_polygon(0)
 , m_pixmap(0)
{
}

QPointF TargetScene::clickLocation() const
{
   return m_targetLocation;
}

void TargetScene::drawContour(MVC::Boundary boundary)
{
   if(m_polygon)
   {
      removeItem(m_polygon);
   }

   QPolygonF polygon(boundary);
   m_polygon = addPolygon(polygon,QPen(Qt::blue, 2, Qt::DashDotLine, Qt::RoundCap));
}

void TargetScene::drawFinalPatch(QImage img)
{
   if(m_pixmap)
   {
      removeItem(m_pixmap);
   }

   QPixmap pixmap = QPixmap::fromImage(img);
   m_pixmap = addPixmap(pixmap);
}

void TargetScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

#ifdef MVC_DEBUG
   m_targetLocation = QPointF(10,10);
   qWarning() << "Running in debug mode. Using hardcoded values for selection and target location!";
#else
   m_targetLocation = mouseEvent->scenePos();
#endif // MVC_DEBUG
   emit runMVCComputation();
}
