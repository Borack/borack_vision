#ifndef CUSTOMSCENE_HPP
#define CUSTOMSCENE_HPP
#include <QGraphicsScene>

class CustomScene : public QGraphicsScene
{
public:
   CustomScene(QObject *parent = 0);

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
};

#endif // CUSTOMSCENE_HPP
