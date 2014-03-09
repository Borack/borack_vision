#include "mvc_targetscene.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

MVCTargetScene::MVCTargetScene(QObject *parent)
 : CustomScene(parent)
 , m_polygon(0)
 , m_pixmap(0)
{
}

QPointF MVCTargetScene::clickLocation() const
{
   return m_targetLocation;
}

void MVCTargetScene::reset()
{
   if(m_pixmap)
   {
      removeItem(m_pixmap);
      m_pixmap = 0;
   }

   if(m_polygon)
   {
      removeItem(m_polygon);
      m_polygon = 0;
   }
}

void MVCTargetScene::drawContour(MVC::Boundary boundary)
{

   reset();
   QPolygonF polygon(boundary);
   m_polygon = addPolygon(polygon,QPen(Qt::blue, 2, Qt::DashDotLine, Qt::RoundCap));
}

void MVCTargetScene::drawFinalPatch(QImage img)
{
   reset();
   QPixmap pixmap = QPixmap::fromImage(img);
   m_pixmap = addPixmap(pixmap);
}

void MVCTargetScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

#ifdef MVC_DEBUG
   m_targetLocation = QPointF(10,10);
   qWarning() << "Running in debug mode. Using hardcoded values for selection and target location!";
#else
   m_targetLocation = mouseEvent->scenePos();
#endif // MVC_DEBUG
   emit runTarget();
}
