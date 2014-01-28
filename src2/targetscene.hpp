#ifndef TARGETSCENE_HPP
#define TARGETSCENE_HPP

#include "customscene.hpp"
#include "mvc_types.hpp"

#include <QPointF>
#include <QGraphicsPolygonItem>

class TargetScene : public CustomScene
{
   Q_OBJECT
public:
   explicit TargetScene(QObject *parent = 0);
   virtual ~TargetScene() {}

   QPointF clickLocation() const;

signals:
   void runMVCComputation();

public slots:
   void drawContour(MVC::Boundary boundary);

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
   QGraphicsPolygonItem* m_polygon;
   QPointF m_targetLocation;

};

#endif // TARGETSCENE_HPP
