#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <QPointer>

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

   void on_mvcButton_clicked();

private:
   Ui::MainWindow *ui;
   QPointer<QWidget> m_moduleWindow;


};

#endif // MAINWINDOW_HPP
