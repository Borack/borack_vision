#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QGraphicsView>
#include <QImage>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QWidget>
#include <QGraphicsScene>


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
    QString sourcePath = QFileDialog::getOpenFileName(this,"Open source image", "","Images (*.png *.jpg)");
    QPixmap sourceImage(sourcePath);

    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->addPixmap(sourceImage);

    ui->graphicsView->setScene(scene);
}

void MainWindow::on_actionOpen_target_triggered()
{
    QString targetPath  = QFileDialog::getOpenFileName(this,"Open target image", "","Images (*.png *.jpg)");
    QPixmap targetImage(targetPath);
}
