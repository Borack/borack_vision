#ifndef PHOTOMONTAGE_SOURCESCENE_HPP
#define PHOTOMONTAGE_SOURCESCENE_HPP

#include "customscene.hpp"

class PMSourceScene : public CustomScene
{
   Q_OBJECT
public:
   typedef QVector<QPointF> Stroke;
   typedef QVector<Stroke> Strokes;
   enum EPathMode { EPathMode_Curve, EPathMode_Line };

   explicit PMSourceScene(QObject *parent = 0);

   virtual void reset();

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:

   void drawStrokes();

   EPathMode m_pathMode;
   Stroke m_currentStroke;
   Strokes m_allStrokes;
};

#endif // PHOTOMONTAGE_SOURCESCENE_HPP
