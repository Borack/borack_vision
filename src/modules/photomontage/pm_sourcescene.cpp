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
           qDebug() << "in curved mode";
       }
       while (i < m_currentStroke.size()) {
           path.lineTo(m_currentStroke.at(i));
           ++i;
       }
   }
   addPath(path,QPen(Qt::green, 5));
}

//-----------------------------------------------------------------------------
void PMSourceScene::reset()
{
   m_allStrokes.clear();
}
