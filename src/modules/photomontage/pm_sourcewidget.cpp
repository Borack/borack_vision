#include "pm_sourcewidget.hpp"
#include "ui_pm_sourcewidget.h"

PMSourceWidget::PMSourceWidget(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::PMSourceWidget)
{
   ui->setupUi(this);
}

PMSourceWidget::~PMSourceWidget()
{
   delete ui;
}
