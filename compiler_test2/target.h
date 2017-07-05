#ifndef TARGET_H
#define TARGET_H

#include <QWidget>

namespace Ui {
class target;
}

class target : public QWidget
{
    Q_OBJECT

public:
    explicit target(QWidget *parent = 0);
    ~target();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::target *ui;
};

#endif // TARGET_H
