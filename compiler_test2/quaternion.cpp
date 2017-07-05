#include "quaternion.h"
#include "ui_quaternion.h"

#include "cal_quat.h"

extern cal_quat main_quat;

quaternion::quaternion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::quaternion)
{
    ui->setupUi(this);
}

quaternion::~quaternion()
{
    delete ui;
}

void quaternion::on_pushButton_clicked()
{
    ui->listWidget->clear();

    int sz = main_quat.quat.size();
    bool flag = 0;
    while(!main_quat.display.empty()) {
        main_quat.display.pop_back();
    }
    while(sz--) {
        string x = main_quat.quat.front();
        main_quat.quat.pop_front();
        main_quat.quat.push_back(x);
        if(flag) {
            main_quat.display.push_back(x);
            int len = x.length();
            char mm[111111];
            QString str = "";
            memset(mm, 0, sizeof mm);
            for(int i = 0; i < len; i++) {
                mm[i] = x[i];
            }
            str = QString(QLatin1String(mm));
            ui->listWidget->addItem(str);
        }
        if(x == main_quat.store_quat("main", "__", "__", "__")) {
            flag = 1;
        }
        if(!flag) {
            main_quat.fun_quat.push_back(x);
        }
    }
    while(!main_quat.last_quat.empty()) {
        main_quat.last_quat.pop_back();
    }
    while(!main_quat.ret_target.empty()) {
        main_quat.ret_target.pop_back();
    }
    while(!main_quat.ret_for.empty()) {
        main_quat.ret_for.pop_back();
    }
    int tot = 30;
    while(tot--) {
        while(!main_quat.show_quat[tot].empty()) {
            main_quat.show_quat[tot].pop_back();
        }
        while(!main_quat.optimize_quat[tot].empty()) {
            main_quat.optimize_quat[tot].pop_back();
        }
    }
    main_quat.block_num = 0;
    main_quat.opt_quat();
    main_quat.opt_again();
    //main_quat.del_if();
}

void quaternion::on_pushButton_2_clicked()
{
    ui->listWidget_2->clear();

    int sz = main_quat.last_quat.size();
    while(sz--) {
        string x = main_quat.last_quat.front();
        main_quat.last_quat.pop_front();
        main_quat.last_quat.push_back(x);
        int len = x.length();
        char mm[111111];
        QString str = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = x[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_2->addItem(str);
    }
}

void quaternion::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    close();
}
