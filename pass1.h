#ifndef PASS1_H
#define PASS1_H
#endif // PARSER_H
#include "parser.h"
#include"instruction.h"

class Pass1
{
    public:
        Pass1();
        Pass1(string);
        void read_file();
        bool is_completed();
        unordered_map<string , int> get_sym_table();
        vector<Instruction> get_instruction();
        map<string,int> get_lit_table();

    private:
        bool completed = true;
        bool start = false;
        bool endf = false;
        string path;
        int location_counter=0;
        vector <string> commands;
        vector<Instruction> instruction_vector;
        unordered_map<string, int> sym_table;
};
