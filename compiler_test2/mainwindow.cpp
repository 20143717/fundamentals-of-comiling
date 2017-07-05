#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include "lexical.h"
#include "syntax.h"
#include "cal_quat.h"
#include "target_code.h"

extern lexical_analyse main_lexical;
extern syntax_analyse main_syntax;
extern cal_quat main_quat;
extern target_code main_tar;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str = ui->textEdit->toPlainText();
    main_lexical.solve(str);
    if(!main_lexical.err) {
        QMessageBox::warning(this, tr("Warning!"), tr("词法有错误"), QMessageBox::Yes);
        main_lexical.err = 1;
        return;
    }
    else {
        main_syntax.err = 0;
        main_syntax.get_word = "";
        main_syntax.get_type = -1;
        main_syntax.get_token = -1;
        main_syntax.struct_flag = 0;
        main_syntax.main_flag = 0;
        main_syntax.cur_type = "";
        main_syntax.total_address = 0;
        main_syntax.table_flag = 0;
        main_syntax.left_bracket = 0;
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
        /*while(!main_quat.quat.empty()) {
            main_quat.quat.pop_back();
        }*/
        while(!main_quat.fun_quat.empty()) {
            main_quat.fun_quat.pop_back();
        }
        main_syntax.redefine_check.clear();
        main_syntax.str_redefine.clear();
        main_syntax.fun_redefine.clear();
        main_syntax.tot = 1;
        main_syntax.solve();
        if(main_syntax.err) {
            QMessageBox::warning(this, tr("Warning!"), tr("语法或语义有错误"), QMessageBox::Yes);
            main_syntax.err = 0;
            return;
        }
        else {
            QMessageBox::about(this, tr("Successful!"), tr("编译通过"));
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
            while(!main_tar.tar_code.empty()) {
                main_tar.tar_code.pop_back();
            }
            main_tar.reput.clear();
            main_tar.solve();
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString str = ui->textEdit->toPlainText();
    main_lexical.solve(str);
    mylexical.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString str = ui->textEdit->toPlainText();
    main_lexical.solve(str);
    mysyntax.show();
}

void MainWindow::on_pushButton_4_clicked()
{
    QString str = ui->textEdit->toPlainText();
    main_lexical.solve(str);
    mys_table.show();
}

void MainWindow::on_pushButton_5_clicked()
{
    /*QString str = ui->textEdit->toPlainText();
    main_lexical.solve(str);
    main_syntax.err = 0;
    main_syntax.get_word = "";
    main_syntax.get_type = -1;
    main_syntax.get_token = -1;
    main_syntax.struct_flag = 0;
    main_syntax.main_flag = 0;
    main_syntax.cur_type = "";
    main_syntax.total_address = 0;
    main_syntax.table_flag = 0;
    main_syntax.left_bracket = 0;
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
    while(!main_quat.quat.empty()) {
        main_quat.quat.pop_back();
    }
    while(!main_quat.fun_quat.empty()) {
        main_quat.fun_quat.pop_back();
    }
    main_syntax.redefine_check.clear();
    main_syntax.fun_redefine.clear();
    main_syntax.tot = 1;
    main_syntax.solve();*/
    myquaternion.show();
}

void MainWindow::on_pushButton_6_clicked()
{
    mytarget.show();
}

void MainWindow::on_pushButton_7_clicked()
{
    qApp->quit();
}

void MainWindow::on_pushButton_8_clicked()
{
    system("start C:\Program Files (x86)\DOSBox-0.74\DOSBox.exe");
}
