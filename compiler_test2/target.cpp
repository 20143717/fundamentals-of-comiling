#include "target.h"
#include "ui_target.h"
#include "target_code.h"
#include <QFileDialog>

extern cal_quat main_quat;
extern target_code main_tar;

target::target(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::target)
{
    ui->setupUi(this);
}

target::~target()
{
    delete ui;
}

void target::on_pushButton_clicked()
{
    ui->textEdit->clear();

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
            //ui->listWidget->addItem(str);
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
    //-----------------------------

    main_tar.tot1 = 10;
    main_tar.tot2 = 100;
    main_tar.flag = 1000;
    main_tar.flag2 = 100;
    main_tar.cur = 0;
    while(!main_tar.tar_code.empty()) {
        main_tar.tar_code.pop_back();
    }
    main_tar.reput.clear();
    main_tar.solve();
    int szz = main_tar.tar_code.size();
    while(szz--) {
        string x = main_tar.tar_code.front();
        main_tar.tar_code.pop_front();
        main_tar.tar_code.push_back(x);
        int len = x.length();
        char mm[111111];
        QString str = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = x[i];
        }
        str = QString(QLatin1String(mm));
        ui->textEdit->append(str);
    }
}

void target::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    close();
}
