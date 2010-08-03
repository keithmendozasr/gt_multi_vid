#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "videowidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void show();

private:
    Ui::MainWindow *ui;

    QList<VideoWidget *>vidWidgetList;

    int numVids;

    void createVidWidgets();
    void askNumVids();

private slots:
    void startDialogAccept();
    void startDialogReject();
    void setVideos();
};

#endif // MAINWINDOW_H
