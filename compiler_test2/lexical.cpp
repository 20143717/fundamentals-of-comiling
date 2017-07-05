#include "lexical.h"
#include "ui_lexical.h"
#include <QtDebug>
#include <QMessageBox>
#include "syntax.h"
#include <iostream>

extern lexical_analyse main_lexical;
extern syntax_analyse main_syntax;

lexical::lexical(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::lexical)
{
    ui->setupUi(this);
}

lexical::~lexical()
{
    delete ui;
}

void lexical::on_pushButton_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    ui->listWidget_3->clear();
    close();
}

void lexical::on_pushButton_2_clicked()
{
   show_lex x;
   int tot = 1;
   int total = 1;
   while(!main_syntax.const_table.empty()) {
       main_syntax.const_table.pop_back();
   }
   while(!main_lexical.show_word.empty()) {
       x = main_lexical.show_word.front();
       main_lexical.show_word.pop();
       int len = x.str.length();
       char mm[111111];
       memset(mm, 0, sizeof mm);
       for(int i = 0; i < len; i++) {
           mm[i] = x.str[i];
       }
       QString str = QString(QLatin1String(mm));
       ui->listWidget->addItem(tr("%1:   %2").arg(tot).arg(str));
       if(x.type_id == 1) {
           ui->listWidget_2->addItem(tr("%1:   关键字").arg(tot));
       }
       else if(x.type_id == 2) {
           ui->listWidget_2->addItem(tr("%1:   界符").arg(tot));
       }
       else if(x.type_id == 3) {
           ui->listWidget_2->addItem(tr("%1:   标识符").arg(tot));
       }
       else if(x.type_id == 4) {
           ui->listWidget_2->addItem(tr("%1:   整型常量").arg(tot));
           main_syntax.x.appear_time = total++;
           main_syntax.x.symbol_address = 0;
           main_syntax.x.symbol_kind = "const";
           main_syntax.x.symbol_name = x.str;
           main_syntax.x.symbol_type = "interger";
           main_syntax.const_table.push_back(main_syntax.x);
       }
       else if(x.type_id == 5) {
           ui->listWidget_2->addItem(tr("%1:   实型常量").arg(tot));
           main_syntax.x.appear_time = total++;
           main_syntax.x.symbol_address = 0;
           main_syntax.x.symbol_kind = "const";
           main_syntax.x.symbol_name = x.str;
           main_syntax.x.symbol_type = "real";
           main_syntax.const_table.push_back(main_syntax.x);
       }
       else if(x.type_id == 6) {
           ui->listWidget_2->addItem(tr("%1:   字符常量").arg(tot));
           main_syntax.x.appear_time = total++;
           main_syntax.x.symbol_address = 0;
           main_syntax.x.symbol_kind = "const";
           main_syntax.x.symbol_name = x.str;
           main_syntax.x.symbol_type = "character";
           main_syntax.const_table.push_back(main_syntax.x);
       }
       else if(x.type_id == 7) {
           ui->listWidget_2->addItem(tr("%1:   字符串常量").arg(tot));
           main_syntax.x.appear_time = total++;
           main_syntax.x.symbol_address = 0;
           main_syntax.x.symbol_kind = "const";
           main_syntax.x.symbol_name = x.str;
           main_syntax.x.symbol_type = "string";
           main_syntax.const_table.push_back(main_syntax.x);
       }
       ui->listWidget_3->addItem(tr("%1:  %2").arg(tot).arg(x.token));
       tot++;
   }
   if(!main_lexical.err) {
       QMessageBox::warning(this, tr("Warning!"), tr("词法有错误"), QMessageBox::Yes);
       main_lexical.err = 1;
   }
}
