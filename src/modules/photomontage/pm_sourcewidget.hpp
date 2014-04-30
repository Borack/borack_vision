#ifndef PM_SOURCEVIEW_HPP
#define PM_SOURCEVIEW_HPP

#include <QWidget>

#include <pm_sourcescene.hpp>

namespace Ui {
class PMSourceWidget;
}

class PMSourceWidget : public QWidget
{
   Q_OBJECT

public:
   explicit PMSourceWidget(QWidget *parent = 0);
   ~PMSourceWidget();

private slots:
   void on_loadBtn_clicked();

private:
   Ui::PMSourceWidget *ui;
   PMSourceScene* m_sScene;
};

#endif // PM_SOURCEVIEW_HPP
