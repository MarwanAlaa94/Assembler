#include "instruction.h"
#include "regexbuilder.h"
#ifndef PARSER_H
#define PARSER_H

class Parser
{
    public:
        Parser(string);
        Instruction read_line(string);
    private:
        RegexBuilder rgx_builder;
        bool is_valid_label(string);
        bool check_adressing_mode(Instruction&  , string ,string ,string ,string ,int);
        bool process_directive(Instruction& , string , string,string);

};

#endif // PARSER_H
