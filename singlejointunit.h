#ifndef SINGLEJOINTUNIT_H
#define SINGLEJOINTUNIT_H

#include <QWidget>

namespace Ui {
class SingleJointUnit;
}

class SingleJointUnit : public QWidget
{
    Q_OBJECT

public:
    explicit SingleJointUnit(int, QWidget *parent = nullptr);
    ~SingleJointUnit();

signals:
    void moveRequest(int index, int direction);

private slots:
    void on_lessButton_clicked();
    void on_moreButton_clicked();

private:
    Ui::SingleJointUnit *ui;
    int properId;
};

#endif // SINGLEJOINTUNIT_H
