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
      const float length = 100;
      m_boundary << QPointF(0,0);
      m_boundary << QPointF(0,length);
      m_boundary << QPointF(length,length);
      m_boundary << QPointF(length,0);
#else
   m_boundary << mouseEvent->scenePos();
#endif

   drawPolygon();
}

void SourceScene::reset()
{
   m_boundary.clear();
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
