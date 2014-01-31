#include "sourcescene.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>
#include <QPen>
#include <QBrush>

SourceScene::SourceScene(QObject *parent)
   : CustomScene(parent)
   , m_polygon(0)
{
}

MVC::Boundary SourceScene::getBoundary() const
{
   return m_boundary;
}

void SourceScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   //   qDebug() << "Button down pos: " << mouseEvent->buttonDownPos(Qt::AllButtons);
   //   qDebug() << "Button down scene pos: " << mouseEvent->buttonDownScenePos(Qt::AllButtons);
   //   qDebug() << "Button down screen pos: " << mouseEvent->buttonDownScreenPos(Qt::AllButtons);
   //   qDebug() << "Pos: " << mouseEvent->pos();
//      qDebug() << "Scene pos: " << mouseEvent->scenePos();
   //   qDebug() << "Screen pos: " << mouseEvent->screenPos();
   //   qDebug() << "";


#ifdef MVC_DEBUG
      m_boundary.clear();
      m_boundary << QPointF(0,0);
      m_boundary << QPointF(0,DEBUG_LENGTH-1);
      m_boundary << QPointF(DEBUG_LENGTH-1,DEBUG_LENGTH-1);
      m_boundary << QPointF(DEBUG_LENGTH-1,0);
#else
   m_boundary << mouseEvent->scenePos();
#endif

   drawPolygon();
}

void SourceScene::reset()
{
   m_boundary.clear();
   if(m_polygon)
   {
      removeItem(m_polygon);

   }
}

void SourceScene::drawPolygon()
{
   if(m_polygon)
   {
      removeItem(m_polygon);

   }

   QPolygonF polygon(m_boundary);
   m_polygon = addPolygon(polygon,QPen(Qt::green, 20, Qt::DashDotLine, Qt::RoundCap));
}
