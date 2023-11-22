#include "serialmanager.h"
#include "qdebug.h"
#include "ui_serialmanager.h"
#include <QSerialPortInfo>
#include <QThread>

SerialManager::SerialManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialManager)
    , spOpened(false)
{
    ui->setupUi(this);
    connect(&sp, SIGNAL(readyRead()), this, SLOT(onReadReady()));
}

SerialManager::~SerialManager()
{
    delete ui;
}

void SerialManager::StartScan()
{
    QList<QSerialPortInfo> portsList = QSerialPortInfo::availablePorts();
    ui->comboBox->clear();
    qDebug()<<"portsList len is "<<portsList.size();
    if(portsList.size() > 0)
        ui->comboBox->addItem("");
    for(auto ic = portsList.cbegin(); ic != portsList.cend(); ++ic)
    {
        ui->comboBox->addItem(ic->portName(), ic->systemLocation());
    }
}


void SerialManager::on_scanButton_clicked()
{
    StartScan();
    ui->connectButton->setEnabled(false);
}


void SerialManager::on_comboBox_activated(int index)
{
    qDebug()<<"activated index "<<index<<"  with value"<<ui->comboBox->itemText(index);
    ui->connectButton->setEnabled(ui->comboBox->itemText(index) != "" );
}


void SerialManager::on_disconnectButton_clicked()
{
    if(sp.isOpen())
    {
        sp.close();
    }
    spOpened = false;
    ui->disconnectButton->setEnabled(spOpened);
}


void SerialManager::on_connectButton_clicked()
{
    auto i = ui->comboBox->currentIndex();
    qDebug()<<ui->comboBox->itemText(i)<<"   "<<ui->comboBox->itemData(i).toString();
    sp.setPortName( ui->comboBox->itemText(i) );
    sp.setBaudRate(QSerialPort::Baud115200);
    sp.setDataBits(QSerialPort::Data8);
    sp.setParity(QSerialPort::NoParity);
    sp.setStopBits(QSerialPort::OneStop);
    sp.setFlowControl(QSerialPort::SoftwareControl);
    auto openRV = sp.open(QIODevice::ReadWrite);
    if(sp.isOpen())
    {
        spOpened = true;
        ui->disconnectButton->setEnabled(spOpened);
        ui->connectButton->setEnabled(false);
    }
}

void SerialManager::onReadReady()
{
    auto rv = sp.readAll();
    qDebug()<<"Received "<<rv;
}

void SerialManager::makeMove(int slot, int direction, int step, int speed)
{
    QString cmd = QString("G1 J%1 %2 S %3").arg(slot).arg(direction > 0?(step * 100):(-step * 100)).arg(speed);
    qDebug()<<"cmd == "<<cmd;
    auto array = cmd.toLocal8Bit();

    int i;
    for(i=0; i < array.length(); ++i)
    {
        char rr[2];
        rr[1] = '\0';
        rr[0]= array.at(i);
        sp.write(rr);
        QThread::msleep(5);
    }
    sp.write("\r\n");
}

void SerialManager::on_xButton_clicked()
{
    sp.write("x");
}

