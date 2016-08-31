#include<bits/stdc++.h>
#ifndef MNEMONIC_H
#define MNEMONIC_H
using namespace std;

class mnemonic
{
    public:
        mnemonic(string);
        string get_name();
        int get_opcode();
        int get_format();
    private:
        string name;
        int format;
        int opcode;
};

#endif // MNEMONIC_H
