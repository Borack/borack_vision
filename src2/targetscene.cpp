#include "targetscene.hpp"
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

TargetScene::TargetScene(QObject *parent) :
   CustomScene(parent)
{
}

void TargetScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   m_targetLocation = mouseEvent->scenePos();
   emit runMVCComputation();
}
