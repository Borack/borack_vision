#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QScopedPointer>
#include <QAbstractButton>
#include <QString>

#include <meanvalue_seamless_cloning.hpp>
#include "sourcescene.hpp"
#include "targetscene.hpp"

#include <photomontage.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_actionOpen_source_triggered();

   void on_actionOpen_target_triggered();

   void on_runMVCSource();

   void on_runMVCTarget();

   void on_buttonBox_clicked(QAbstractButton *button);

   void on_reset();

   void on_sourceZoom_sliderMoved(int position);

   void on_targetZoom_sliderMoved(int position);

private:

   void setup();
   void loadSourceImg(const QString& path);
   void loadTargetImg(const QString& path);
   void tryToLoadMVCInstance();

   Ui::MainWindow *ui;

   SourceScene *m_sScene;
   TargetScene *m_tScene;

   QScopedPointer<MeanValueSeamlessCloning> m_mvcCloning;
   static const QString SETTINGS_LAST_SOURCE_PATH;
   static const QString SETTINGS_LAST_TARGET_PATH;

   //! @todo needs to be modularized!
#ifdef MODULE_PHOTOMONTAGE
   QScopedPointer<PhotoMontage> m_photoMontage;
#endif
};

#endif // MAINWINDOW_HPP
