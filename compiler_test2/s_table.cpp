#include "s_table.h"
#include "ui_s_table.h"
#include "lexical.h"
#include "syntax.h"
#include <QMessageBox>
#include <QString>
#include <QtDebug>

extern lexical_analyse main_lexical;
extern syntax_analyse main_syntax;

s_table::s_table(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::s_table)
{
    ui->setupUi(this);
}

s_table::~s_table()
{
    delete ui;
}

void s_table::on_pushButton_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();

    main_syntax.err = 0;
    main_syntax.get_word = "";
    main_syntax.get_type = -1;
    main_syntax.get_token = -1;
    main_syntax.struct_flag = 0;
    main_syntax.main_flag = 0;
    main_syntax.cur_type = "";
    main_syntax.redefine_check.clear();
    main_syntax.tot = 1;
    main_syntax.total_address = 0;
    main_syntax.table_flag = 0;
    main_syntax.left_bracket = 0;
    main_syntax.get_elem = "";
    while(!main_syntax.symbol_table.empty()) {
        main_syntax.symbol_table.pop_back();
    }
    while(!main_syntax.struct_table.empty()) {
        main_syntax.struct_table.pop_back();
    }
    while(!main_syntax.function_table.empty()) {
        main_syntax.function_table.pop_back();
    }
    while(!main_syntax.array_table.empty()) {
        main_syntax.array_table.pop_back();
    }
    while(!main_syntax.get_quat.empty()) {
        main_syntax.get_quat.pop_back();
    }
    main_syntax.redefine_check.clear();
    main_syntax.str_redefine.clear();
    main_syntax.fun_redefine.clear();
    main_syntax.tot = 1;
    main_syntax.solve();
    int x = main_lexical.repick.size();
    while(x) {
        x--;
        show_lex z = main_lexical.repick.front();
        main_lexical.repick.pop();
        main_lexical.repick.push(z);
        main_lexical.syntax_check.push(z);
    }
    int xx = main_syntax.symbol_table.size();
    int len;
    int table_flag = 0;//设置存入对应符号表
    while(xx) {
        xx--;
        main_syntax.show_table = main_syntax.symbol_table.front();
        main_syntax.symbol_table.pop_front();
        main_syntax.symbol_table.push_back(main_syntax.show_table);
        len = main_syntax.show_table.symbol_name.length();
        char mm[111111];
        QString str = "";
        QString s_kind = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_name[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_kind.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_kind[i];
        }
        str = QString(QLatin1String(mm));
        s_kind = QString(QLatin1String(mm));
        ui->listWidget_2->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_type.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_type[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_3->addItem(tr("%1").arg(str));

        //变量的区距
        main_syntax.show_table.symbol_address = main_syntax.total_address;
        if(str == "int") {
            if(s_kind == "variable" || s_kind == "var_f") {
                main_syntax.total_address += 4;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
            }
            else if(s_kind == "array") {
                main_syntax.total_address += 4*main_syntax.show_table.arr_len;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
                main_syntax.array_table.push_back(main_syntax.show_table);
            }
            else if(s_kind == "function") {
                main_syntax.total_address = 0;
                main_syntax.show_table.symbol_address = 0;
                main_syntax.function_table.push_back(main_syntax.show_table);
                table_flag = 2;
            }
        }
        else if(str == "char") {
            if(s_kind == "variable" || s_kind == "var_f") {
                main_syntax.total_address += 1;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
            }
            else if(s_kind == "array") {
                main_syntax.total_address += 1*main_syntax.show_table.arr_len;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
                main_syntax.array_table.push_back(main_syntax.show_table);
            }
            else if(s_kind == "function") {
                main_syntax.total_address = 0;
                main_syntax.show_table.symbol_address = 0;
                main_syntax.function_table.push_back(main_syntax.show_table);
                table_flag = 2;
            }
        }
        else if(str == "float") {
            if(s_kind == "variable" || s_kind == "var_f") {
                main_syntax.total_address += 4;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
            }
            else if(s_kind == "array") {
                main_syntax.total_address += 4*main_syntax.show_table.arr_len;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
                main_syntax.array_table.push_back(main_syntax.show_table);
            }
            else if(s_kind == "function") {
                main_syntax.total_address = 0;
                main_syntax.show_table.symbol_address = 0;
                main_syntax.function_table.push_back(main_syntax.show_table);
                table_flag = 2;
            }
        }
        else if(str == "double") {
            if(s_kind == "variable" || s_kind == "var_f") {
                main_syntax.total_address += 8;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
            }
            else if(s_kind == "array") {
                main_syntax.total_address += 8*main_syntax.show_table.arr_len;
                if(table_flag == 2) {
                    main_syntax.function_table.push_back(main_syntax.show_table);
                }
                else if(table_flag == 1) {
                    main_syntax.struct_table.push_back(main_syntax.show_table);
                }
                main_syntax.array_table.push_back(main_syntax.show_table);
            }
            else if(s_kind == "function") {
                main_syntax.total_address = 0;
                main_syntax.show_table.symbol_address = 0;
                main_syntax.function_table.push_back(main_syntax.show_table);
                table_flag = 2;
            }
        }
        else if(s_kind == "struct") {
            main_syntax.total_address = 0;
            main_syntax.show_table.symbol_address = 0;
            table_flag = 1;
            main_syntax.struct_table.push_back(main_syntax.show_table);
        }
        else if(s_kind == "array") {
            main_syntax.total_address = 0;
            main_syntax.show_table.symbol_address = 0;
            main_syntax.array_table.push_back(main_syntax.show_table);
        }
        if(s_kind == "struct" || s_kind == "function") {
            ui->listWidget_4->addItem(tr("---"));
        }
        else {
            ui->listWidget_4->addItem(tr("%1").arg(main_syntax.show_table.symbol_address));
        }
        ui->listWidget_5->addItem(tr("%1").arg(main_syntax.show_table.appear_time));
    }
}

void s_table::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();
    close();
}
void s_table::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();

    int tot = 1;
    int xx = main_syntax.struct_table.size();
    int len;
    while(xx) {
        xx--;
        main_syntax.show_table = main_syntax.struct_table.front();
        main_syntax.struct_table.pop_front();
        main_syntax.struct_table.push_back(main_syntax.show_table);
        len = main_syntax.show_table.symbol_name.length();
        char mm[111111];
        QString str = "";
        QString s_kind = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_name[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_kind.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_kind[i];
        }
        str = QString(QLatin1String(mm));
        s_kind = QString(QLatin1String(mm));
        ui->listWidget_2->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_type.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_type[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_3->addItem(tr("%1").arg(str));
        if(s_kind == "struct") {
            ui->listWidget_4->addItem(tr("---"));
        }
        else {
            ui->listWidget_4->addItem(tr("%1").arg(main_syntax.show_table.symbol_address));
        }
        ui->listWidget_5->addItem(tr("%1").arg(tot++));
    }
}
void s_table::on_pushButton_4_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();

    int tot = 1;
    int xx = main_syntax.function_table.size();
    int len;
    while(xx) {
        xx--;
        main_syntax.show_table = main_syntax.function_table.front();
        main_syntax.function_table.pop_front();
        main_syntax.function_table.push_back(main_syntax.show_table);
        len = main_syntax.show_table.symbol_name.length();
        char mm[111111];
        QString str = "";
        QString s_kind = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_name[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_kind.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_kind[i];
        }
        str = QString(QLatin1String(mm));
        s_kind = QString(QLatin1String(mm));
        ui->listWidget_2->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_type.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_type[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_3->addItem(tr("%1").arg(str));
        if(s_kind == "function") {
            ui->listWidget_4->addItem(tr("---"));
        }
        else {
            ui->listWidget_4->addItem(tr("%1").arg(main_syntax.show_table.symbol_address));
        }
        ui->listWidget_5->addItem(tr("%1").arg(tot++));
    }
}
void s_table::on_pushButton_5_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();

    int tot = 1;
    int xx = main_syntax.array_table.size();
    int len;
    while(xx) {
        xx--;
        main_syntax.show_table = main_syntax.array_table.front();
        main_syntax.array_table.pop_front();
        main_syntax.array_table.push_back(main_syntax.show_table);
        len = main_syntax.show_table.symbol_name.length();
        char mm[111111];
        QString str = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_name[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_kind.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_kind[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_2->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_type.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_type[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_3->addItem(tr("%1").arg(str));
        ui->listWidget_4->addItem(tr("下界：0, 上界：%1").arg(main_syntax.show_table.arr_len));
        ui->listWidget_5->addItem(tr("%1").arg(tot++));
    }
}
void s_table::on_pushButton_6_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    ui->listWidget_4->clear();
    ui->listWidget_5->clear();

    int xx = main_syntax.const_table.size();
    int len;
    while(xx) {
        xx--;
        main_syntax.show_table = main_syntax.const_table.front();
        main_syntax.const_table.pop_front();
        main_syntax.const_table.push_back(main_syntax.show_table);
        len = main_syntax.show_table.symbol_name.length();
        char mm[111111];
        QString str = "";
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_name[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_kind.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_kind[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_2->addItem(tr("%1").arg(str));

        len = main_syntax.show_table.symbol_type.length();
        memset(mm, 0, sizeof mm);
        for(int i = 0; i < len; i++) {
            mm[i] = main_syntax.show_table.symbol_type[i];
        }
        str = QString(QLatin1String(mm));
        ui->listWidget_3->addItem(tr("%1").arg(str));
        ui->listWidget_4->addItem(tr("---"));
        ui->listWidget_5->addItem(tr("%1").arg(main_syntax.show_table.appear_time));
    }
}
