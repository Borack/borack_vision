#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_source_triggered()
{
    QFileDialog::getOpenFileName(this,"Open source image", "","Images (*.png *.jpg)");
}

void MainWindow::on_actionOpen_target_triggered()
{
    QFileDialog::getOpenFileName(this,"Open target image", "","Images (*.png *.jpg)");
}
