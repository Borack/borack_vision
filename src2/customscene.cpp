#include "customscene.hpp"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

CustomScene::CustomScene(QObject* parent)
   : QGraphicsScene(parent)
{
}

void CustomScene::setPixmap(const QPixmap &img)
{
      reset();
      m_sceneImage = img;
      m_pixmapItem = addPixmap(m_sceneImage);
}

void CustomScene::reset()
{
   // empty
}
