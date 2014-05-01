#include "pm_sourcescene.hpp"
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

//-----------------------------------------------------------------------------
PMSourceScene::PMSourceScene(QObject *parent)
   : CustomScene(parent)
   , m_pathMode(EPathMode_Curve)
   , m_currentPath(0)
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
   qDebug() << "Scene pos: " << mouseEvent->scenePos();
//   qDebug() << "Screen pos: " << mouseEvent->screenPos();
   qDebug() << "";
}

//-----------------------------------------------------------------------------
void PMSourceScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   if(event->buttons() != Qt::NoButton)
   {
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


   m_currentPath = addPath(path,QPen(Qt::blue, 20, Qt::SolidLine, Qt::FlatCap, Qt::BevelJoin));
}

//-----------------------------------------------------------------------------
void PMSourceScene::reset()
{
   m_allStrokes.clear();
   if(m_currentPath)
   {
      removeItem(m_currentPath);
   }
   m_currentPath = 0;
}

const PMSourceScene::Strokes &PMSourceScene::strokes() const
{
   return m_allStrokes;
}
