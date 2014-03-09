#ifndef TARGETSCENE_HPP
#define TARGETSCENE_HPP

#include <customscene.hpp>
#include <mvc_types.hpp>

#include <QPointF>
#include <QGraphicsPolygonItem>
#include <QImage>
#include <QPixmap>

class MVCTargetScene : public CustomScene
{
   Q_OBJECT
public:
   explicit MVCTargetScene(QObject *parent = 0);
   virtual ~MVCTargetScene() {}

   QPointF clickLocation() const;
   virtual void reset();

public slots:
   void drawContour(MVC::Boundary boundary);
   void drawFinalPatch(QImage img);

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) {}
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) {}

private:
   QGraphicsPolygonItem* m_polygon;
   QGraphicsPixmapItem* m_pixmap;
   QPointF m_targetLocation;

};

#endif // TARGETSCENE_HPP
