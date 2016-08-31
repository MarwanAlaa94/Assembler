#include <bits/stdc++.h>
#ifndef OPERAND_H
#define OPERAND_H
using namespace std;

class operand
{
    public:
        operand(string);
        string get_nixbpe();
        void set_e(bool);
    private:
        string name;
        int nixpbe;
};

#endif // OPERAND_H
