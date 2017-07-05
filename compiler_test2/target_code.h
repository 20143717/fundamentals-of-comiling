#ifndef TARGET_CODE_H
#define TARGET_CODE_H

#include "cal_quat.h"
#include "syntax.h"
#include "lexical.h"

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <set>

using namespace std;

extern cal_quat main_quat;

class target_code {
public:
    deque<string> tar_code;
    struct get_sep {
        string str1, str2, str3, str4;
    };
    get_sep goal[1111];
    set<string> reput;
    int tot1, tot2;
    int flag, flag2;
    int cur;

    string get_current_string(int t) {
        string res = "";
        while(t) {
            string x = "";
            x += (t%10)+'0';
            t /= 10;
            res = x+res;
        }
        return res;
    }

    get_sep sep_tar(string ss) {
        get_sep x;
        int len = ss.length();
        int pos;
        x.str1 = "";
        x.str2 = "";
        x.str3 = "";
        x.str4 = "";
        for(int i = 2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.str1 += ss[i];
            }
        }
        for(int i = pos+2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.str2 += ss[i];
            }
        }
        for(int i = pos+2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.str3 += ss[i];
            }
        }
        for(int i = pos+2; i < len; i++) {
            if(ss[i] == ' ' || ss[i] == ',' || ss[i] == ')') {
                pos = i;
                break;
            }
            else {
                x.str4 += ss[i];
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

    bool is_invalid(string x) {
        if(x == "=" || x == "+" || x == "-" || x == "*" || x == "/" || x == "%" || x == "&" || x == "|" || x == "^"
        || x == "__" || x == "if" || x == "if_end" || x == "else" || x == "while" || x == "while_end" || x == "out"
        || x == "for" || x == "for_end" || is_number(x) || x == "do_while" || x == ">" || x == "<" || x == "do_for"
        || x == "<=" || x == ">=" || x == "<<" || x == ">>") {
            return true;
        }
        return false;
    }

    void solve() {
        tar_code.push_back("DSEG  SEGMENT");
        int sz = main_quat.last_quat.size();
        for(int i = 0; i < sz; i++) {
            string sp = main_quat.last_quat.front();
            goal[i] = sep_tar(sp);
            main_quat.last_quat.pop_front();
            main_quat.last_quat.push_back(sp);
            if(!is_invalid(goal[i].str1)) {
                if(!reput.count(goal[i].str1+"   DB    ?")) {
                    tar_code.push_back(goal[i].str1+"   DB    ?");
                    reput.insert(goal[i].str1+"   DB    ?");
                }
            }
            if(!is_invalid(goal[i].str2)) {
                if(!reput.count(goal[i].str2+"   DB    ?")) {
                    tar_code.push_back(goal[i].str2+"   DB    ?");
                    reput.insert(goal[i].str2+"   DB    ?");
                }
            }
            if(!is_invalid(goal[i].str3)) {
                if(!reput.count(goal[i].str3+"   DB    ?")) {
                    tar_code.push_back(goal[i].str3+"   DB    ?");
                    reput.insert(goal[i].str3+"   DB    ?");
                }
            }
            if(!is_invalid(goal[i].str4)) {
                if(!reput.count(goal[i].str4+"   DB    ?")) {
                    tar_code.push_back(goal[i].str4+"   DB    ?");
                    reput.insert(goal[i].str4+"   DB    ?");
                }
            }
        }
        tar_code.push_back("HTAB  DB  '0123456789ABCDEF'");
        tar_code.push_back("DSEG  ENDS");
        tar_code.push_back("SHOW  MACRO  M");
        tar_code.push_back("  MOV  AL, M");
        tar_code.push_back("  MOV  CH, M");
        tar_code.push_back("  MOV  CL, 4");
        tar_code.push_back("  SHR  AL, CL");
        tar_code.push_back("  LEA  BX, HTAB");
        tar_code.push_back("  XLAT");
        tar_code.push_back("  MOV  DL, AL");
        tar_code.push_back("  MOV  AH, 02H");
        tar_code.push_back("  INT  21H");
        tar_code.push_back("  AND  CH, 0FH");
        tar_code.push_back("  MOV  AL, CH");
        tar_code.push_back("  XLAT");
        tar_code.push_back("  MOV  DL, AL");
        tar_code.push_back("  MOV  AH, 02H");
        tar_code.push_back("  INT  21H");
        tar_code.push_back("  ENDM");
        tar_code.push_back("DISP  MACRO  M");
        tar_code.push_back("  MOV  DL, M");
        tar_code.push_back("  MOV  AH, 02H");
        tar_code.push_back("  INT  21H");
        tar_code.push_back("  ENDM");
        tar_code.push_back("CSEG  SEGMENT");
        tar_code.push_back("    ASSUME  CS:CSEG, DS:DSEG");
        tar_code.push_back("START:");
        tar_code.push_back("MOV  AX, DSEG");
        tar_code.push_back("MOV  DS, AX");

        for(int i = 0; i < sz; i++) {
            if(goal[i].str1 == "=") {
                tar_code.push_back("MOV  "+goal[i].str4+", "+goal[i].str2);
            }
            if(goal[i].str1 == "+") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("ADD  AL, "+goal[i].str3);
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "-") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("SUB  AL, "+goal[i].str3);
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "*") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("MOV  BL, "+goal[i].str3);
                tar_code.push_back("MUL  BL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "/") {
                tar_code.push_back("MOV  AX, "+goal[i].str2);
                tar_code.push_back("MOV  BL, "+goal[i].str3);
                tar_code.push_back("DIV  BL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "&") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("MOV  BL, "+goal[i].str3);
                tar_code.push_back("AND  AL, BL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "|") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("MOV  BL, "+goal[i].str3);
                tar_code.push_back("OR   AL, BL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "^") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("MOV  BL, "+goal[i].str3);
                tar_code.push_back("XOR  AL, BL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "<<") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("MOV  CL, "+goal[i].str3);
                tar_code.push_back("SHL  AL, CL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == ">>") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("MOV  CL, "+goal[i].str3);
                tar_code.push_back("SHR  AL, CL");
                tar_code.push_back("MOV  "+goal[i].str4+", AL");
            }
            if(goal[i].str1 == "out") {
                tar_code.push_back("MOV  AL, "+goal[i].str2);
                tar_code.push_back("SHOW  AL");
                tar_code.push_back("DISP  ' '");
                //tar_code.push_back("MOV  DL, AL");
                //tar_code.push_back("MOV  AH, 02H");
                //tar_code.push_back("INT  21H");
            }
            //for和if分开判断
            if(goal[i].str1 == "for" || goal[i].str1 == "while") {
                if(goal[i+1].str1 == "<") {
                    tar_code.push_back("FOR"+get_current_string(tot1)+":");
                    //tar_code.push_back("CMP  "+goal[i+1].str2+", "+goal[i+1].str3);
                    tar_code.push_back("MOV  AL, "+goal[i+1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i+1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JB   OUTF"+get_current_string(tot2));
                    tar_code.push_back("JMP  FAR  PTR  NEXT"+get_current_string(tot1));
                    tar_code.push_back("OUTF"+get_current_string(tot2)+":");
                    tot2++;
                    tot1++;
                }
                if(goal[i+1].str1 == ">") {
                    tar_code.push_back("FOR"+get_current_string(tot1)+":");
                    //tar_code.push_back("CMP  "+goal[i+1].str2+", "+goal[i+1].str3);
                    tar_code.push_back("MOV  AL, "+goal[i+1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i+1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JA   OUTF"+get_current_string(tot2));
                    tar_code.push_back("JMP  FAR  PTR  NEXT"+get_current_string(tot1));
                    tar_code.push_back("OUTF"+get_current_string(tot2)+":");
                    tot2++;
                    tot1++;
                }
                if(goal[i+1].str1 == "<=") {
                    tar_code.push_back("FOR"+get_current_string(tot1)+":");
                    //tar_code.push_back("CMP  "+goal[i+1].str2+", "+goal[i+1].str3);
                    tar_code.push_back("MOV  AL, "+goal[i+1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i+1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JBE  OUTF"+get_current_string(tot2));
                    tar_code.push_back("JMP  FAR  PTR  NEXT"+get_current_string(tot1));
                    tar_code.push_back("OUTF"+get_current_string(tot2)+":");
                    tot2++;
                    tot1++;
                }
                if(goal[i+1].str1 == ">=") {
                    tar_code.push_back("FOR"+get_current_string(tot1)+":");
                    //tar_code.push_back("CMP  "+goal[i+1].str2+", "+goal[i+1].str3);
                    tar_code.push_back("MOV  AL, "+goal[i+1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i+1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JAE  OUTF"+get_current_string(tot2));
                    tar_code.push_back("JMP  FAR  PTR  NEXT"+get_current_string(tot1));
                    tar_code.push_back("OUTF"+get_current_string(tot2)+":");
                    tot2++;
                    tot1++;
                }
            }
            if(goal[i].str1 == "break") {
                tar_code.push_back("JMP  FAR  PTR  NEXT"+get_current_string(tot1-1));
            }
            if(goal[i].str1 == "for_end" || goal[i].str1 == "while_end") {
                tot1--;
                tar_code.push_back("JMP  FOR"+get_current_string(tot1));
                tar_code.push_back("NEXT"+get_current_string(tot1)+":");
            }
            if(goal[i].str1 == "if") {
                if(goal[i-1].str1 == "<") {
                    tar_code.push_back("MOV  AL, "+goal[i-1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i-1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JB   OUTI"+get_current_string(flag2));
                    tar_code.push_back("JMP  FAR  PTR  NEXTI"+get_current_string(flag));
                    tar_code.push_back("OUTI"+get_current_string(flag2)+":");
                    flag2++;
                }
                if(goal[i-1].str1 == ">") {
                    tar_code.push_back("MOV  AL, "+goal[i-1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i-1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JA   OUTI"+get_current_string(flag2));
                    tar_code.push_back("JMP  FAR  PTR  NEXTI"+get_current_string(flag));
                    tar_code.push_back("OUTI"+get_current_string(flag2)+":");
                    flag2++;
                }
                if(goal[i-1].str1 == "<=") {
                    tar_code.push_back("MOV  AL, "+goal[i-1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i-1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JBE  OUTI"+get_current_string(flag2));
                    tar_code.push_back("JMP  FAR  PTR  NEXTI"+get_current_string(flag));
                    tar_code.push_back("OUTI"+get_current_string(flag2)+":");
                    flag2++;
                }
                if(goal[i-1].str1 == ">=") {
                    tar_code.push_back("MOV  AL, "+goal[i-1].str2);
                    tar_code.push_back("MOV  BL, "+goal[i-1].str3);
                    tar_code.push_back("CMP  AL, BL");
                    tar_code.push_back("JAE  OUTI"+get_current_string(flag2));
                    tar_code.push_back("JMP  FAR  PTR  NEXTI"+get_current_string(flag));
                    tar_code.push_back("OUTI"+get_current_string(flag2)+":");
                    flag2++;
                }
                if(goal[i].str2 == "0") {
                    tar_code.push_back("JMP   NEXTI"+get_current_string(flag));
                }
                flag++;
            }
            if(goal[i].str1 == "else") {
                cur = 1;
                flag--;
                tar_code.push_back("JMP  IEND"+get_current_string(flag));
                tar_code.push_back("NEXTI"+get_current_string(flag)+":");
            }
            if(goal[i].str1 == "if_end") {
                tar_code.push_back("IEND"+get_current_string(flag)+":");
                if(!cur) {
                    flag--;
                }
                cur = 0;
            }
        }

        tar_code.push_back("MOV  AH, 4CH");
        tar_code.push_back("INT  21H");
        tar_code.push_back("CSEG  ENDS");
        tar_code.push_back("  END  START");
    }
};

#endif // TARGET_CODE_H
