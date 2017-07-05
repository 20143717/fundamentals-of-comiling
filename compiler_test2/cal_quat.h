#ifndef CAL_QUAT_H
#define CAL_QUAT_H

#include "syntax.h"
#include <QtDebug>

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <sstream>

using namespace std;

extern syntax_analyse main_syntax;

class cal_quat {
public:
    string num, x;
    stack<string> stk1, stk2;
    deque<string> quat, operate_num, create, last_quat, fun_quat, display;
    deque<string> show_quat[111], optimize_quat[111];
    int current_num;
    string str1, str2, str3, str4;
    map<string, string> tar_change, exp_change;
    set<string> tar_check, exp_check;
    deque<string> ret_target, del_tar, ret_for;
    struct separate {
        string s1, s2, s3, s4;
    };
    deque<separate> new_quat;
    separate ans;
    separate quat_again[1111];
    bool vis[1111];
    int block_num;

    int priority(string x) {
        if(x == "||") return 1;
        if(x == "&&") return 2;
        if(x == "|") return 3;
        if(x == "^") return 4;
        if(x == "&") return 5;
        if(x == "==" || x == "!=") return 6;
        if(x == ">" || x == "<" || x == ">=" || x == "<=") return 7;
        if(x == "<<" || x == ">>") return 8;
        if(x == "+" || x == "-") return 9;
        if(x == "*" || x == "/" || x == "%") return 10;
        return -1;
    }

    bool is_operator(string x) {
        if(x == "*" || x == "/" || x == "%" || x == "+" || x == "-" || x == "<<" || x == ">>"
         || x == ">" || x == "<" || x == ">=" || x == "<=" || x == "==" || x == "!=" || x == "&"
         || x == "^" || x == "|" || x == "&&" || x == "||" || x == "(" || x == ")") {
            return true;
        }
        return false;
    }

    void RPN() {
        while(!stk1.empty()) stk1.pop();
        while(!stk2.empty()) stk2.pop();
        num = "";
        x = "";
        stk1.push("#");
        while(!main_syntax.get_quat.empty()) {
            num = main_syntax.get_quat.front();
            main_syntax.get_quat.pop_front();
            if(!is_operator(num)) {
                stk2.push(num);
            }
            int token = main_lexical.bound_id[num];
            switch(token) {
                case 27: {
                    x = "";
                    x += num;
                    stk1.push(x);
                    x = "";
                    break;
                }
                case 28: {
                    while(stk1.top() != "(") {
                        x = stk1.top();
                        stk1.pop();
                        stk2.push(x);
                    }
                    stk1.pop();
                    break;
                }
                case 20: {
                    for(x = stk1.top(); x != "#" && priority(x) == 1; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 19: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 2; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 16: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 3; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 18: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 4; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 15: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 5; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 6:
                case 7: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 6; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 2:
                case 3:
                case 4:
                case 5: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 7; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 13:
                case 14: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 8; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 8:
                case 9: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 9; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
                case 10:
                case 11:
                case 12: {
                    for(x = stk1.top(); x != "#" && priority(x) >= 10; x = stk1.top()) {
                        if(x == "(") break;
                        else {
                            string xx = stk1.top();
                            stk1.pop();
                            stk2.push(xx);
                        }
                    }
                    x = "";
                    x += num;
                    stk1.push(x);
                    break;
                }
            }
        }
        while(!stk1.empty() && stk1.top() != "#") {
            x = stk1.top();
            stk1.pop();
            stk2.push(x);
        }
    }

    string store_quat(string str1, string str2, string str3, string str4) {
        string res = "";
        res += "( ";
        res += str1;
        res += ", ";
        res += str2;
        res += ", ";
        res += str3;
        res += ", ";
        res += str4;
        res += " )";
        return res;
    }

    string get_current_string(int t) {
        string res = "";
        while(t) {
            string x = "";
            x += (t%10)+'0';
            t /= 10;
            res = x+res;
        }
        res = "t"+res;
        return res;
    }

    void exp_quat() {
        RPN();
        while(!create.empty()) create.pop_back();
        while(!operate_num.empty()) operate_num.pop_back();
        int cnt = stk2.size();
        while(!stk2.empty()) {
            operate_num.push_front(stk2.top());
            stk2.pop();
        }
        //qDebug() << cnt;
        if(cnt < 3) {//处理赋值语句的四元式
            string x = operate_num.front();
            operate_num.pop_front();
            str4 = get_current_string(current_num++);
            quat.push_back(store_quat("=", x, "__", str4));
            separate tmp1 = sep_quat(quat.back());
            string cur = quat.back();
            quat.pop_back();
            separate tmp2 = sep_quat(quat.back());
            if(tmp1.s1 == "=" && tmp2.s1 == "=" && tmp2.s2 == tmp1.s4) {
                quat.pop_back();
                quat.push_back(store_quat("=", tmp1.s2, "__", tmp2.s4));
            }
            else {
                quat.push_back(cur);
            }
        }
        else {
            while(!operate_num.empty()) {
                string x = operate_num.front();
                operate_num.pop_front();
                if(!is_operator(x)) {
                    create.push_back(x);
                }
                else {
                    str1 = x;
                    str3 = create.back();
                    create.pop_back();
                    str2 = create.back();
                    create.pop_back();
                    str4 = get_current_string(current_num++);
                    create.push_back(str4);
                    quat.push_back(store_quat(str1, str2, str3, str4));
                }
            }
        }
    }

    separate sep_quat(string ss) {
        separate x;
        int len = ss.length();
        int pos;
        x.s1 = "";
        x.s2 = "";
        x.s3 = "";
        x.s4 = "";
        for(int i = 2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.s1 += ss[i];
            }
        }
        for(int i = pos+2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.s2 += ss[i];
            }
        }
        for(int i = pos+2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.s3 += ss[i];
            }
        }
        for(int i = pos+2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.s4 += ss[i];
            }
        }
        return x;
    }

    bool is_number(string x) {
        int len = x.length();
        for(int i = 0; i < len; i++) {
            if(x[i] == '-') {
                continue;
            }
            if((x[i] >= '0' && x[i] <= '9') || x[i] == '.') {
                continue;
            }
            else {
                return false;
            }
        }
        return true;
    }

    double get_num(string x) {
        int len = x.length();
        double res = 0;
        int ok = 0;
        int neg = 0;
        for(int i = 0; i < len; i++) {
            if(x[i] == '-') {
                neg = 1;
                continue;
            }
            if(x[i] >= '0' && x[i] <= '9') {
                if(!ok) {
                    res = res*10+x[i]-'0';
                }
                else {
                    res += (x[i]-'0')*pow(10.0, ok-i);
                }
            }
            else if(x[i] == '.') {
                ok = i;
            }
            else {
                return 0;
            }
        }
        if(neg) {
            res = -res;
        }
        return res;
    }

    string d_to_s(double x) {
        ostringstream os;
        os << x;
        return os.str();
    }

    /*void del_quat(string ss) {
        while(!del_tar.empty()) {
            del_tar.pop_back();
        }
        separate x;
        x.s4 = "--";
        while(x.s4 != ss) {
            x = sep_quat(last_quat.front());
            if(x.s4 == ss) {
                last_quat.pop_front();
                break;
            }
            else {
                string tmp = last_quat.front();
                last_quat.pop_front();
                del_tar.push_back(tmp);
            }
        }
        while(!del_tar.empty()) {
            string tmp = del_tar.back();
            del_tar.pop_back();
            last_quat.push_front(tmp);
        }
    }*/

    void get_block() {
        /*int sz = quat.size();
        while(sz--) {
            separate x = sep_quat(quat.front());
            string tmp = quat.front();
            quat.pop_front();
            quat.push_back(tmp);
            if(x.s1[0] != 'i' && x.s1[0] != 'e' && x.s1[0] != 'w' && x.s1[0] != 'd' && x.s1[0] != 'f') {
                show_quat[block_num].push_back(tmp);
                optimize_quat[block_num].push_back(tmp);
            }
            else {
                show_quat[block_num].push_back(tmp);
                optimize_quat[block_num].push_back(tmp);
                block_num++;
            }
        }*/
        int sz = display.size();
        while(sz--) {
            separate x = sep_quat(display.front());
            string tmp = display.front();
            display.pop_front();
            display.push_back(tmp);
            if(x.s1[0] != 'i' && x.s1[0] != 'e' && x.s1[0] != 'w' && x.s1[0] != 'd' && x.s1[0] != 'f' && x.s1[0] != 'o') {
                show_quat[block_num].push_back(tmp);
                optimize_quat[block_num].push_back(tmp);
            }
            else {
                show_quat[block_num].push_back(tmp);
                optimize_quat[block_num].push_back(tmp);
                block_num++;
            }
        }
    }

    void opt_quat() {
        get_block();
        exp_change.clear();
        tar_change.clear();
        exp_check.clear();
        tar_check.clear();
        string op = "", num1 = "", num2 = "", target = "";
        separate x;
        int sz;

        //optimize-----------------------------------
        int total = 0;
        while(total <= block_num) {
            for(int i = 0; i < 20; i++) {
                tar_change.clear();
                exp_change.clear();
                tar_check.clear();
                exp_check.clear();
                while(!show_quat[total].empty()) {
                    show_quat[total].pop_back();
                }
                //---------------------------
                while(!optimize_quat[total].empty()) {
                    x = sep_quat(optimize_quat[total].front());
                    optimize_quat[total].pop_front();
                    op = x.s1;
                    num1 = x.s2;
                    num2 = x.s3;
                    target = x.s4;
                    if(op == "=" && target[0] == 't') {
                        x = sep_quat(optimize_quat[total].front());
                        optimize_quat[total].pop_front();
                        if(x.s1 == "if" || x.s1 == "while" || x.s1 == "for") {
                            show_quat[total].push_back(store_quat(x.s1, num1, "__", "__"));
                        }
                        else if(x.s1 == "=") {
                            show_quat[total].push_back(store_quat("=", num1, num2, x.s4));
                        }
                    }
                    else if(op == "=" && target[0] != 't' && num1[0] == 't') {
                        x = sep_quat(show_quat[total].back());
                        show_quat[total].pop_back();
                        show_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, target));
                    }
                    else if(is_number(num1) && is_number(num2)) {
                        double dnum1 = get_num(num1);
                        double dnum2 = get_num(num2);
                        double ansnum;
                        if(op == "+") {
                            ansnum = dnum1+dnum2;
                        }
                        else if(op == "-") {
                            ansnum = dnum1-dnum2;
                        }
                        else if(op == "*") {
                            ansnum = dnum1*dnum2;
                        }
                        else if(op == "/") {
                            ansnum = dnum1/dnum2;
                        }
                        else if(op == "%") {
                            ansnum = ((int)(dnum1))%((int)(dnum2));
                        }
                        else if(op == "&") {
                            ansnum = ((int)(dnum1))&((int)(dnum2));
                        }
                        else if(op == "|") {
                            ansnum = ((int)(dnum1))|((int)(dnum2));
                        }
                        else if(op == "^") {
                            ansnum = ((int)(dnum1))^((int)(dnum2));
                        }
                        else if(op == "&&") {
                            ansnum = ((dnum1))&&((dnum2));
                        }
                        else if(op == "||") {
                            ansnum = ((dnum1))||((dnum2));
                        }
                        else if(op == "==") {
                            ansnum = ((dnum1))==((dnum2));
                        }
                        else if(op == "!=") {
                            ansnum = ((dnum1))!=((dnum2));
                        }
                        else if(op == ">") {
                            ansnum = ((dnum1))>((dnum2));
                        }
                        else if(op == ">=") {
                            ansnum = ((dnum1))>=((dnum2));
                        }
                        else if(op == "<") {
                            ansnum = ((dnum1))<((dnum2));
                        }
                        else if(op == "<=") {
                            ansnum = ((dnum1))<=((dnum2));
                        }
                        else if(op == "<<") {
                            ansnum = ((int)(dnum1))<<((int)(dnum2));
                        }
                        else if(op == ">>") {
                            ansnum = ((int)(dnum1))>>((int)(dnum2));
                        }
                        string ans_ss;
                        ans_ss = d_to_s(ansnum);
                        show_quat[total].push_back(store_quat("=", ans_ss, "__", target));
                    }
                    else {
                        show_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                    }
                }
                //-------------------------
                sz = show_quat[total].size();
                while(sz--) {
                    x = sep_quat(show_quat[total].front());
                    string tmp = show_quat[total].front();
                    show_quat[total].pop_front();
                    if(!exp_check.count(x.s1+x.s2+x.s3)) {
                        if(x.s1 == "=") {
                            tar_change[x.s4] = x.s2;
                            tar_change[x.s2] = x.s2;
                            exp_check.insert(x.s1+x.s2+x.s3);
                            if(x.s4[0] != 't') {
                                show_quat[total].push_back(tmp);
                            }
                        }
                        else {
                            exp_check.insert(x.s1+x.s2+x.s3);
                            exp_change[x.s1+x.s2+x.s3] = x.s4;
                            tar_change[x.s4] = "";
                            show_quat[total].push_back(tmp);
                        }
                        //-------------------------
                    }
                    else {
                        if(x.s1 == "=") {
                            tar_change[x.s4] = x.s2;
                        }
                        else {
                            tar_change[x.s4] = exp_change[x.s1+x.s2+x.s3];
                        }
                    }
                }

                sz = show_quat[total].size();
                while(sz--) {
                    x = sep_quat(show_quat[total].front());
                    string tmp = show_quat[total].front();
                    show_quat[total].pop_front();
                    if(tar_change[x.s2] != "") {
                        x.s2 = tar_change[x.s2];
                        if(tar_change[x.s3] != "") {
                            x.s3 = tar_change[x.s3];
                            show_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                            optimize_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                        }
                        else {
                            show_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                            optimize_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                        }
                    }
                    else if(tar_change[x.s3] != "") {
                        x.s3 = tar_change[x.s3];
                        show_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                        optimize_quat[total].push_back(store_quat(x.s1, x.s2, x.s3, x.s4));
                    }
                    else {
                        show_quat[total].push_back(tmp);
                        optimize_quat[total].push_back(tmp);
                    }
                }
            }
            total++;
        }
    }

    void get_last_quat() {
        int show_sz = 0;
        while(show_sz <= block_num) {
            int sz = show_quat[show_sz].size();
            while(sz--) {
                string x = show_quat[show_sz].front();
                show_quat[show_sz].pop_front();
                show_quat[show_sz].push_back(x);
                last_quat.push_back(x);
            }
            show_sz++;
        }
    }

    void opt_again() {
        get_last_quat();
        int len = last_quat.size();
        for(int i = 0; i < len; i++) {
            quat_again[i] = sep_quat(last_quat.front());
            last_quat.pop_front();
        }
        memset(vis, 0, sizeof vis);
        bool mid = 0;
        for(int i = 0; i < len; i++) {
            if(quat_again[i].s4[0] != 't') {
                for(int j = i+1; j < len; j++) {
                    if(quat_again[j].s2 == quat_again[i].s4 || quat_again[j].s3 == quat_again[i].s4) {
                        mid = 1;
                    }
                    if(!mid && (quat_again[j].s4 == quat_again[i].s4)) {
                        vis[i] = 1;
                    }
                }
                mid = 0;
            }
        }
        for(int i = 0; i < len; i++) {
            if(!vis[i]) {
                last_quat.push_back(store_quat(quat_again[i].s1, quat_again[i].s2, quat_again[i].s3, quat_again[i].s4));
            }
        }

        //for_end
        len = last_quat.size();
        for(int i = 0; i < len; i++) {
            quat_again[i] = sep_quat(last_quat.front());
            last_quat.pop_front();
        }
        //bool flag;
        int t = 0;
        while(quat_again[t].s1 != "do_for" && t < len) {
            last_quat.push_back(store_quat(quat_again[t].s1, quat_again[t].s2, quat_again[t].s3, quat_again[t].s4));
            t++;
            if(quat_again[t].s1 == "do_for") {
                last_quat.push_back(store_quat(quat_again[t].s1, quat_again[t].s2, quat_again[t].s3, quat_again[t].s4));
                while(quat_again[len-1].s1 != "for_end") {
                    ret_for.push_front(store_quat(quat_again[len-1].s1, quat_again[len-1].s2, quat_again[len-1].s3, quat_again[len-1].s4));
                    len--;
                }
                if(quat_again[len-1].s1 == "for_end") {
                    ret_for.push_front(store_quat(quat_again[len-1].s1, quat_again[len-1].s2, quat_again[len-1].s3, quat_again[len-1].s4));
                    ret_for.push_front(store_quat(quat_again[t+1].s1, quat_again[t+1].s2, quat_again[t+1].s3, quat_again[t+1].s4));
                    t += 2;
                    len--;
                }
            }
        }
        while(!ret_for.empty()) {
            last_quat.push_back(ret_for.front());
            ret_for.pop_front();
        }
    }

    /*void del_if() {
        memset(vis, 0, sizeof vis);
        int len = last_quat.size();
        int pos1 = -1, pos2 = -1;
        for(int i = 0; i < len; i++) {
            quat_again[i] = sep_quat(last_quat.front());
            last_quat.pop_front();
        }
        for(int i = 0; i < len; i++) {
            if(quat_again[i].s1 == "if" && quat_again[i].s2 == "1") {
                if(!vis[i]) {
                    vis[i] = 1;
                }
                for(int j = len-1; j >= 0; j--) {
                    if(quat_again[j].s1 == "else") {
                        if(!vis[j]) {
                            vis[j] = 1;
                            pos2 = j;
                            break;
                        }
                    }
                }

                pos1 = -1;
            }
            else if(quat_again[i].s1 == "if" && quat_again[i].s2 == "0") {
                if(!vis[i]) {
                    vis[i] = 1;
                    pos1 = i;
                }
                for(int j = i+1; j < len; j++) {
                    if(quat_again[j].s1 == "else") {
                        if(!vis[j]) {
                            vis[j] = 1;
                            pos2 = j;
                            break;
                        }
                    }
                }
                for(int j = pos1; j <= pos2; j++) {
                    if(!vis[j]) {
                        vis[j] = 1;
                    }
                }
                for(int j = len-1; j >= 0; j--) {
                    if(quat_again[j].s1 == "if_end") {
                        if(!vis[j]) {
                            vis[j] = 1;
                            break;
                        }
                    }
                }
                pos1 = -1;
                pos2 = -1;
            }
        }
        for(int i = 0; i < len; i++) {
            if(!vis[i]) {
                last_quat.push_back(store_quat(quat_again[i].s1, quat_again[i].s2, quat_again[i].s3, quat_again[i].s4));
            }
        }
    }*/
};

#endif // CAL_QUAT_H
