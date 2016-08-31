#include <bits/stdc++.h>
#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <operand.h>
#include <mnemonic.h>
using namespace std;

class instruction
{
public:
    instruction();
    int getSize();
    int get_format();
    string get_label();
    void set_address(int);
private:
};


#endif // INSTRUCTION_H
