#include "customscene.hpp"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

CustomScene::CustomScene(QObject* parent)
   : QGraphicsScene(parent)
{
}

void CustomScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
//   qDebug() << "Button down pos: " << mouseEvent->buttonDownPos(Qt::AllButtons);
//   qDebug() << "Button down scene pos: " << mouseEvent->buttonDownScenePos(Qt::AllButtons);
//   qDebug() << "Button down screen pos: " << mouseEvent->buttonDownScreenPos(Qt::AllButtons);
//   qDebug() << "Pos: " << mouseEvent->pos();
   qDebug() << "Scene pos: " << mouseEvent->scenePos();
//   qDebug() << "Screen pos: " << mouseEvent->screenPos();
//   qDebug() << "";
}
