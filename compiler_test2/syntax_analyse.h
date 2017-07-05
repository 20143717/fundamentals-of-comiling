#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H

#include "lexical_analyse.h"

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <QMessageBox>

using namespace std;

extern lexical_analyse main_lexical;

class syntax_analyse {
public:
    void read();//读入
    void error();//报错
    void program();//<程序>
    void function();//<函数>
    void data_type();//<数据类型>
    void data_type1();//<数据类型1>
    void arr();//<数组>
    void declare();//<变量声明>
    void declare1();//<变量声明1>
    void declare2();//<变量声明2>
    void declare3();//<变量声明3s>
    void declare_set();//<变量声明集合>
    void subject();//<主体>
    void assignment();//<赋值>
    void expression();//<表达式>
    void composite_exp();//<复合表达式>
    void composite_exp_set();//<复合表达式集合>
    void headfile();//<头文件>
    void I();//<常量>
    void N();
    void M();
    void X();
    void Y();
    void Z();
    void B();
    void C();
    void E();
    void T();
    void F();
    void F1();
    void solve();

    string get_word;
    int get_type;
    int get_token;
    int err;
    bool struct_flag;
    bool main_flag;
    int table_flag;
    int arr_num;
    string cur_type;
    int left_bracket;
    string get_elem;

    struct symbol {
        string symbol_name;
        string symbol_kind;
        string symbol_type;
        int symbol_address;
        int appear_time;
        int arr_len;
        bool operator < (const symbol &a) const {
            if(symbol_name == a.symbol_name) {
                if(symbol_type == a.symbol_type) {
                    if(symbol_kind == a.symbol_kind) {
                        if(symbol_address == a.symbol_address) {
                            if(arr_len == a.arr_len) {
                                return appear_time < a.appear_time;
                            }
                            return arr_len < a.arr_len;
                        }
                        return symbol_address < a.symbol_address;
                    }
                    return symbol_kind < a.symbol_kind;
                }
                return symbol_type < a.symbol_type;
            }
            return symbol_name < a.symbol_name;
        }
    };
    symbol x, show_table;
    int tot;
    int total_address;
    int io_flag, math_flag;
    deque<symbol> symbol_table, struct_table, function_table, array_table, const_table;
    set<string> redefine_check, fun_redefine, str_redefine;
    deque<string> get_quat;
};

#endif // SYNTAX_ANALYSE_H
