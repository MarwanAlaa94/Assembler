#include <iostream>
#include"parser.h"
#include"instruction.h"
#include "pass2.h"
#include"process_utils.h"
#include <unordered_map>
using namespace std;


int main(int argc, char* argv[]  ){


//    unordered_map<string,int>mp ;
//    mp["lol"] = 4;
//    mp["hamada"] = 5;
//    mp["node"] = 6;
//    string exp = "lol+5+4-hamada*node";
//    Instruction inst;
//    inst.set_op1(exp);
//    cout <<process_utils::eval_expression(mp,inst) <<endl;
//    if(argc != 2){
//        cout<<"USAGE:\n pass1 <filename>"<<endl;
//        return 0;
//    }

    Pass1 pass_1("TXT.txt");
    Pass2  p(pass_1);
    return 0;
}


