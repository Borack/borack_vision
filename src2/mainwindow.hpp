#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QAction>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:



private:

    void setup();
    QAction* m_openFileAct;
    QMenu* m_fileMenu;

private slots:
    void openFile();

};

#endif // MAINWINDOW_HPP
