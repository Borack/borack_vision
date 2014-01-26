#ifndef SOURCESCENE_HPP
#define SOURCESCENE_HPP

#include "customscene.hpp"
#include <QObject>
#include <QGraphicsPolygonItem>

class SourceScene : public CustomScene
{
public:
   typedef QVector<QPointF> Boundary;

   SourceScene(QObject *parent = 0);

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);


private:
   virtual void reset();

   void drawPolygon();


   QGraphicsPolygonItem* m_polygon;
   Boundary m_boundary;

};

#endif // SOURCESCENE_HPP
