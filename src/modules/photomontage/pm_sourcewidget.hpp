#ifndef PM_SOURCEVIEW_HPP
#define PM_SOURCEVIEW_HPP

#include <QWidget>
#include <QScopedPointer>

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
   void on_runSource();

private:
   Ui::PMSourceWidget *ui;
   QScopedPointer<PMSourceScene> m_sScene;

   static const QString SETTINGS_LAST_PM_SOURCE_PATH;
};

#endif // PM_SOURCEVIEW_HPP
