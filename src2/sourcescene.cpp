#include "sourcescene.hpp"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>

SourceScene::SourceScene(QObject *parent)
   : CustomScene(parent)
{
}

void SourceScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   //   qDebug() << "Button down pos: " << mouseEvent->buttonDownPos(Qt::AllButtons);
   //   qDebug() << "Button down scene pos: " << mouseEvent->buttonDownScenePos(Qt::AllButtons);
   //   qDebug() << "Button down screen pos: " << mouseEvent->buttonDownScreenPos(Qt::AllButtons);
   //   qDebug() << "Pos: " << mouseEvent->pos();
      qDebug() << "Scene pos: " << mouseEvent->scenePos();
      m_boundary << mouseEvent->scenePos();
   //   qDebug() << "Screen pos: " << mouseEvent->screenPos();
   //   qDebug() << "";

}

void SourceScene::reset()
{
   m_boundary.clear();
}
