#ifndef LEXICAL_ANALYSE_H
#define LEXICAL_ANALYSE_H

#include <QString>

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <string>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

struct lexical_word {
    string str;
    int token;
};

struct show_lex {
    string str;
    int type_id;
    int token;
};

class lexical_analyse {
public:
    lexical_word key_word[100] = {
        {"int", 51}, {"char", 52}, {"float", 53}, {"double", 54}, {"main", 55}, {"void", 56},
        {"if", 57}, {"else", 58}, {"while", 59}, {"for", 60}, {"continue", 61}, {"break", 62},
        {"return", 63}, {"struct", 64}, {"include", 65}, {"cstdio", 66}, {"cstdlib", 67},
        {"cstring", 68}, {"cmath", 69}, {"iostream", 70}, {"using", 71}, {"namespace", 72},
        {"std", 73}, {"abs", 74}, {"min", 75}, {"max", 76}
    };

    lexical_word bound_word[100] = {
        {"=", 1}, {">", 2}, {"<", 3}, {">=", 4}, {"<=", 5}, {"==", 6}, {"!=", 7}, {"+", 8},
        {"-", 9}, {"*", 10}, {"/", 11}, {"%", 12}, {"<<", 13}, {">>", 14}, {"&", 15}, {"|", 16},
        {"!", 17}, {"^", 18}, {"&&", 19}, {"||", 20}, {",", 21}, {";", 22}, {"{", 23}, {"}", 24},
        {"[", 25}, {"]", 26}, {"(", 27}, {")", 28}, {"\'", 29}, {"\"", 30}, {"+=", 31}, {"-=", 32},
        {"*=", 33}, {"/=", 34}, {"%=", 35}, {"<<=", 36}, {">>=", 37}, {"&=", 38}, {"|=", 39}, {"^=", 40},
        {".", 41}, {"#", 42}
    };

    map<string, int> key_id;
    map<string, int> bound_id;

    queue<show_lex> show_word;
    queue<show_lex> syntax_check;
    queue<show_lex> repick;

    QString ans = "";
    QString sss = "";

    int err = 1;

    void init() {
        key_id.clear();
        bound_id.clear();
        while(!show_word.empty()) show_word.pop();
        while(!syntax_check.empty()) syntax_check.pop();
        while(!repick.empty()) repick.pop();
        for(int i = 0; i < 26; i++) {
            key_id[key_word[i].str] = key_word[i].token;
        }
        for(int i = 0; i < 42; i++) {
            bound_id[bound_word[i].str] = bound_word[i].token;
        }
    }

    //判断是否为关键字
    bool is_key(string ss) {
        for(int i = 0; i < 26; i++) {
            if(key_word[i].str == ss) {
                return true;
            }
        }
        return false;
    }

    //判断是否为界符
    bool is_bound(string ss) {
        for(int i = 0; i < 42; i++) {
            if(bound_word[i].str == ss) {
                return true;
            }
        }
        return false;
    }

    //判断是否为字母
    bool is_letter(char c) {
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            return true;
        }
        return false;
    }

    //判断是否为数字
    bool is_number(char c) {
        if(c >= '0' && c <= '9') {
            return true;
        }
        return false;
    }

    //判断是否是运算符
    bool is_operator(string tmp) {
        if(tmp == "=" || tmp == "+" || tmp == "-" || tmp == "*" || tmp == "/" || tmp == "%" || tmp == "&" || tmp == "|" || tmp == "!" || tmp == "^") {
            return true;
        }
        return false;
    }

    void solve(QString str) {
        init();
        int len = str.length();
        QByteArray ss = str.toLatin1();
        char *mm = ss.data();
        string tmp = "";
        string bound_tmp = "";
        bool point = 0;
        for(int i = 0; i < len; i++) {
            if(mm[i] == ' ' || mm[i] == '\n' || mm[i] == '\t' || mm[i] == '\r') {
                continue;
            }
            //滤掉注释
            if(mm[i] == '/' && mm[i+1] == '/') {
                while(mm[i] != '\n') {
                    i++;
                }
                continue;
            }
            if(mm[i] == '/' && mm[i+1] == '*') {
                i += 2;
                while(!(mm[i] == '*' && mm[i+1] == '/') && i < len) {
                    i++;
                }
                i += 2;
                i = min(len-1, i);
                continue;
            }
            //分离数字
            if(is_number(mm[i])) {
                point = 0;
                tmp = "";
                while(is_number(mm[i])) {
                    tmp += mm[i];
                    i++;
                }
                if(mm[i] == '.') {
                    i++;
                    point = 1;
                    if(is_number(mm[i])) {
                        tmp += '.';
                        while(is_number(mm[i])) {
                            tmp += mm[i];
                            i++;
                        }
                        if(!is_number(mm[i])) {
                            bound_tmp = "";
                            bound_tmp += mm[i];
                            if(!is_bound(bound_tmp) || bound_tmp == ".") {
                                err = 0;
                                return;
                            }
                        }
                    }
                    else {
                        err = 0;
                        return;
                    }
                }
                else if(mm[i] != ' ' && mm[i] != '\n' && mm[i] != '\t' && mm[i] != '\r') {
                    string judge = "";
                    judge += mm[i];
                    if(!is_bound(judge)) {
                        err = 0;
                        return;
                    }
                }
                show_lex x;
                x.str = tmp;
                if(point) {
                    x.token = 5;
                    x.type_id = 5;
                }
                else {
                    x.token = 4;
                    x.type_id = 4;
                }
                show_word.push(x);
                syntax_check.push(x);
                repick.push(x);
                i--;
            }
            //分离字母
            else if(is_letter(mm[i]) || mm[i] == '_') {
                tmp = "";
                while(is_letter(mm[i]) || is_number(mm[i]) || mm[i] == '_') {
                    tmp += mm[i];
                    i++;
                }
                i--;
                show_lex x;
                x.str = tmp;
                if(is_key(tmp)) {
                    x.token = key_id[tmp];
                    x.type_id = 1;
                }
                else {
                    x.token = 3;
                    x.type_id = 3;
                }
                show_word.push(x);
                syntax_check.push(x);
                repick.push(x);
            }
            //分离字符、字符串常量
            else if(mm[i] == '\'' || mm[i] == '\"') {
                tmp = "";
                tmp += mm[i];
                if(tmp == "\'") {
                    i++;
                    tmp += mm[i];
                    i++;
                    if(mm[i] != '\'') {
                        err = 0;
                        return;
                    }
                    tmp += mm[i];
                    show_lex x;
                    x.str = tmp;
                    x.token = 6;
                    x.type_id = 6;
                    show_word.push(x);
                    syntax_check.push(x);
                    repick.push(x);
                }
                else if(tmp == "\"") {
                    i++;
                    while(mm[i] != '\"' && i < len) {
                        tmp += mm[i];
                        i++;
                    }
                    if(i == len) {
                        err = 0;
                        return;
                    }
                    tmp += mm[i];
                    show_lex x;
                    x.str = tmp;
                    x.token = 7;
                    x.type_id = 7;
                    show_word.push(x);
                    syntax_check.push(x);
                    repick.push(x);
                }
            }
            //分离界符
            else {
                tmp = "";
                tmp += mm[i];
                i++;
                if(tmp == "<") {
                    if(mm[i] == '=') {
                        tmp += mm[i];
                    }
                    else if(mm[i] == '<') {
                        tmp += mm[i];
                        i++;
                        if(mm[i] == '=') {
                            tmp += mm[i];
                        }
                        else {
                            i--;
                        }
                    }
                    else {
                        i--;
                    }
                }
                else if(tmp == ">") {
                    if(mm[i] == '=') {
                        tmp += mm[i];
                    }
                    else if(mm[i] == '>') {
                        tmp += mm[i];
                        i++;
                        if(mm[i] == '=') {
                            tmp += mm[i];
                        }
                        else {
                            i--;
                        }
                    }
                    else {
                        i--;
                    }
                }
                else if(is_operator(tmp)) {
                    if(mm[i] == '=') {
                        tmp += mm[i];
                    }
                    else if(tmp == "&" && mm[i] == '&') {
                        tmp += mm[i];
                    }
                    else if(tmp == "|" && mm[i] == '|') {
                        tmp += mm[i];
                    }
                    else {
                        i--;
                    }
                }
                else {
                    i--;
                }
                show_lex x;
                x.str = tmp;
                x.token = bound_id[tmp];
                x.type_id = 2;
                show_word.push(x);
                syntax_check.push(x);
                repick.push(x);
            }
        }
    }
};

#endif // LEXICAL_ANALYSE_H
