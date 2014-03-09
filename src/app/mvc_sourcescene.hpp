#ifndef SOURCESCENE_HPP
#define SOURCESCENE_HPP

#include "customscene.hpp"
#include <QObject>
#include <QGraphicsPolygonItem>
#include <mvc_types.hpp>

class MVCSourceScene : public CustomScene
{
   Q_OBJECT
public:
   explicit MVCSourceScene(QObject *parent = 0);
   virtual ~MVCSourceScene() {}

   MVC::Boundary getBoundary() const;

   virtual void reset();

public slots:
   void drawMesh(MVC::Mesh2d::Segments segements);


protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);


private:

   void drawPolygon();


   QGraphicsPolygonItem* m_polygon;
   MVC::Boundary m_boundary;
   std::vector<QGraphicsLineItem*> m_lines;

};

#endif // SOURCESCENE_HPP
