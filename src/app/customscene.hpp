#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP
#include <QGraphicsScene>

#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QGraphicsPixmapItem>

#include <modules/mvc/mvc_types.hpp>

class CustomScene : public QGraphicsScene
{
   Q_OBJECT
public:
   explicit CustomScene(QObject *parent = 0);
   virtual ~CustomScene() {}

   virtual void setPixmap(const QPixmap&img);
   virtual QPixmap getPixmap() const;

private:
   virtual void reset();
   QPixmap m_sceneImage;
   QGraphicsPixmapItem* m_pixmapItem;
};

#endif // CUSTOMSCENE_HPP
