#include "cd.h"
#include "ui_centraldialog.h"


CentralDialog::CentralDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CentralDialog)
{
    ui->setupUi(this);
    wdjts = new SingleJointUnit*[MaxJoints];
    for(int i=0; i < MaxJoints; ++i)
    {
        wdjts[i] = new SingleJointUnit(i+1, this);
        ui->verticalLayout->addWidget(wdjts[i]);
        connect(wdjts[i], SIGNAL(moveRequest(int, int)), this, SLOT(onMoveRequest(int, int)));

    }
    connect(this, SIGNAL(stScan()), ui->widget, SLOT(StartScan()));
}

CentralDialog::~CentralDialog()
{
    for(int i=0; i < MaxJoints; ++i)
    {
        delete wdjts[i];
    }
    delete[] wdjts;
    delete ui;
}

void CentralDialog::startScan()
{
    emit stScan();
}

void CentralDialog::onMoveRequest(int slot, int direction)
{
    int step;
    int speed;
    bool ok;
    step = ui->lineStep->text().toInt(&ok);
    if(ok)
    {
        if( step > 180 )
        {
            step = 180;
            ui->lineStep->setText(QString("%1").arg(step));
        }
        if (step < 10)
        {
            step = 10;
            ui->lineStep->setText(QString("%1").arg(step));
        }
    } else
    {
        return;
    }

    speed = ui->lineSpeed->text().toInt(&ok);
    if(ok)
    {
        if( speed > 100 )
        {
            speed = 100;
            ui->lineSpeed->setText(QString("%1").arg(speed));
        }
        if (speed < 30)
        {
            speed = 30;
            ui->lineSpeed->setText(QString("%1").arg(speed));
        }
    } else
    {
        return;
    }

    ui->widget->makeMove(slot, direction, step, speed);
}

const int CentralDialog::MaxJoints = 6;
