#ifndef PM_SOURCEVIEW_HPP
#define PM_SOURCEVIEW_HPP

#include <QWidget>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QPixmap>

#include <pm_sourcescene.hpp>

namespace Ui {
class PMSourceWidget;
}

typedef QSharedPointer<QPixmap> PixmapPointer;

class PMSourceWidget : public QWidget
{
   Q_OBJECT

public:


   explicit PMSourceWidget(QWidget *parent = 0);
   ~PMSourceWidget();

   PixmapPointer getPixmap();

private slots:
   void on_loadBtn_clicked();
   void on_runSource();

private:
   Ui::PMSourceWidget *ui;
   QScopedPointer<PMSourceScene> m_sScene;

   PixmapPointer m_pixmap;

   static const QString SETTINGS_LAST_PM_SOURCE_PATH;
};

#endif // PM_SOURCEVIEW_HPP
