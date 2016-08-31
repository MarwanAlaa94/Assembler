#ifndef PROCESS_UTILS_H
#define PROCESS_UTILS_H
#include "instruction.h"
#include "regexbuilder.h"
#include <queue>
#include <map>

using namespace std;

class process_utils
{
    public:
        static bool check_adressing_mode(Instruction& , string ,string ,string ,string,int ,RegexBuilder&);
        static bool process_directive(Instruction&, string , string ,string,RegexBuilder& );
        static int process_lit(int);
        static vector<string> split(string x,char c);
        static string trim(string x);
        static int eval_expression(unordered_map<string,int>&,Instruction&);
        static int eval(int,int , char);
        static map<string , int> get_lit_tab();
        static map <string, string>  reg_table;
        static void initialize_regesters();
    private:
        static queue<string> lit_queue;
        static map<string , int> lit_tab;

};

#endif // PROCESS_UTILS_H
