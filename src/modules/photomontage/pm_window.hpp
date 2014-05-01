#ifndef PM_WINDOW_HPP
#define PM_WINDOW_HPP

#include <QMainWindow>

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

   void on_comboBox_currentIndexChanged(int index);
   
private:

   enum EGraphCut_Objective
   {
       EGraphCut_Objective_Minimum_Lumincance = 0
      , EGraphCut_Objective_Maximum_Lumincance
   };
   EGraphCut_Objective m_gcMode;

   void setupCombobox();



   Ui::pm_window *ui;
};

#endif // PM_WINDOW_HPP
