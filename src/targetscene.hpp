#ifndef TARGETSCENE_HPP
#define TARGETSCENE_HPP

#include "customscene.hpp"
#include "mvc_types.hpp"

#include <QPointF>
#include <QGraphicsPolygonItem>
#include <QImage>
#include <QPixmap>

class TargetScene : public CustomScene
{
   Q_OBJECT
public:
   explicit TargetScene(QObject *parent = 0);
   virtual ~TargetScene() {}

   QPointF clickLocation() const;
   virtual void reset();

signals:
   void runMVCComputation();

public slots:
   void drawContour(MVC::Boundary boundary);
   void drawFinalPatch(QImage img);

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);

private:
   QGraphicsPolygonItem* m_polygon;
   QGraphicsPixmapItem* m_pixmap;
   QPointF m_targetLocation;

};

#endif // TARGETSCENE_HPP
