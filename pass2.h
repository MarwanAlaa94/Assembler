#ifndef PASS2_H
#define PASS2_H
#include "pass1.h"
class Pass2
{
    public:
        Pass2(Pass1&);
        void generate_op_code();
        string intToHex(int);
        string get_displacement(Instruction&);
        int get_reg_byte(Instruction&);
        string get_op_code(Instruction&);
        void print_object_code();
    private:
        string length;
        string name;
        string start;
        unordered_map <string, int> sym_table;
        map <string, int>  lit_table;

       // StringUtilities utility;
        vector <string> object_code;
        vector<Instruction> instructs;
        vector<pair<string, string> > records;

};

#endif // PASS 2_H
