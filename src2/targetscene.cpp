#include "targetscene.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

TargetScene::TargetScene(QObject *parent)
 : CustomScene(parent)
 , m_polygon(0)
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
   m_polygon = addPolygon(polygon,QPen(Qt::blue, 20, Qt::DashDotLine, Qt::RoundCap));
}

void TargetScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   m_targetLocation = mouseEvent->scenePos();
   emit runMVCComputation();
}
