#ifndef SOURCESCENE_HPP
#define SOURCESCENE_HPP

#include "customscene.hpp"
#include <QObject>
#include <QGraphicsPolygonItem>
#include <mvc_types.hpp>

class SourceScene : public CustomScene
{
   Q_OBJECT
public:
   explicit SourceScene(QObject *parent = 0);
   virtual ~SourceScene() {}

   MVC::Boundary getBoundary() const;

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);


private:
   virtual void reset();

   void drawPolygon();


   QGraphicsPolygonItem* m_polygon;
   MVC::Boundary m_boundary;

};

#endif // SOURCESCENE_HPP
