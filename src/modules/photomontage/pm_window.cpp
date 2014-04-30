#include "pm_window.hpp"
#include "ui_pm_window.h"

PmWindow::PmWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::pm_window)
{
   ui->setupUi(this);
}

PmWindow::~PmWindow()
{
   delete ui;
}
