#include "startdialog.h"
#include "ui_startdialog.h"

#include <QIntValidator>

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartDialog)
{
    ui->setupUi(this);
    ui->numVidBox->setValidator(new QIntValidator);
}

StartDialog::~StartDialog()
{
    delete ui;
}

int StartDialog::getNumVids()
{
    bool ok;
    int retVal = ui->numVidBox->text().toInt(&ok);

    return retVal;
}
