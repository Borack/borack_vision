#ifndef PM_SOURCEVIEW_HPP
#define PM_SOURCEVIEW_HPP

#include <QWidget>

namespace Ui {
class PMSourceWidget;
}

class PMSourceWidget : public QWidget
{
   Q_OBJECT

public:
   explicit PMSourceWidget(QWidget *parent = 0);
   ~PMSourceWidget();

private:
   Ui::PMSourceWidget *ui;
};

#endif // PM_SOURCEVIEW_HPP
