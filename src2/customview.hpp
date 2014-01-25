#ifndef CUSTOMVIEW_HPP
#define CUSTOMVIEW_HPP

#include <QGraphicsView>

class CustomView : public QGraphicsView
{
public:
   CustomView(QWidget *parent = 0);

protected:
   virtual void mousePressEvent(QMouseEvent *event);
};

#endif // CUSTOMVIEW_HPP
