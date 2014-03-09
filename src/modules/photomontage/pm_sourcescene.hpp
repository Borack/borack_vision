#ifndef PHOTOMONTAGE_SOURCESCENE_HPP
#define PHOTOMONTAGE_SOURCESCENE_HPP

#include "customscene.hpp"

class PMSourceScene : public CustomScene
{
   Q_OBJECT
public:
   explicit PMSourceScene(QObject *parent = 0);

   virtual void reset() {}

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {}
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {}
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) {}
};

#endif // PHOTOMONTAGE_SOURCESCENE_HPP
