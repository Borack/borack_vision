#ifndef PM_TARGETSCENE_HPP
#define PM_TARGETSCENE_HPP

#include <customscene.hpp>

class PMTargetScene : public CustomScene
{
public:
   PMTargetScene(QObject *parent = 0);

   virtual void reset() {}

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) {}
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {}
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) {}
};

#endif // PM_TARGETSCENE_HPP
