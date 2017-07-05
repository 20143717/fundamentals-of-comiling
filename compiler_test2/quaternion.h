#ifndef QUATERNION_H
#define QUATERNION_H

#include <QWidget>

namespace Ui {
class quaternion;
}

class quaternion : public QWidget
{
    Q_OBJECT

public:
    explicit quaternion(QWidget *parent = 0);
    ~quaternion();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
private:
    Ui::quaternion *ui;
};

#endif // QUATERNION_H
