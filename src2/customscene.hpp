#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP
#include <QGraphicsScene>

#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QGraphicsPixmapItem>

class CustomScene : public QGraphicsScene
{
public:
   CustomScene(QObject *parent = 0);

   virtual void setPixmap(const QPixmap&img);

private:
   virtual void reset();
   QPixmap m_sceneImage;
   QGraphicsPixmapItem* m_pixmapItem;
};

#endif // CUSTOMSCENE_HPP
