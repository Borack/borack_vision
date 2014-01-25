#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout;
    ui->centralwidget->setLayout(layout);
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
