#ifndef CENTRALDIALOG_H
#define CENTRALDIALOG_H

#include <QDialog>
#include "singlejointunit.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CentralDialog; }
QT_END_NAMESPACE

class CentralDialog : public QDialog
{
    Q_OBJECT

public:
    static const int MaxJoints;
    CentralDialog(QWidget *parent = nullptr);
    ~CentralDialog();

    void startScan();

public slots:
    void onMoveRequest(int slot, int direction);

signals:
    void stScan();

private:
    Ui::CentralDialog *ui;
    SingleJointUnit **wdjts;
};
#endif // CENTRALDIALOG_H
