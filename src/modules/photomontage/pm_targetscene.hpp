#ifndef PM_TARGETSCENE_HPP
#define PM_TARGETSCENE_HPP

#include <customscene.hpp>

class PMTargetScene : public CustomScene
{
public:
   PMTargetScene(QObject *parent = 0);

   virtual void reset() override {}

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override {}
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *) override {}
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override {}
};

#endif // PM_TARGETSCENE_HPP
