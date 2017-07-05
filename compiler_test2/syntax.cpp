#include "syntax.h"
#include "ui_syntax.h"

#include "cal_quat.h"

#include <QMessageBox>
#include <QtDebug>

extern syntax_analyse main_syntax;
extern cal_quat main_quat;

syntax::syntax(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::syntax)
{
    ui->setupUi(this);
}

syntax::~syntax()
{
    delete ui;
}

void syntax::on_pushButton_clicked()
{
    ui->listWidget->clear();

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
    main_syntax.get_elem = "";
    main_syntax.io_flag = 0;
    main_syntax.math_flag = 0;
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
    if(main_syntax.err == 0) {
        syntax::ui->listWidget->addItem(tr("语法、语义分析正确"));
        QMessageBox::about(this, tr("Successful!"), tr("语法分析正确"));
    }
    else if(main_syntax.err == 1) {
        syntax::ui->listWidget->addItem(tr("存在重定义变量"));
    }
    else if(main_syntax.err == 2) {
        syntax::ui->listWidget->addItem(tr("存在类型不匹配的变量"));
    }
    else if(main_syntax.err == 3) {
        syntax::ui->listWidget->addItem(tr("缺少一个分号';'"));
    }
    else if(main_syntax.err == 4) {
        syntax::ui->listWidget->addItem(tr("缺少一个'{'"));
    }
    else if(main_syntax.err == 5) {
        syntax::ui->listWidget->addItem(tr("缺少一个'}'"));
    }
    else if(main_syntax.err == 6) {
        syntax::ui->listWidget->addItem(tr("缺少一个'('"));
    }
    else if(main_syntax.err == 7) {
        syntax::ui->listWidget->addItem(tr("缺少一个')'"));
    }
    else if(main_syntax.err == 8) {
        syntax::ui->listWidget->addItem(tr("缺少一个']'"));
    }
    else if(main_syntax.err == 9) {
        syntax::ui->listWidget->addItem(tr("缺少标识符"));
    }
    else if(main_syntax.err == 10) {
        syntax::ui->listWidget->addItem(tr("主函数只能有一个，或主函数后有多余字符"));
    }
    else if(main_syntax.err == 11) {
        syntax::ui->listWidget->addItem(tr("主函数只能有一个"));
    }
    else if(main_syntax.err == 12) {
        syntax::ui->listWidget->addItem(tr("程序入口的输入非法"));
    }
    else if(main_syntax.err == 13) {
        syntax::ui->listWidget->addItem(tr("缺少一个'<'"));
    }
    else if(main_syntax.err == 14) {
        syntax::ui->listWidget->addItem(tr("缺少一个'>'"));
    }
    else if(main_syntax.err == 15) {
        syntax::ui->listWidget->addItem(tr("无该头文件"));
    }
    else if(main_syntax.err == 16) {
        syntax::ui->listWidget->addItem(tr("无该关键字"));
    }
    else if(main_syntax.err == 17) {
        syntax::ui->listWidget->addItem(tr("存在未声明变量"));
    }
    else if(main_syntax.err == 18) {
        syntax::ui->listWidget->addItem(tr("存在非法定义"));
    }
    else if(main_syntax.err == 19) {
        syntax::ui->listWidget->addItem(tr("赋值语句有误"));
    }
    else if(main_syntax.err == 20) {
        syntax::ui->listWidget->addItem(tr("缺少结构体对应的内部标识符"));
    }
    else if(main_syntax.err == 21) {
        syntax::ui->listWidget->addItem(tr("赋值语句缺少变量"));
    }
    else if(main_syntax.err == 22) {
        syntax::ui->listWidget->addItem(tr("未定义数组大小"));
    }
    else if(main_syntax.err == 23) {
        syntax::ui->listWidget->addItem(tr("声明语句缺少标识符"));
    }
    else if(main_syntax.err == 24) {
        syntax::ui->listWidget->addItem(tr("存在表达式语句错误"));
    }
    else if(main_syntax.err == 25) {
        syntax::ui->listWidget->addItem(tr("缺少函数名"));
    }
    else if(main_syntax.err == 26) {
        syntax::ui->listWidget->addItem(tr("存在非法声明语句"));
    }
    else if(main_syntax.err == 27) {
        syntax::ui->listWidget->addItem(tr("return语句不合法"));
    }
    else if(main_syntax.err == 28) {
        syntax::ui->listWidget->addItem(tr("cout输出语句不合法"));
    }
    else if(main_syntax.err == 29) {
        syntax::ui->listWidget->addItem(tr("函数的调用缺少参数"));
    }
    else if(main_syntax.err == 30) {
        syntax::ui->listWidget->addItem(tr("函数的调用不合法"));
    }
    else if(main_syntax.err == 31) {
        syntax::ui->listWidget->addItem(tr("函数未事先声明"));
    }
    else if(main_syntax.err == 32) {
        syntax::ui->listWidget->addItem(tr("命名空间语句有错误"));
    }
    else if(main_syntax.err == 33) {
        syntax::ui->listWidget->addItem(tr("无法调用cout,缺少头文件或命名空间语句"));
    }
    else if(main_syntax.err == 34) {
        syntax::ui->listWidget->addItem(tr("缺少cmath头文件"));
    }
    int x = main_lexical.repick.size();
    while(x) {
        x--;
        show_lex z = main_lexical.repick.front();
        main_lexical.repick.pop();
        main_lexical.repick.push(z);
        main_lexical.syntax_check.push(z);
    }
}

void syntax::on_pushButton_2_clicked()
{
    ui->listWidget->clear();
    close();
}

void syntax_analyse::read() {
    if(!main_lexical.syntax_check.empty()) {
        show_lex x = main_lexical.syntax_check.front();
        get_word = x.str;
        get_token = x.token;
        get_type = x.type_id;
        main_lexical.syntax_check.pop();
    }
    else {
        get_word = "";
        get_token = -1;
        get_type = -1;
    }
}

void syntax_analyse::error() {
    /*get_word = "";
    get_type = -1;
    get_token = -1;
    struct_flag = 0;
    main_flag = 0;
    cur_type = "";
    total_address = 0;
    table_flag = 0;
    --
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
    redefine_check.clear();
    tot = 1;*/
    //QMessageBox::warning(NULL, "Warning!", "语法有错误", QMessageBox::Yes);
    //exit(0);
}

//<程序>→<函数><程序>| struct标识符{<变量声明集合> };  <程序>|int main() {<主体>}
void syntax_analyse::program() {
    //struct
    if(get_word == "struct") {
        table_flag = 2;
        redefine_check.clear();
        read();
        //标识符
        if(get_type == 3) {
            if(str_redefine.count(get_word)) {
                err = 1;
                error();
                return;
            }
            else {
                str_redefine.insert(get_word);
                //设置结构体名作为类型
                x.appear_time = tot++;
                x.symbol_kind = "struct";
                x.symbol_type = "struct";
                x.symbol_name = get_word;
                symbol_table.push_back(x);
                read();
                if(get_word == "{") {
                    read();
                    declare_set();
                    if(err != 0) {
                        error();
                        return;
                    }
                    if(get_word == "}") {
                        read();
                        if(get_type == 3) {
                            read();
                            //--------------------------
                            arr();
                            if(get_word == ";") {
                                read();
                                program();
                                if(err != 0) {
                                    error();
                                    return;
                                }
                            }
                            else {
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                err = 3;
                                error();
                                return;
                            }
                        }
                        else if(get_word == ";") {
                            read();
                            program();
                            if(err != 0) {
                                error();
                                return;
                            }
                        }
                        else {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 3;
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 5;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 4;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 9;
            error();
            return;
        }
    }
    else if(get_word == "int") {
        x.appear_time = tot++;
        x.symbol_kind = "function";
        x.symbol_type = "int";
        read();
        if(get_word == "main") {
            table_flag = 1;
            main_quat.quat.push_back(main_quat.store_quat("main", "__", "__", "__"));
            x.symbol_name = "main";
            symbol_table.push_back(x);
            redefine_check.clear();
            if(!main_flag) {
                main_flag = 1;
                read();
                if(get_word == "(") {
                    read();
                    if(get_word == ")") {
                        read();
                        if(get_word == "{") {
                            read();
                            subject();
                            if(err != 0) {
                                error();
                                return;
                            }
                            if(get_word == "}") {
                                read();
                                if(get_word != "") {
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    err = 10;
                                    error();
                                    return;
                                }
                            }
                            else {
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                err = 5;
                                error();
                                return;
                            }
                        }
                        else {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 4;
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 7;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 6;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 11;
                error();
                return;
            }
        }
        else if(get_type == 3) {
            if(!fun_redefine.count(get_word)) {
                fun_redefine.insert(get_word);
                table_flag = 3;
                x.symbol_name = get_word;
                symbol_table.push_back(x);
                redefine_check.clear();
                read();
                if(get_word == "(") {
                    read();
                    declare2();
                    if(err != 0) {
                        error();
                        return;
                    }
                    if(get_word == ")") {
                        read();
                        if(get_word == "{") {
                            read();
                            subject();
                            if(err != 0) {
                                error();
                                return;
                            }
                            if(get_word == "}") {
                                read();
                                program();
                                if(err != 0) {
                                    error();
                                    return;
                                }
                            }
                            else {
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                err = 5;
                                error();
                                return;
                            }
                        }
                        else {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 4;
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 7;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 6;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 25;
            error();
            return;
        }
    }
    else if((get_token >= 52 && get_token <= 54) || (get_token == 56)) {
        if(get_token == 52) {
            x.symbol_type = "char";
        }
        else if(get_token == 53) {
            x.symbol_type = "float";
        }
        else if(get_token == 54) {
            x.symbol_type = "double";
        }
        else if(get_token == 56) {
            x.symbol_type = "void";
        }
        x.appear_time = tot++;
        x.symbol_kind = "function";
        read();
        table_flag = 3;
        if(get_type == 3) {
            x.symbol_name = get_word;
            read();
            if(get_word == "(") {
                read();
                declare2();
                if(err != 0) {
                    error();
                    return;
                }
                if(get_word == ")") {
                    read();
                    if(get_word == "{") {
                        read();
                        subject();
                        if(err != 0) {
                            error();
                            return;
                        }
                        if(get_word == "}") {
                            read();
                            program();
                            if(err != 0) {
                                error();
                                return;
                            }
                        }
                        else {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 5;
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 4;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 7;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 6;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 25;
            error();
            return;
        }
    }
    else if(get_word == "#") {
        read();
        headfile();
        if(err == 0) {
            program();
        }
        else {
            error();
            return;
        }
    }
    else if(get_word == "using") {
        read();
        if(get_word == "namespace") {
            read();
            if(get_word == "std") {
                read();
                io_flag++;
                if(get_word == ";") {
                    read();
                    program();
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 32;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 32;
            error();
            return;
        }
    }
    else {
        err = 12;
        error();
        return;
    }
}

//<头文件>→include<关键字>{#include<关键字>}
void syntax_analyse::headfile() {
    if(get_word == "include") {
        read();
        if(get_word == "<") {
            read();
            if(get_token >= 66 && get_token <= 70) {
                if(get_word == "cmath") {
                    fun_redefine.insert("abs");
                    fun_redefine.insert("min");
                    fun_redefine.insert("max");
                    math_flag++;
                }
                if(get_word == "iostream") {
                    io_flag++;
                }
                read();
                if(get_word == ">") {
                    read();
                    while(get_word == "#") {
                        read();
                        headfile();
                        if(err != 0) {
                            error();
                            return;
                        }
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 14;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 15;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 13;
            error();
            return;
        }
    }
    else {
        if(err != 0) {
            error();
            return;
        }
        err = 16;
        error();
        return;
    }
}

//<主体>→if(<表达式>){<主体>} else{<主体>} <主体>
//		|while(<表达式>){<主体>} <主体>
//      |for(<赋值语句>;<表达式>;<赋值语句>){<主体>}<主体>
//		|<类型> 标识符<变量声明>;<主体>
//		|标识符<赋值语句>;<主体>
//      |return 标识符|常量;<主体>
//      |cout << 标识符;<主体>
//		|空
void syntax_analyse::subject() {
    bool else_flag = 0;
    if(get_word == "break") {
        read();
        if(get_word == ";") {
            main_quat.quat.push_back(main_quat.store_quat("break", "__", "__", "__"));
            read();
            subject();
            if(err != 0) {
                error();
                return;
            }
        }
        else {
            err = 3;
            error();
            return;
        }
    }
    else if(get_word == "cout") {
        if(io_flag == 0) {
            err = 33;
            error();
            return;
        }
        else {
            read();
            if(get_word == "<<") {
                read();
                if(get_type == 3) {
                    main_quat.quat.push_back(main_quat.store_quat("out", get_word, "__", "__"));
                    if(!redefine_check.count(get_word)) {
                        err = 17;
                        error();
                        return;
                    }
                    else {
                        read();
                        if(get_word == ";") {
                            read();
                            subject();
                        }
                        else {
                            err = 3;
                            error();
                            return;
                        }
                    }
                }
                else {
                    err = 28;
                    error();
                    return;
                }
            }
            else {
                err = 28;
                error();
                return;
            }
        }
    }
    else if(get_word == "return") {
        read();
        if(get_type == 3) {
            if(!redefine_check.count(get_word)) {
                err = 17;
                error();
                return;
            }
            else {
                read();
                if(get_word == ";") {
                    read();
                    subject();
                }
                else {
                    err = 3;
                    error();
                    return;
                }
            }
        }
        else if(get_type == 4 || get_type == 5) {
            read();
            if(get_word == ";") {
                read();
                subject();
            }
            else {
                err = 3;
                error();
                return;
            }
        }
        else {
            err = 27;
            error();
            return;
        }
    }
    else if(get_word == "if") {
        read();
        if(get_word == "(") {
            left_bracket++;
            read();
            expression();
            get_quat.pop_back();
            main_quat.exp_quat();
            main_quat.quat.push_back(main_quat.store_quat("if", main_quat.str4, "__", "__"));
            if(err != 0) {
                error();
                return;
            }
            if(get_word == ")") {
                read();
                if(get_word == "{") {
                    read();
                    subject();
                    if(err != 0) {
                        error();
                        return;
                    }
                    if(get_word == "}") {
                        read();
                        if(get_word == "else") {
                            else_flag = 1;
                            main_quat.quat.push_back(main_quat.store_quat("else", "__", "__", "__"));
                            read();
                            if(get_word == "{") {
                                read();
                                subject();
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                main_quat.quat.push_back(main_quat.store_quat("if_end", "__", "__", "__"));
                                if(get_word == "}") {
                                    read();
                                    subject();
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                }
                                else {
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    err = 5;
                                    error();
                                    return;
                                }
                            }
                            else {
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                err = 4;
                                error();
                                return;
                            }
                        }
                        if(!else_flag) {
                            main_quat.quat.push_back(main_quat.store_quat("if_end", "__", "__", "__"));
                        }
                        //---------
                        if(err == 0) {
                            subject();
                            if(err != 0) {
                                error();
                                return;
                            }
                        }
                        else {
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 5;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 4;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 7;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 6;
            error();
            return;
        }
    }
    else if(get_word == "for") {
        read();
        if(get_word == "(") {
            left_bracket++;
            read();
            if(get_type == 3) {
                main_quat.quat.push_front(get_word);
                get_elem += get_word;
                if(redefine_check.count(get_word)) {
                    read();
                    assignment();
                    if(err != 0) {
                        error();
                        return;
                    }
                    if(get_word == ";") {
                        main_quat.quat.push_back(main_quat.store_quat("for", "__", "__", "__"));
                        cur_type = "";
                        read();
                        expression();
                        if(err != 0) {
                            error();
                            return;
                        }
                        get_quat.pop_back();
                        main_quat.exp_quat();
                        if(err != 0) {
                            error();
                            return;
                        }
                        main_quat.quat.push_back(main_quat.store_quat("do_for", main_quat.str4, "__", "__"));
                        if(get_word == ";") {
                            cur_type = "";
                            read();
                            if(get_type == 3) {
                                main_quat.quat.push_front(get_word);
                                get_elem += get_word;
                                if(redefine_check.count(get_word)) {
                                    read();
                                    assignment();
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    if(get_word == ")") {
                                        read();
                                        if(get_word == "{") {
                                            read();
                                            subject();
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            if(get_word == "}") {
                                                main_quat.quat.push_back(main_quat.store_quat("for_end", "__", "__", "__"));
                                                read();
                                                subject();
                                                if(err != 0) {
                                                    error();
                                                    return;
                                                }
                                            }
                                            else {
                                                if(err != 0) {
                                                    error();
                                                    return;
                                                }
                                                err = 5;
                                                error();
                                                return;
                                            }
                                        }
                                        else {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            err = 4;
                                            error();
                                            return;
                                        }
                                    }
                                    else {
                                        if(err != 0) {
                                            error();
                                            return;
                                        }
                                        err = 7;
                                        error();
                                        return;
                                    }
                                }
                                else {
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    err = 17;
                                    error();
                                    return;
                                }
                            }
                        }
                        else {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 3;
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 3;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 17;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 6;
            error();
            return;
        }
    }
    else if(get_word == "while") {
        read();
        if(get_word == "(") {
            main_quat.quat.push_back(main_quat.store_quat("while", "__", "__", "__"));
            left_bracket++;
            read();
            expression();
            get_quat.pop_back();
            main_quat.exp_quat();
            if(err != 0) {
                error();
                return;
            }
            if(get_word == ")") {
                read();
                if(get_word == "{") {
                    main_quat.quat.push_back(main_quat.store_quat("do_while", main_quat.str4, "__", "__"));
                    read();
                    subject();
                    if(err != 0) {
                        error();
                        return;
                    }
                    if(get_word == "}") {
                        main_quat.quat.push_back(main_quat.store_quat("while_end", "__", "__", "__"));
                        read();
                        subject();
                        if(err != 0) {
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 5;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 4;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 7;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 6;
            error();
            return;
        }
    }
    else if(get_type == 3) {
        main_quat.quat.push_front(get_word);
        get_elem += get_word;
        if(redefine_check.count(get_word)) {
            read();
            assignment();
            if(err != 0) {
                error();
                return;
            }
            if(get_word == ";") {
                cur_type = "";
                read();
                subject();
                if(err != 0) {
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 3;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 17;
            error();
            return;
        }
    }
    else if(get_word == "int") {//--------------------------------
        cur_type = "int";
        x.symbol_type = "int";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            //main_quat.quat.push_front(get_word);
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(!redefine_check.count(x.symbol_name)) {
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    get_elem = "";
                    cur_type = "";
                    read();
                    subject();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    else if(get_word == "char") {//--------------------------------
        cur_type = "char";
        x.symbol_type = "char";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            //main_quat.quat.push_front(get_word);
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(!redefine_check.count(x.symbol_name)) {
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    get_elem = "";
                    cur_type = "";
                    read();
                    subject();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    else if(get_word == "float") {//--------------------------------
        cur_type = "float";
        x.symbol_type = "float";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            //main_quat.quat.push_front(get_word);
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(!redefine_check.count(x.symbol_name)) {
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    get_elem = "";
                    cur_type = "";
                    read();
                    subject();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    else if(get_word == "double") {//--------------------------------
        cur_type = "double";
        x.symbol_type = "double";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            //main_quat.quat.push_front(get_word);
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(!redefine_check.count(x.symbol_name)) {
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    get_elem = "";
                    cur_type = "";
                    read();
                    subject();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    /*else if(get_word == "char") {
        read();
        if(get_type == 3) {
            read();
            declare();
            if(get_word == ";") {
                read();
            }
            else {
                error();
            }
            subject();
        }
        else {
            error();
        }
    }*/
    //结构体标识符
}

//<赋值语句>→<数组>=<复合表达式>
//          |.标识符<数组>=<复合表达式>
void syntax_analyse::assignment() {
    if(get_word == ".") {
        get_elem += get_word;
        read();
        if(get_type == 3) {
            get_elem += get_word;
            read();
            arr();
            if(err != 0) {
                error();
                return;
            }
            if(get_word == "=") {
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "+=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("+=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "-=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("-=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "*=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("*=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "/=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("/=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "%=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("%=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "&=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("&=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "|=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("|=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "^=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("^=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == "<<=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("<<=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else if(get_word == ">>=") {
                //main_quat.quat.push_front(get_elem);
                if(get_elem[get_elem.length()-1] == ']') {
                    main_quat.quat.pop_front();
                    main_quat.quat.push_front(get_elem);
                }
                get_elem = "";
                read();
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat(">>=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 19;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 20;
            error();
            return;
        }
    }
    else {
        arr();
        if(err != 0) {
            error();
            return;
        }
        if(get_word == "=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            /*if(get_word == "abs") {
                if(math_flag == 0) {
                    err = 34;
                    error();
                    return;
                }
                read();
                if(get_word == "(") {
                    read();
                    if(get_type == 3) {
                        if(!redefine_check.count(get_word)) {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 17;
                            error();
                            return;
                        }
                        else {
                            string assign = main_quat.quat.front();
                            main_quat.quat.pop_front();
                            main_quat.quat.push_back(main_quat.store_quat("if", "<", get_word, "0"));
                            main_quat.quat.push_back(main_quat.store_quat("=", "-"+get_word, "__", assign));
                            main_quat.quat.push_back(main_quat.store_quat("else", "__", "__", "__"));
                            main_quat.quat.push_back(main_quat.store_quat("=", get_word, "__", assign));
                            main_quat.quat.push_back(main_quat.store_quat("if_end", "__", "__", "__"));
                            read();
                            if(get_word == ")") {
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                //--------------------------------
                                read();
                            }
                            else {
                                if(err != 0) {
                                    error();
                                    return;
                                }
                                err = 7;
                                error();
                                return;
                            }
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 30;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 6;
                    error();
                    return;
                }
            }
            else if(get_word == "min") {
                string num1 = "", num2 = "";
                read();
                if(get_word == "(") {
                    read();
                    if(get_type == 3) {
                        num1 = get_word;
                        if(!redefine_check.count(get_word)) {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 17;
                            error();
                            return;
                        }
                        else {
                            read();
                            if(get_word == ",") {
                                read();
                                if(get_type == 3) {
                                    num2 = get_word;
                                    if(!redefine_check.count(get_word)) {
                                        if(err != 0) {
                                            error();
                                            return;
                                        }
                                        err = 17;
                                        error();
                                        return;
                                    }
                                    else {
                                        read();
                                        if(get_word == ")") {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            //--------------------------------
                                            string assign = main_quat.quat.front();
                                            main_quat.quat.pop_front();
                                            main_quat.quat.push_back(main_quat.store_quat("if", "<", num1, num2));
                                            main_quat.quat.push_back(main_quat.store_quat("=", num1, "__", assign));
                                            main_quat.quat.push_back(main_quat.store_quat("else", "__", "__", "__"));
                                            main_quat.quat.push_back(main_quat.store_quat("=", num2, "__", assign));
                                            main_quat.quat.push_back(main_quat.store_quat("if_end", "__", "__", "__"));
                                            read();
                                        }
                                        else {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            err = 7;
                                            error();
                                            return;
                                        }
                                    }
                                }
                                else {
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    err = 29;
                                    error();
                                    return;
                                }
                            }
                            else if(get_word == ")") {
                                read();
                            }
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 30;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 6;
                    error();
                    return;
                }
            }
            else if(get_word == "max") {
                string num1 = "", num2 = "";
                read();
                if(get_word == "(") {
                    read();
                    if(get_type == 3) {
                        num1 = get_word;
                        if(!redefine_check.count(get_word)) {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 17;
                            error();
                            return;
                        }
                        else {
                            read();
                            if(get_word == ",") {
                                read();
                                if(get_type == 3) {
                                    num2 = get_word;
                                    if(!redefine_check.count(get_word)) {
                                        if(err != 0) {
                                            error();
                                            return;
                                        }
                                        err = 17;
                                        error();
                                        return;
                                    }
                                    else {
                                        read();
                                        if(get_word == ")") {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            //--------------------------------
                                            string assign = main_quat.quat.front();
                                            main_quat.quat.pop_front();
                                            main_quat.quat.push_back(main_quat.store_quat("if", ">", num1, num2));
                                            main_quat.quat.push_back(main_quat.store_quat("=", num1, "__", assign));
                                            main_quat.quat.push_back(main_quat.store_quat("else", "__", "__", "__"));
                                            main_quat.quat.push_back(main_quat.store_quat("=", num2, "__", assign));
                                            main_quat.quat.push_back(main_quat.store_quat("if_end", "__", "__", "__"));
                                            read();
                                        }
                                        else {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            err = 7;
                                            error();
                                            return;
                                        }
                                    }
                                }
                                else {
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    err = 29;
                                    error();
                                    return;
                                }
                            }
                            else if(get_word == ")") {
                                read();
                            }
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 30;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 6;
                    error();
                    return;
                }
            }
            else*/
            if(fun_redefine.count(get_word)) {
                read();
                if(get_word == "(") {
                    read();
                    if(get_type == 3) {
                        if(!redefine_check.count(get_word)) {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 17;
                            error();
                            return;
                        }
                        else {
                            read();
                            if(get_word == ",") {
                                read();
                                if(get_type == 3) {
                                    if(!redefine_check.count(get_word)) {
                                        if(err != 0) {
                                            error();
                                            return;
                                        }
                                        err = 17;
                                        error();
                                        return;
                                    }
                                    else {
                                        read();
                                        if(get_word == ")") {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            //--------------------------------
                                            int sz = main_quat.quat.size();
                                            bool flag = 0;
                                            while(sz--) {
                                                string x = main_quat.quat.front();
                                                main_quat.quat.pop_front();
                                                main_quat.quat.push_back(x);
                                                if(x == main_quat.store_quat("main", "__", "__", "__")) {
                                                    flag = 1;
                                                    //main_quat.quat.pop_back();
                                                }
                                                if(!flag && x[0] == '(') {
                                                    main_quat.fun_quat.push_back(x);
                                                }
                                            }
                                            while(!main_quat.fun_quat.empty()) {
                                                main_quat.quat.push_back(main_quat.fun_quat.front());
                                                main_quat.fun_quat.pop_front();
                                            }
                                            string assign = main_quat.quat.front();
                                            main_quat.quat.pop_front();
                                            string tar = main_quat.quat.back();
                                            int len = tar.length();
                                            string target = "";
                                            for(int i = 5; i < len; i++) {
                                                char c = tar[i];
                                                if(c == ',') {
                                                    break;
                                                }
                                                target = target+c;
                                            }
                                            main_quat.quat.pop_back();
                                            main_quat.quat.push_back(main_quat.store_quat("=", target, "__", assign));
                                            read();
                                        }
                                        else {
                                            if(err != 0) {
                                                error();
                                                return;
                                            }
                                            err = 7;
                                            error();
                                            return;
                                        }
                                    }
                                }
                                else {
                                    if(err != 0) {
                                        error();
                                        return;
                                    }
                                    err = 29;
                                    error();
                                    return;
                                }
                            }
                            else if(get_word == ")") {
                                read();
                            }
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 30;
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 6;
                    error();
                    return;
                }
            }
            else if(get_type == 3 || get_type == 4 || get_type == 5 || get_word == "(") {
                composite_exp();
                if(err != 0) {
                    error();
                    return;
                }
                get_quat.pop_back();
                main_quat.exp_quat();
                //main_quat.opt_quat();
                string assign = main_quat.quat.front();
                main_quat.quat.pop_front();
                main_quat.quat.push_back(main_quat.store_quat("=", main_quat.str4, "__", assign));
                if(err != 0) {
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 31;
                error();
                return;
            }
        }
        else if(get_word == "+=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("+=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "-=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("-=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "*=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("*=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "/=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("/=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "%=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("%=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "&=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("&=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "|=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("|=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "^=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("^=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == "<<=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat("<<=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else if(get_word == ">>=") {
            //main_quat.quat.push_front(get_elem);
            if(get_elem[get_elem.length()-1] == ']') {
                main_quat.quat.pop_front();
                main_quat.quat.push_front(get_elem);
            }
            get_elem = "";
            read();
            composite_exp();
            if(err != 0) {
                error();
                return;
            }
            get_quat.pop_back();
            main_quat.exp_quat();
            string assign = main_quat.quat.front();
            main_quat.quat.pop_front();
            main_quat.quat.push_back(main_quat.store_quat(">>=", main_quat.str4, "__", assign));
            if(err != 0) {
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 19;
            error();
            return;
        }
    }
}

//<变量声明集合>→<类型> 标识符<变量声明>;<变量声明集合>|空
void syntax_analyse::declare_set() {
    if(get_word == "int") {
        cur_type = "int";
        x.symbol_type = "int";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(redefine_check.count(x.symbol_name)) {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
            else {
                //-----------------
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    cur_type = "";
                    read();
                    declare_set();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    else if(get_word == "char") {
        cur_type = "char";
        x.symbol_type = "char";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(redefine_check.count(x.symbol_name)) {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
            else {
                //-----------------
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    cur_type = "";
                    read();
                    declare_set();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    else if(get_word == "float") {
        cur_type = "float";
        x.symbol_type = "float";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(redefine_check.count(x.symbol_name)) {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
            else {
                //-----------------
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    cur_type = "";
                    read();
                    declare_set();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    else if(get_word == "double") {
        cur_type = "double";
        x.symbol_type = "double";
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(redefine_check.count(x.symbol_name)) {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
            else {
                //-----------------
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
                if(get_word == ";") {
                    cur_type = "";
                    read();
                    declare_set();
                    if(err != 0) {
                        error();
                        return;
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 3;
                    error();
                    return;
                }
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 18;
            error();
            return;
        }
    }
    //结构体标识符用来声明变量
}

//<变量声明>→ =<复合表达式><变量声明1>
//| [] =  {<复合表达式><复合表达式集合> } |<字符串>   <变量声明1>
//| [<I>]   =   {<复合表达式><复合表达式集合>} |<字符串>  <变量声明1>
//          ---------------------------------------
//|<变量声明1>
void syntax_analyse::declare() {
    if(get_word == "[") {
        x.symbol_kind = "array";
        read();
        if(get_word != "]") {
            I();
            if(err != 0) {
                error();
                return;
            }
            if(get_word == "]") {
                symbol_table.push_back(x);
                read();
                if(get_word == "=") {
                    read();
                    if(get_word == "{") {
                        read();
                        composite_exp();
                        if(err == 0) {
                            composite_exp_set();
                        }
                        else {
                            error();
                            return;
                        }
                        if(get_word == "}") {
                            read();
                            declare1();
                            if(err != 0) {
                                error();
                                return;
                            }
                        }
                        else {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 5;
                            error();
                            return;
                        }
                    }
                    else if(get_type == 7) {
                        if(cur_type != "char") {
                            if(err != 0) {
                                error();
                                return;
                            }
                            err = 2;
                            error();
                            return;
                        }
                        else {
                            read();
                            declare1();
                            if(err != 0) {
                                error();
                                return;
                            }
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 21;
                        error();
                        return;
                    }
                }
                //数组没有赋值
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 8;
                error();
                return;
            }
        }
        else {
            read();
            if(get_word == "=") {
                read();
                if(get_word == "{") {
                    arr_num = 0;
                    read();
                    composite_exp();
                    if(err == 0) {
                        composite_exp_set();
                    }
                    else {
                        error();
                        return;
                    }
                    if(get_word == "}") {
                        read();
                        declare1();
                        if(err != 0) {
                            error();
                            return;
                        }
                    }
                    else {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 5;
                        error();
                        return;
                    }
                }
                else if(get_type == 7) {
                    if(cur_type != "char") {
                        if(err != 0) {
                            error();
                            return;
                        }
                        err = 2;
                        error();
                        return;
                    }
                    else {
                        read();
                        declare1();
                        if(err != 0) {
                            error();
                            return;
                        }
                    }
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 21;
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 22;
                error();
                return;
            }
        }
    }
    else if(get_word == "=") {
        symbol_table.push_back(x);
        read();
        if(get_type == 7) {
            if(err != 0) {
                error();
                return;
            }
            err = 2;
            error();
            return;
        }
        else if(get_type == 6 && cur_type != "char") {
            if(err != 0) {
                error();
                return;
            }
            err = 2;
            error();
            return;
        }
        else {
            composite_exp();
            if(err == 0) {
                declare1();
                if(err != 0) {
                    error();
                    return;
                }
            }
            else {
                error();
                return;
            }
        }
    }
    else {
        symbol_table.push_back(x);
        declare1();
        if(err != 0) {
            error();
            return;
        }
    }
}

//<变量声明1> → , 标识符<变量声明>|空
void syntax_analyse::declare1() {
    //定义的是结构体变量
    if(get_word == ",") {
        x.symbol_type = cur_type;
        x.symbol_kind = "variable";
        read();
        if(get_type == 3) {
            x.symbol_name = get_word;
            x.appear_time = tot++;
            if(!redefine_check.count(x.symbol_name)) {
                redefine_check.insert(x.symbol_name);
                read();
                declare();
                if(err != 0) {
                    error();
                    return;
                }
                //symbol_table.push_back(x);
            }
            else {
                cur_type = "";
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 26;
            error();
            return;
        }
    }
}

//<变量声明2> → 类型 标识符 <变量声明3>| 空
void syntax_analyse::declare2() {
    if(get_token >= 51 && get_token <= 54) {
        if(get_token == 51) {
            x.symbol_type = "int";
        }
        else if(get_token == 52) {
            x.symbol_type = "char";
        }
        else if(get_token == 53) {
            x.symbol_type = "float";
        }
        else if(get_token == 54) {
            x.symbol_type = "double";
        }
        read();
        if(get_type == 3) {
            if(!redefine_check.count(get_word)) {
                redefine_check.insert(get_word);
                x.symbol_name = get_word;
                read();
                x.appear_time = tot++;
                x.symbol_kind = "var_f";
                symbol_table.push_back(x);
                declare3();
                if(err != 0) {
                    error();
                    return;
                }
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 1;
                error();
                return;
            }
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 23;
            error();
            return;
        }
    }
}

//<变量声明3> → , <变量声明2>|空
void syntax_analyse::declare3() {
    if(get_word == ",") {
        read();
        declare2();
        if(err != 0) {
            error();
            return;
        }
    }
}

//<复合表达式集合>→,<复合表达式><复合表达式集合>|空
void syntax_analyse::composite_exp_set() {
    if(get_word == ",") {
        read();
        composite_exp();
        if(err == 0) {
            composite_exp_set();
            if(err != 0) {
                error();
                return;
            }
        }
        else {
            error();
            return;
        }
    }
}

//<复合表达式>→<表达式>|<字符>|<字符串>
void syntax_analyse::composite_exp() {
    arr_num++;
    if(get_type == 6) {
        read();
    }
    else if(get_type == 7) {
        read();
    }
    else {
        //-----------------
        expression();
        if(err != 0) {
            error();
            return;
        }
    }
}

//<数组>→[<E>]|空
void syntax_analyse::arr() {
    if(get_word == "[") {
        get_elem += "[";
        read();
        //expression();
        I();
        if(err != 0) {
            error();
            return;
        }
        //----------------------------------------------
        if(get_word == "]") {
            get_elem += "]";
            read();
        }
        else {
            if(err != 0) {
                error();
                return;
            }
            err = 8;
            error();
            return;
        }
    }
}

//表达式---------------------------------------------------
//A->N{||N}
void syntax_analyse::expression() {
    //*********************************
    get_quat.push_back(get_word);
    N();
    if(err != 0) {
        error();
        return;
    }
    if(get_word == ")" && left_bracket == 0) {
        err = 6;
        error();
        return;
    }
    while(get_word == "||") {
        read();
        get_quat.push_back(get_word);
        N();
        if(err != 0) {
            error();
            return;
        }
    }
}

//N->M{&&M}
void syntax_analyse::N() {
    M();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "&&") {
        read();
        get_quat.push_back(get_word);
        M();
        if(err != 0) {
            error();
            return;
        }
    }
}

//M->X{|X}
void syntax_analyse::M() {
    X();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "|") {
        read();
        get_quat.push_back(get_word);
        X();
        if(err != 0) {
            error();
            return;
        }
    }
}

//X->Y{^Y}
void syntax_analyse::X() {
    Y();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "^") {
        read();
        get_quat.push_back(get_word);
        Y();
        if(err != 0) {
            error();
            return;
        }
    }
}

//Y->Z{&Z}
void syntax_analyse::Y() {
    Z();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "&") {
        read();
        get_quat.push_back(get_word);
        Z();
        if(err != 0) {
            error();
            return;
        }
    }
}

//Z->B{==B|!=B}
void syntax_analyse::Z() {
    B();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "==" || get_word == "!=") {
        read();
        get_quat.push_back(get_word);
        B();
        if(err != 0) {
            error();
            return;
        }
    }
}

//B->C{<C|<=C|>C|>=C}
void syntax_analyse::B() {
    C();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "<" || get_word == "<=" || get_word == ">" || get_word == ">=") {
        read();
        get_quat.push_back(get_word);
        C();
        if(err != 0) {
            error();
            return;
        }
    }
}

//C->E{<<E|>>E}
void syntax_analyse::C() {
    E();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "<<" || get_word == ">>") {
        read();
        get_quat.push_back(get_word);
        E();
        if(err != 0) {
            error();
            return;
        }
    }
}

//E->T{+T|-T}
void syntax_analyse::E() {
    T();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "+" || get_word == "-") {
        read();
        get_quat.push_back(get_word);
        T();
        if(err != 0) {
            error();
            return;
        }
    }
}

//T->F{*F|/F|%F}
void syntax_analyse::T() {
    F();
    if(err != 0) {
        error();
        return;
    }
    while(get_word == "*" || get_word == "/" || get_word == "%") {
        read();
        get_quat.push_back(get_word);
        F();
        if(err != 0) {
            error();
            return;
        }
    }
}

//F->F1
void syntax_analyse::F() {
    F1();
    if(err != 0) {
        error();
        return;
    }
}

//F1->!F1| 空 | I | (A) | (-F1)
void syntax_analyse::F1() {
    if(get_word == "!") {
        read();
        get_quat.push_back("!"+get_word);
        F1();
        if(err != 0) {
            error();
            return;
        }
    }
    else if(get_word == "(") {
        left_bracket++;
        read();
        if(get_word == "-") {
            read();
            get_quat.push_back("-"+get_word);
            F1();
            if(err != 0) {
                error();
                return;
            }
            if(get_word == ")") {
                left_bracket--;
                read();
                get_quat.push_back(get_word);
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 7;
                error();
                return;
            }
        }
        else {
            expression();
            if(err != 0) {
                error();
                return;
            }
            if(get_word == ")") {
                left_bracket--;
                read();
                get_quat.push_back(get_word);
            }
            else {
                if(err != 0) {
                    error();
                    return;
                }
                err = 7;
                error();
                return;
            }
        }
    }
    else {
        if(get_type == 1 || get_type == 2 || get_type == 6 || get_type == 7) {
            err = 24;
            error();
            return;
        }
        else {
            I();
            if(err != 0) {
                error();
                return;
            }
        }
    }
}

void syntax_analyse::I() {
    if(get_type == 3) {
        get_elem += get_word;
        if(!redefine_check.count(get_word)) {
            if(err != 0) {
                error();
                return;
            }
            err = 17;
            error();
            return;
        }
        else {
            read();
            if(get_word != "]")
                get_quat.push_back(get_word);
            //----------------------------------------------------------------
            if(get_word == ".") {
                get_elem += get_word;
                read();
                if(get_type == 3) {
                    get_elem += get_word;
                    read();
                }
                else {
                    if(err != 0) {
                        error();
                        return;
                    }
                    err = 20;
                    error();
                    return;
                }
            }
            //else
            arr();
            if(err != 0) {
                error();
                return;
            }
        }
        /*read();
        arr();*/
    }
    else if(get_type == 4) {
        get_elem += get_word;
        int len = get_word.length();
        int tt = 1;
        int ans = 0;
        for(int i = 0; i < len; i++) {
            ans += get_word[i]-'0';
            ans *= tt;
            tt *= 10;
        }
        x.arr_len = ans;
        read();
        if(get_word != "]")
            get_quat.push_back(get_word);
    }
    else if(get_type == 5) {
        get_elem += get_word;
        read();
        if(get_word != "]")
            get_quat.push_back(get_word);
    }
    else {
        if(err != 0) {
            error();
            return;
        }
        err = 24;
        error();
        return;
    }
}

void syntax_analyse::solve() {
    main_quat.current_num = 1;
    while(!main_quat.quat.empty()) main_quat.quat.pop_back();
    read();
    program();
}
