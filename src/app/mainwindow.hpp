#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = 0);
   ~MainWindow();

protected:
   virtual void closeEvent(QCloseEvent*event);

private slots:
   void on_quitButton_clicked();

private:
   Ui::MainWindow *ui;
};

#endif // MAINWINDOW_HPP
