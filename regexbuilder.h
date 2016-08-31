#ifndef REGEXBUILDER_H
#define REGEXBUILDER_H
#include <bits/stdc++.h>
using namespace std;

class RegexBuilder{

public:
    RegexBuilder();
    void add_op(string x,map<string,string>&mp,string y);
    void read_regx(string file_name);
    map<string,string> get_format2_regx();
    map<string,string> get_format3_4_regx();
    bool is_reserved_word(string);
    int get_obj_code(string);
    string get_ind_regx();
    string get_label_regx();
    string get_imd_regx();
    string get_comment_regx();
    string get_dir_regx(int);
    string get_ret_sub_regx();

private:
    string literal_regx;
    string exp_regx;
    string address_regx;
    string comment_regx;
    string registers_regx;
    string label_regx;
    string char_regx;
    string byte_regx;
    string imd_regx;
    string ind_regx;
    string ret_sub_regx;
    string dir_regx[9];
    map<string,string> format2_regx;
    map<string,string> format3_4_regx;
    map<string,int> obj_code;


};

#endif // REGEXBUILDER_H
