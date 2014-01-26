#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_source_triggered();

    void on_actionOpen_target_triggered();
private:

    void setup();
    void loadSourceImg(const QString& path);
    void loadTargetImg(const QString& path);

    Ui::MainWindow *ui;
    QString m_lastImgPath;
    static const QString SETTINGS_LAST_SOURCE_PATH;
    static const QString SETTINGS_LAST_TARGET_PATH;
};

#endif // MAINWINDOW_HPP
