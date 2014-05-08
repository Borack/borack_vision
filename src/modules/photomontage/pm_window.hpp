#ifndef PM_WINDOW_HPP
#define PM_WINDOW_HPP

#include <QMainWindow>
#include <QScopedPointer>

#include <photomontage.hpp>
#include <pm_targetscene.hpp>

namespace Ui {
class pm_window;
}

class PmWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit PmWindow(QWidget *parent = 0);
   ~PmWindow();

private slots:
   void on_runButton_clicked();
   
   void on_dataComboBox_currentIndexChanged(int index);

   void on_smoothnessComboBox_currentIndexChanged(int index);

private:

   EGraphCut_DataTerm m_gcDataTermMode;
   EGraphCut_SmoothnessTerm m_gcSmoothnessTermMode;

   void setupComboboxes();
   void runLuminance(bool isMinimum);



   Ui::pm_window *ui;
   QScopedPointer<PMTargetScene> m_tScene;

};

#endif // PM_WINDOW_HPP
