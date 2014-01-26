#ifndef TARGETSCENE_HPP
#define TARGETSCENE_HPP

#include "customscene.hpp"
#include <QPointF>

class TargetScene : public CustomScene
{
   Q_OBJECT
public:
   explicit TargetScene(QObject *parent = 0);
   virtual ~TargetScene() {}

signals:
   void runMVCComputation();

public slots:


protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
   QPointF m_targetLocation;

};

#endif // TARGETSCENE_HPP
