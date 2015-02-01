#ifndef PB_WINDOW_HPP
#define PB_WINDOW_HPP

#include <QMainWindow>

namespace Ui {
class PBWindow;
}

class PBWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit PBWindow(QWidget *parent = 0);
   ~PBWindow();

private slots:
   void on_runButton_clicked();

private:
   Ui::PBWindow *ui;
};

#endif // PB_WINDOW_HPP
