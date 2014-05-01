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

private:
   Ui::pm_window *ui;
};

#endif // PM_WINDOW_HPP
