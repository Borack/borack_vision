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

   virtual void reset() override;

   const Strokes& strokes() const;

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override;
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;

private:

   void drawStrokes();

   EPathMode m_pathMode;
   QVector<QGraphicsPathItem*> m_drawnPathes;
   Stroke m_currentStroke;
   Strokes m_allStrokes;
};

#endif // PHOTOMONTAGE_SOURCESCENE_HPP
