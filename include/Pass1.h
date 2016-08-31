#include <bits/stdc++.h>
#ifndef PASS1_H
#define PASS1_H
#endif // PARSER_H
#include "Parser.h"
using namespace std;
class Pass1
{
    public:
        Pass1(string);
        void read_file();
        bool is_completed();
    private:
        bool completed = true;
        string path;
        int location_counter=0;
        Parser parser;
        vector <string> commands;
        vector<instruction> instructions;
        map<string, int> sym_table;
};

