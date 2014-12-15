#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP
#include <QGraphicsScene>

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QPointF>
#include <QVector>



class CustomScene : public QGraphicsScene
{
   Q_OBJECT

public:
   explicit CustomScene(QObject *parent = 0);
   virtual ~CustomScene() {}

   virtual void setPixmap(const QPixmap&img);
   virtual QPixmap getPixmap() const;

   virtual void reset() = 0;

signals:
   void runSource();
   void runTarget();

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) override  = 0;
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override = 0;
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override = 0;

private:
   QPixmap m_sceneImage;
   QGraphicsPixmapItem* m_pixmapItem;
};

#endif // CUSTOMSCENE_HPP
