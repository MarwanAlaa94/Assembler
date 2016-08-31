#include "process_utils.h"

queue<string> process_utils::lit_queue;
map<string , int> process_utils::lit_tab;
map<string , string> process_utils::reg_table;
vector<string> process_utils::split(string x,char c){
    string curr = "";
    vector<string>ret;
    for(int i=0;i<x.size();i++){
        if(x[i] == c){
            if(curr != "")ret.push_back(curr);
            curr = "";
        }else
            curr += x[i];
    }
    if(curr != "")
        ret.push_back(curr);
    return ret;
}

string process_utils::trim(string x){
    int i  = 0 ;
    int j = x.size()-1;
    while(i < j && x[i] == ' ')i++;
    while(i < j && x[j] == ' ')j--;
    return x.substr(i,j-i+1);
}

bool process_utils::check_adressing_mode(Instruction &inst , string label,string op,string op1,string op2,int format, RegexBuilder &r){
    if(r.is_reserved_word(label)){
        inst.set_error(true);
        return false;
    }
    if( format != 2){
        /// format 3 or 4 , aly (single)
        if(op[0] == '+' ){
            op = op.substr(1);
            inst.set_e(true);
            format = 4;
        }

        if(op1.size() && op1[0] == '@' ){
            op1 = op1.substr(1);
            inst.set_n(true);
        }else if( op1.size() && op1[0] == '#' ){
            op1 = op1.substr(1);
            inst.set_i(true);
        }else if(op1.size() && op1.find(",x") != string::npos ){
            op1 = op1.substr(0,op1.size()-2);
            inst.set_i(true);
            inst.set_x(true);
            inst.set_n(true);
        }else if(op1[0] == '='){
            int opSize = op1.size();
            if(op1[1] == 'x' && ( (opSize - 4) % 2 == 1)){
                inst.set_error(true);
            }
            else lit_queue.push(op1);
        }else{
            inst.set_n(true);
            inst.set_i(true);
        }
    }

    inst.set_label(label);
    inst.set_op_label(op);
    inst.set_op_code(r.get_obj_code(op));
    inst.set_op1(op1);
    inst.set_op2(op2);
    inst.set_format(format);

    return true;

}


int process_utils::process_lit(int address){

    while(!lit_queue.empty()){

        string tmp = lit_queue.front();
        lit_queue.pop();

        if(lit_tab.find(tmp) == lit_tab.end()){
           lit_tab[tmp] = address;

            int str_size = tmp.size();

            if(tmp[1] == 'x')
                address += (str_size - 4)/2;
            else if (tmp[1] == 'c')
                address += (str_size - 4);
            else
                address += 3;
        }

    }

    return address;
}

bool process_utils::process_directive(Instruction &inst, string label, string directive,string op, RegexBuilder &r){

    if(r.is_reserved_word(label)){
        inst.set_error(true);
        return false;
    }

    inst.set_label(label);
    inst.set_op_label(directive);
    inst.set_op1(op);
    int opSize = op.size();

    if(directive == "resw"){
       if(opSize > 4){
           inst.set_error(false);
           return false;
       }
       inst.set_format(  -1 * atoi(op.c_str()) * 3);
    }

    if(directive == "resb"){
          if(opSize > 4){
                inst.set_error(true);
               return false;
          }
          inst.set_format(  -1 * atoi(op.c_str()) );
    }

    if(directive == "word"){
           int max_len = 5;
           vector<string>words = split(op,',');
           for(string x : words){
                x = trim(x);
                if(x[0] == '-' && x.size()> 5){
                    inst.set_error(true);
                    return false;
                }
                else if(x[0] != '-' && x.size()> 4){
                    inst.set_error(true);
                    return false;
                }
           }
           int counter = 1 ;
           inst.set_format(-3*words.size());
    }

    if(directive == "byte"){

        if(op[0] == 'x' && ( (opSize -3) % 2 == 0)){

            inst.set_format(- (opSize-3) / 2);

        }else if(op[0] == 'c'){

            inst.set_format(- (opSize-3));

        }else{

            inst.set_error(true);
            return false;

        }

    }

    if(directive == "start"){

        if(opSize > 4){
            inst.set_error(false);
            return false;
        }

    }

    return true;

}


int process_utils:: eval_expression(unordered_map<string,int>&mp,Instruction& inst){
    string curr = "";
    stack<char>ops;
    stack<int>nums;
    for(char x : inst.get_op1()){
        if(x == '+'){
            if(curr[0] >= '0' && curr[0] <= '9'){
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-atoi(curr.c_str()));
                else
                    nums.push(atoi(curr.c_str()));
            }else{
                if(mp.find(curr) == mp.end()){
                    inst.set_error(false);
                    return 1;
                }
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-mp[curr]);
                else
                    nums.push(mp[curr]);
            }
            if(!ops.empty() && (ops.top() == '*' || ops.top() == '/')){
                int a = nums.top();
                int b = nums.top();
                nums.pop();
                nums.pop();
                nums.push(eval(b,a,ops.top()));
                ops.pop();
            }
            ops.push('+');
            curr = "";
        }else if(x == '-'){

            if(curr[0] >= '0' && curr[0] <= '9'){
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-atoi(curr.c_str()));
                else
                    nums.push(atoi(curr.c_str()));
            }else{
                if(mp.find(curr) == mp.end()){
                    inst.set_error(false);
                    return 1;
                }
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-mp[curr]);
                else
                    nums.push(mp[curr]);
            }

            if(!ops.empty() && (ops.top() == '*' || ops.top() == '/')){
                int a = nums.top();
                int b = nums.top();
                nums.pop();
                nums.pop();
                nums.push(eval(b,a,ops.top()));
                ops.pop();
            }
            ops.push('-');
            curr = "";
        }else if(x == '/'){

            if(curr[0] >= '0' && curr[0] <= '9'){
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-atoi(curr.c_str()));
                else
                    nums.push(atoi(curr.c_str()));
            }else{
                if(mp.find(curr) == mp.end()){
                    inst.set_error(false);
                    return 1;
                }
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-mp[curr]);
                else
                    nums.push(mp[curr]);
            }

            if(!ops.empty() && (ops.top() == '*' || ops.top() == '/')){
                int a = nums.top();
                int b = nums.top();
                nums.pop();
                nums.pop();
                nums.push(eval(b,a,ops.top()));
                ops.pop();
            }
            curr = "";
            ops.push('/');
        }else if(x == '*'){

            if(curr[0] >= '0' && curr[0] <= '9'){
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-atoi(curr.c_str()));
                else
                    nums.push(atoi(curr.c_str()));
            }else{
                if(mp.find(curr) == mp.end()){
                    inst.set_error(false);
                    return 1;
                }
                if(!ops.empty() && ops.top() == '-')
                    nums.push(-mp[curr]);
                else
                    nums.push(mp[curr]);
            }

            if(!ops.empty() && (ops.top() == '*' || ops.top() == '/')){
                int a = nums.top();
                int b = nums.top();
                nums.pop();
                nums.pop();
                nums.push(eval(b,a,ops.top()));
                ops.pop();
            }
            curr = "";
            ops.push('*');
        }else
            curr += x;
    }
    if(curr[0] >= '0' && curr[0] <= '9'){
        if(!ops.empty() && ops.top() == '-')
            nums.push(-atoi(curr.c_str()));
        else
            nums.push(atoi(curr.c_str()));
    }else{
        if(mp.find(curr) == mp.end()){
            inst.set_error(false);
            return 1;
        }
        if(!ops.empty() && ops.top() == '-')
            nums.push(-mp[curr]);
        else
            nums.push(mp[curr]);
    }
    while(!ops.empty()){
        char x = ops.top();
        int a,b;
        a = nums.top();
        nums.pop();
        b = nums.top();
        nums.pop();
        ops.pop();
        nums.push(eval(b,a,x));
    }
    return nums.top();
}
int process_utils:: eval(int a,int b , char x){
    if(x == '+' || x == '-')return a+b;
    if(x == '*')return a*b;
    if(x == '/')return a/b;
}

map<string , int> process_utils::get_lit_tab(){
    return lit_tab;
}
void process_utils::initialize_regesters(){
    reg_table["a"]="0";
    reg_table["x"]="1";
    reg_table["l"]="2";
    reg_table["b"]="3";
    reg_table["s"]="4";
    reg_table["t"]="5";
    reg_table["f"]="6";
}
