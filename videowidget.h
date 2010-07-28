#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <phonon/MediaObject>
#include <phonon/VideoWidget>
#include <QWidget>
#include <QString>
#include <QAction>

namespace Ui {
    class VideoWidget;
}

class QString;

class VideoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = 0);
    VideoWidget(QString fileName, QWidget *parent = 0);

    ~VideoWidget();

    void setVideoFile(QString fileName);

public slots:
    void play();
    void pause();
    void stop();
    void backStep();
    void fwdStep();

private slots:
    void selectVideo();

private:
    Ui::VideoWidget *ui;

    Phonon::MediaObject mediaObject;
    Phonon::VideoWidget *vidWidget;

    void init();
    void setSlots();
};

#endif // VIDEOWIDGET_H
