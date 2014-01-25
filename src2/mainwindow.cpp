#include "mainwindow.hpp"
#include <QMenuBar>
#include <QKeySequence>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setup();
}

void MainWindow::setup()
{
    m_openFileAct = new QAction(tr("&Open..."), this);
    m_openFileAct->setShortcut(QKeySequence::Open);
    connect(m_openFileAct, SIGNAL(triggered()), this, SLOT(openFile()));

    m_fileMenu = menuBar()->addMenu("&File");
    m_fileMenu->addAction(m_openFileAct);
}


void MainWindow::openFile()
{

}
