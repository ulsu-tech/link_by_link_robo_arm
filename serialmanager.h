#ifndef SERIALMANAGER_H
#define SERIALMANAGER_H

#include <QWidget>
#include <QSerialPort>

namespace Ui {
class SerialManager;
}

class SerialManager : public QWidget
{
    Q_OBJECT

public:
    explicit SerialManager(QWidget *parent = nullptr);
    ~SerialManager();

public slots:
    void StartScan();
    void makeMove(int slot, int direction, int step, int speed);
    void onReadReady();

private slots:
    void on_scanButton_clicked();
    void on_comboBox_activated(int index);
    void on_disconnectButton_clicked();
    void on_connectButton_clicked();

    void on_xButton_clicked();

private:
    Ui::SerialManager *ui;
    QSerialPort sp;
    bool spOpened;
};

#endif // SERIALMANAGER_H
