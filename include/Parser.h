#ifndef PARSER_H
#define PARSER_H
#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;

class Parser
{
    public:
        Parser();
        instruction get_instrunction(string);
        string get_label();
    private:

};

#endif // PARSER_H
