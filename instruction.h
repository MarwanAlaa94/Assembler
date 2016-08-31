#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include<iostream>
using namespace std;
class Instruction
{
    public:
        Instruction();
        void set_n(bool );
        void set_i(bool );
        void set_x(bool );
        void set_p(bool );
        void set_b(bool );
        void set_e(bool );
        void set_format(int);
        void set_label(string);
        void set_op1(string);
        void set_op2(string);
        void set_op_label(string);
        void set_op_code(int);
        void set_error(bool);
        void set_address(int);
        void set_is_comment(bool);
        bool get_n();
        bool get_i();
        bool get_x();
        bool get_p();
        bool get_b();
        bool get_e();
        bool get_error();
        int get_format();
        int get_address();
        bool get_is_comment();

        void print();
        string get_label();
        string get_op1();
        string get_op2();
        string get_op_label();
        int get_op_code();
    private:
        bool n,i,x,b,p,e,error;
        int format;
        int op_code;
        int address;
        bool is_comment;
        string label;
        string op_label,op1,op2;

};

#endif // INSTRUCTION_H
