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

#ifdef MVC_DEBUG
   m_targetLocation = QPointF(0,0);
   qWarning() << "Running in debug mode. Using hardcoded values for selection and target location!";
#else
   m_targetLocation = mouseEvent->scenePos();
#endif // MVC_DEBUG
   emit runMVCComputation();
}
