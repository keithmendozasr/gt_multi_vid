#include <phonon/MediaSource>
#include <QString>
#include <Phonon>
#include <QFileDialog>

#include "videowidget.h"
#include "ui_videowidget.h"

VideoWidget::VideoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VideoWidget)
{
    init();
}

void VideoWidget::setSlots()
{
    connect(ui->playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(ui->pauseButton, SIGNAL(clicked()), this, SLOT(pause()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(backStep()));
    connect(ui->fwdButton, SIGNAL(clicked()), this, SLOT(fwdStep()));
    connect(ui->loadVidButton, SIGNAL(clicked()), this, SLOT(selectVideo()));
}

void VideoWidget::init()
{
    ui->setupUi(this);

    vidWidget = new Phonon::VideoWidget(this);
    Phonon::createPath(&mediaObject, vidWidget);

    ui->vidGrid->addWidget(vidWidget);
    setSlots();
}

void VideoWidget::setVideoFile(QString fileName)
{
    ui->fileNameLabel->setText(fileName);
    Phonon::MediaSource *src = new Phonon::MediaSource(fileName);
    src->setAutoDelete(true);
    mediaObject.setCurrentSource(*src);
}

VideoWidget::VideoWidget(QString fileName, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VideoWidget)
{
    init();
    setVideoFile(fileName);
}

VideoWidget::~VideoWidget()
{
    delete ui;
}

void VideoWidget::play()
{
    mediaObject.play();
}

void VideoWidget::pause()
{
    mediaObject.pause();
}

void VideoWidget::stop()
{
    mediaObject.stop();
}

void VideoWidget::backStep()
{
    mediaObject.seek(mediaObject.currentTime() - 1000);
}

void VideoWidget::fwdStep()
{
    mediaObject.seek(mediaObject.currentTime() + 1000);
}

void VideoWidget::selectVideo()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select Video File"));
    if(fileName.length())
    {
        setVideoFile(fileName);
    }
}
