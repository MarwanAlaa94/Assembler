#include "instruction.h"

Instruction::Instruction(){
    n = i = x = b = p = e = false;
    format = 0;
    op_code = -1;
    label = "";
    op_label = "";
    op1 = "";
    op2 = "";
    error = 0;
    is_comment = false;
}
void Instruction::set_n(bool x){
    n = x;
}
void Instruction:: set_i(bool x){
    i = x;
}
void Instruction:: set_x(bool x){
    this->x = x;
}
void Instruction:: set_p(bool x){
    p = x;
}
void Instruction:: set_b(bool x){
    b = x;
}
void Instruction:: set_e(bool x){
    e = x;
}
void Instruction:: set_format(int x){
    format = x;
}
void Instruction:: set_label(string x){
    label = x;
}
void Instruction:: set_op1(string x){
    op1 = x;
}
void Instruction:: set_op2(string x){
    op2 = x;
}
void Instruction:: set_op_label(string x){
    op_label = x;
    }
void Instruction:: set_op_code(int x){
    op_code = x;
    }
void Instruction::set_error(bool x){
    error = x;
}
void Instruction::set_address(int x){
    address = x;
}
void Instruction::set_is_comment(bool x){
    is_comment = x;
}

void Instruction:: print(){
    cout<<"n = "<<n<<" i = "<<i<<" x = "<<x<<" p = "<<p<<" b = "<<b<< "e = "<<e<<endl;
    cout<<"error = "<< error<<endl;
    cout<<"format = "<< format <<endl;
    cout<<"label = "<< label<<endl;
    cout<<"op_label = "<< op_label<<endl;
    cout<<"op1 = "<< op1<<endl;
    cout<<"op2 = "<< op2<<endl;
    cout<<"get_op_code = "<< hex<<op_code<<endl;
    cout<<"address = "<< address<<endl;
}

bool Instruction:: get_n(){return n;}
bool Instruction:: get_i(){return i;}
bool Instruction:: get_x(){return x;}
bool Instruction:: get_p(){return p;}
bool Instruction:: get_b(){return b;}
bool Instruction:: get_e(){return e;}
bool Instruction:: get_is_comment(){return is_comment;}
int Instruction:: get_format(){return format;}
string Instruction:: get_label(){return label;}
string Instruction:: get_op1(){return op1;}
string Instruction:: get_op2(){return op2;}
string Instruction:: get_op_label(){return op_label;}
int Instruction:: get_op_code(){return op_code;}
bool Instruction:: get_error(){return error;}
int Instruction:: get_address(){return address;}

