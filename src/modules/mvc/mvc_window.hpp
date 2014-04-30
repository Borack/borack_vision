#ifndef MVC_WINDOW_HPP
#define MVC_WINDOW_HPP

#include <QMainWindow>
#include <QScopedPointer>
#include <QAbstractButton>
#include <QString>

#include <meanvalue_seamless_cloning.hpp>
#include <mvc_sourcescene.hpp>
#include <mvc_targetscene.hpp>

namespace Ui {
class MvcWindow;
}

class MvcWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MvcWindow(QWidget *parent = 0);
   ~MvcWindow();

private slots:
   void on_actionOpen_source_triggered();

   void on_actionOpen_target_triggered();

   void on_runSource();

   void on_runTarget();

   void on_buttonBox_clicked(QAbstractButton *button);

   void on_reset();

   void on_sourceZoom_sliderMoved(int position);

   void on_targetZoom_sliderMoved(int position);

   void on_mvcSelected(bool enabled);

private:

   enum EMode{
      EMode_MVC = 0,
      EMode_PhotoMontage
   };

   void setup();
   void loadSourceImg(const QString& path);
   void loadTargetImg(const QString& path);
   void tryToLoadMVCInstance();

   Ui::MvcWindow *ui;

   CustomScene *m_sScene;
   CustomScene *m_tScene;

   QScopedPointer<MeanValueSeamlessCloning> m_mvcCloning;


   static const QString SETTINGS_LAST_SOURCE_PATH;
   static const QString SETTINGS_LAST_TARGET_PATH;

   EMode m_mode;

};

#endif // MVC_WINDOW_HPP
