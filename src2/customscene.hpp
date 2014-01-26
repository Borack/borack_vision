#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP
#include <QGraphicsScene>

#include <QPixmap>
#include <QVector>
#include <QPointF>

class CustomScene : public QGraphicsScene
{
public:
   CustomScene(QObject *parent = 0);

   virtual void setPixmap(const QPixmap&img);

private:
   virtual void reset();
   QPixmap m_sceneImage;
};

#endif // CUSTOMSCENE_HPP
