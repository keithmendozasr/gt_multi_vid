#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "videowidget.h"
#include "startdialog.h"

#include <cmath>

#include <phonon/MediaObject>
#include <phonon/VideoWidget>
#include <QStringList>

#include <QString>
#include <iostream>

StartDialog *box;

void closeBox()
{
    box->close();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::createVidWidgets()
{
    double rslt = sqrt(numVids);
    int numCols = static_cast<int>(ceil(rslt));
    int numRows = static_cast<int>(floor(rslt)) + ((numVids % numCols) ? 1 : 0);

    for(int rows=0, numLeft = numVids; rows<numRows; rows++)
    {
        for(int cols=0; cols<numCols && numLeft; cols++, numLeft--)
        {
            VideoWidget *vidWidget = new VideoWidget(this);

            ui->vidGrid->addWidget(vidWidget, rows, cols);

            connect(ui->playButton, SIGNAL(clicked()), vidWidget, SLOT(play()));
            connect(ui->stopButton, SIGNAL(clicked()), vidWidget, SLOT(stop()));
            connect(ui->pauseButton, SIGNAL(clicked()), vidWidget, SLOT(pause()));
            connect(ui->backButton, SIGNAL(clicked()), vidWidget, SLOT(backStep()));
            connect(ui->fwdButton, SIGNAL(clicked()), vidWidget, SLOT(fwdStep()));
            vidWidgetList.append(vidWidget);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QWidget::show();

    box = new StartDialog();
    connect(box, SIGNAL(accepted()), this, SLOT(startDialogAccept()));
    connect(box, SIGNAL(rejected()), this, SLOT(startDialogRejected()));
    box->setWindowModality(Qt::WindowModal);
    box->show();
}

void MainWindow::startDialogAccept()
{
    closeBox();
    numVids = box->getNumVids();

    createVidWidgets();
    delete box;
}

void MainWindow::startDialogReject()
{
    closeBox();
    delete box;
}
