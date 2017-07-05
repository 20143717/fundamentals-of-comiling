#ifndef SYNTAX_H
#define SYNTAX_H

#include <QWidget>
#include "syntax_analyse.h"

namespace Ui {
class syntax;
}

class syntax : public QWidget
{
    Q_OBJECT

public:
    explicit syntax(QWidget *parent = 0);
    ~syntax();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::syntax *ui;
};

#endif // SYNTAX_H
