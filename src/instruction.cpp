#include <bits/stdc++.h>
#include "instruction.h"
using namespace std;
instruction::instruction()
{
    //ctor
}
int instruction::getSize(){
    return 1;
}
int instruction::get_format() {
    return -1e1;
}
string instruction::get_label() {
    return "hamada";
}
void instruction::set_address(int x){}
