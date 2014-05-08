#ifndef CUSTOMVIEW_HPP
#define CUSTOMVIEW_HPP

#include <QGraphicsView>
#include <QRectF>

class CustomView : public QGraphicsView
{
public:
   CustomView(QWidget *parent = 0);

protected:
   virtual void resizeEvent(QResizeEvent * event);
};

#endif // CUSTOMVIEW_HPP
