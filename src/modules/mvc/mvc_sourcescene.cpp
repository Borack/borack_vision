#include "mvc_sourcescene.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPolygonF>
#include <QPen>
#include <QBrush>

MVCSourceScene::MVCSourceScene(QObject *parent)
   : CustomScene(parent)
   , m_polygon(0)
{
}

//-----------------------------------------------------------------------------

MVC::Boundary MVCSourceScene::getBoundary() const
{
   return m_boundary;
}

//-----------------------------------------------------------------------------

void MVCSourceScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
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

//-----------------------------------------------------------------------------

void MVCSourceScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if(event->buttons() != Qt::NoButton)
   {
//      qDebug() << "A button was pressed at: " << event->scenePos();
      m_boundary << event->scenePos();
      drawPolygon();
   }
}

//-----------------------------------------------------------------------------

void MVCSourceScene::mouseReleaseEvent(QGraphicsSceneMouseEvent */*event*/)
{
    qDebug() << "Mouse released";
    emit runSource();
}

//-----------------------------------------------------------------------------

void MVCSourceScene::reset()
{
   m_boundary.clear();
   if(m_polygon)
   {
      removeItem(m_polygon);

   }

   foreach(QGraphicsLineItem* line, m_lines)
   {
      removeItem(line);
   }
   m_lines.clear();
}

//-----------------------------------------------------------------------------

void MVCSourceScene::drawMesh(MVC::Mesh2d::Segments segements)
{
   foreach(QGraphicsLineItem* line, m_lines)
   {
      removeItem(line);
   }
   m_lines.clear();

   foreach(QLineF line, segements)
   {
      m_lines.push_back(addLine(line,QPen(QColor(0,0,0))));
   }
}

//-----------------------------------------------------------------------------

void MVCSourceScene::drawPolygon()
{
   if(m_polygon)
   {
      removeItem(m_polygon);

   }

   QPolygonF polygon(m_boundary);
   m_polygon = addPolygon(polygon,QPen(Qt::green, 5, Qt::DashDotLine, Qt::RoundCap));
}

//-----------------------------------------------------------------------------
