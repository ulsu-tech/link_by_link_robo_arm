#include "singlejointunit.h"
#include "ui_singlejointunit.h"

SingleJointUnit::SingleJointUnit(int v, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleJointUnit),
    properId(v)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QString("%1").arg(properId));
}

SingleJointUnit::~SingleJointUnit()
{
    delete ui;
}

void SingleJointUnit::on_lessButton_clicked()
{
    emit moveRequest( properId, -1);
}


void SingleJointUnit::on_moreButton_clicked()
{
    emit moveRequest( properId, 1);
}

