#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP
#include <QGraphicsScene>

#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QGraphicsPixmapItem>


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
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent) = 0;
   virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) = 0;

private:
   QPixmap m_sceneImage;
   QGraphicsPixmapItem* m_pixmapItem;
};

#endif // CUSTOMSCENE_HPP
