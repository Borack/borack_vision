#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QScopedPointer>
#include <QAbstractButton>
#include <QString>

#include <modules/mvc/meanvalue_seamless_cloning.hpp>
#include "sourcescene.hpp"
#include "targetscene.hpp"

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

    void on_runMVCSource();

    void on_runMVCTarget();

    void on_buttonBox_clicked(QAbstractButton *button);

    void on_reset();

private:

    void setup();
    void loadSourceImg(const QString& path);
    void loadTargetImg(const QString& path);
    void tryToLoadMVCInstance();

    Ui::MainWindow *ui;

    SourceScene *m_sScene;
    TargetScene *m_tScene;

    QScopedPointer<MeanValueSeamlessCloning> m_mvcCloning;
    static const QString SETTINGS_LAST_SOURCE_PATH;
    static const QString SETTINGS_LAST_TARGET_PATH;
};

#endif // MAINWINDOW_HPP
