#ifndef S_TABLE_H
#define S_TABLE_H

#include <QWidget>

namespace Ui {
class s_table;
}

class s_table : public QWidget
{
    Q_OBJECT

public:
    explicit s_table(QWidget *parent = 0);
    ~s_table();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::s_table *ui;
};

#endif // S_TABLE_H
