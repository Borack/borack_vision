#ifndef PM_WINDOW_HPP
#define PM_WINDOW_HPP

#include <QMainWindow>
#include <photomontage.hpp>

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

   EGraphCut_Objective m_gcMode;

   void setupCombobox();
   void runLuminance(bool isMinimum);



   Ui::pm_window *ui;
};

#endif // PM_WINDOW_HPP
