#ifndef LEXICAL_H
#define LEXICAL_H

#include <QMainWindow>
#include <QString>
#include "ui_mainwindow.h"
#include "lexical_analyse.h"

namespace Ui {
class lexical;
}

class lexical : public QMainWindow
{
    Q_OBJECT

public:
    explicit lexical(QWidget *parent = 0);
    ~lexical();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::lexical *ui;
};

#endif // LEXICAL_H
