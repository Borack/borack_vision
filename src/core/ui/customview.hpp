#ifndef CUSTOMVIEW_HPP
#define CUSTOMVIEW_HPP

#include <QGraphicsView>
#include <QRectF>

//!
//! \brief  The \class CustomView class is a QGraphicsView.
//!         It is ensured that we render to an OpenGL context for
//!         a hardware accelerated UI performance
//!
class CustomView : public QGraphicsView
{
public:
   CustomView(QWidget *parent = 0);

protected:
   virtual void resizeEvent(QResizeEvent * event) override;
};

#endif // CUSTOMVIEW_HPP
