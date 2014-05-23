#include "pm_sourcescene.hpp"
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

//-----------------------------------------------------------------------------
PMSourceScene::PMSourceScene(QObject *parent)
   : CustomScene(parent)
   , m_pathMode(EPathMode_Curve)
{
}

//-----------------------------------------------------------------------------
void PMSourceScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   m_currentStroke.clear();
//   qDebug() << "Button down pos: " << mouseEvent->buttonDownPos(Qt::AllButtons);
//   qDebug() << "Button down scene pos: " << mouseEvent->buttonDownScenePos(Qt::AllButtons);
//   qDebug() << "Button down screen pos: " << mouseEvent->buttonDownScreenPos(Qt::AllButtons);
//   qDebug() << "Pos: " << mouseEvent->pos();
//   qDebug() << "Scene pos: " << mouseEvent->scenePos();
//   qDebug() << "Screen pos: " << mouseEvent->screenPos();
//   qDebug() << "";
}

//-----------------------------------------------------------------------------
void PMSourceScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if(event->buttons() != Qt::NoButton)
   {
//      qDebug() << "Scene pos: " << event->scenePos();
      m_currentStroke << event->scenePos();
      drawStrokes();
   }
}

//-----------------------------------------------------------------------------
void PMSourceScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
   m_allStrokes << m_currentStroke;
   m_currentStroke.clear();

   emit runSource();
}

//-----------------------------------------------------------------------------
void PMSourceScene::drawStrokes()
{

#if 1
   QPainterPath path(m_currentStroke.at(0));

   if (m_pathMode == EPathMode_Line) {
       for (int i=1; i<m_currentStroke.size(); ++i) {
           path.lineTo(m_currentStroke.at(i));
       }
   } else {
       int i=1;
       while (i + 2 < m_currentStroke.size()) {
           path.cubicTo(m_currentStroke.at(i), m_currentStroke.at(i+1), m_currentStroke.at(i+2));
           i += 3;
       }
       while (i < m_currentStroke.size()) {
           path.lineTo(m_currentStroke.at(i));
           ++i;
       }
   }

   m_drawnPathes.push_back(addPath(path,QPen(Qt::blue, 20, Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin)));

#else

   double rad = 5;
   foreach(QPointF point, m_currentStroke)
   {
      addEllipse(point.x()-rad, point.y()-rad, rad*2.0, rad*2.0,
               QPen(), QBrush(Qt::SolidPattern));
   }
#endif
}

//-----------------------------------------------------------------------------
void PMSourceScene::reset()
{
   m_allStrokes.clear();
   foreach(QGraphicsPathItem* path , m_drawnPathes)
   {
      removeItem(path);
   }
   m_drawnPathes.clear();
}

const PMSourceScene::Strokes &PMSourceScene::strokes() const
{
   return m_allStrokes;
}
