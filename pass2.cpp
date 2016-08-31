#include "pass2.h"
#include"process_utils.h"
Pass2::Pass2(Pass1 &pass_1) {
    this->sym_table = pass_1.get_sym_table();
    this->lit_table = pass_1.get_lit_table();
    this->instructs = pass_1.get_instruction();
    process_utils::initialize_regesters();
    generate_op_code();
}

string Pass2::intToHex(int intValue) {
    string hexStr;
    stringstream sstream;
    sstream<< hex << (int)intValue;
    hexStr= sstream.str();
    sstream.clear();
    transform(hexStr.begin(), hexStr.end(), hexStr.begin(), ::toupper);
    return hexStr;
}

string Pass2::get_displacement(Instruction &instruction) {//shiftNotDone

    int sz = 3;
    if (instruction.get_format() == 4)sz = 5;
    else if (instruction.get_format()  == 2)sz = 2;
    int disp = 0;
    string str;
    if (instruction.get_format() == 2){
        str += process_utils::reg_table[instruction.get_op1()];
        if (instruction.get_op2().size() == 0){
            str += "0";
        }
        else {
            str += process_utils::reg_table[instruction.get_op2()];
        }
        return str;
    }

    else if (instruction.get_format() == 4){



    }else{
        if(sym_table.count(instruction.get_op1())){

             int dis = sym_table[instruction.get_op1()] - instruction.get_address();
             if(instruction.get_op_label()  == "sub")instruction.print();


             if(dis >= -2048 && dis < 2048){
                str = intToHex(dis);
                instruction.set_p(1);
             }
//             else if(){
//
//             }
//             else{
//
//             }

        }
        else if(lit_table.count(instruction.get_op1())){//edited


             int dis = lit_table[instruction.get_op1()] - instruction.get_address();

             if(dis >= -2048 && dis < 2048){
                str = intToHex(dis);
                instruction.set_p(1);
             }
//             else if(){
//
//             }
//             else{
//
//             }

        }
        else{
            // no PC for now :3
            int result = process_utils::eval_expression(sym_table , instruction);
            if(result == -1e9){
                str = "error";
            }else{
                str = intToHex(result);
            }
        }
    }
    while(str.size() < sz) {
        str = '0' + str;
    }
    while(str.size()>sz){
        str=str.substr(1);
    }
    return str;
}

string Pass2::get_op_code(Instruction &instruction) {
    int ans=instruction.get_op_code();
    if(instruction.get_n())
     ans+=2;
    if(instruction.get_i())
     ans+=1;
     string res=intToHex(ans);
     while(res.size()<2){
        res="0"+res;
     }
    return res;
}

int Pass2::get_reg_byte(Instruction &instruction) {
    int ans=0;
    if(instruction.get_x())
        ans+=1<<3;
    if(instruction.get_b())
        ans+=1<<2;
   if(instruction.get_p())
        ans+=1<<1;
    if(instruction.get_e())
        ans+=1;
    return ans;
}

void Pass2::generate_op_code(){

        for(Instruction inst: instructs){
//       if(inst.get_op_label()=="jeq"){
//          cout<<inst.get_i()<<" "<<inst.get_p()<<endl;
//       }  //sub zero !!,td,rd,immediate!!
        if(inst.get_op_label()=="start"){
            length = inst.get_op1();
            start=inst.get_op1();
            name = inst.get_label();
            object_code.push_back("start");
        }
       else if(inst.get_op_label()=="end"){
            length = intToHex(inst.get_address() - atoi(length.c_str()));
        }
       else if(inst.get_op_label() == "resw" || inst.get_op_label() == "resb"){
            object_code.push_back("BREAK");
            continue;
        }
       else if(inst.get_op_label() == "word"){
            string s=intToHex(atoi(inst.get_op1().c_str()));//edited
            while(s.size()<6){
                s="0"+s;
            }
            object_code.push_back(s);
        }
        else if(inst.get_op_label() == "byte"){
            if(inst.get_op1()[0] == 'x' || inst.get_op1()[0] == 'X'){
                string temp = inst.get_op1();
                temp = temp.substr(2, temp.size()-3);
                object_code.push_back(temp);
            }
            else {
                string temp = inst.get_op1();
                temp = temp.substr(2, temp.size()-3);
                string temp2;
                for(int i=0;i<temp.size();i++){
                    temp2 += intToHex(temp[i]);
                }
                object_code.push_back(temp2);
            }
        }
        else if(inst.get_op_label() == "rsub" || inst.get_op_label() == "RSUB"){
            object_code.push_back("4F0000");
        }
        else if(inst.get_format()==2){//edited
            string temp = get_op_code(inst);
            temp += get_displacement(inst);
             object_code.push_back(temp);
        }
        else if(inst.get_op_label() == "org" || inst.get_op_label() == "ltorg" || inst.get_op_label() == "equ")  continue;
        else{
            string temp = get_op_code(inst);
            string dis  = get_displacement(inst);
            string xbpe = intToHex(get_reg_byte(inst));
            object_code.push_back(temp+xbpe+dis);
        }
        //cout<<temp<<"\n";
    }
    for(int i=0;i<object_code.size();i++){
        cout<<object_code[i]<<endl;
  }

       print_object_code();
}

void Pass2::print_object_code() {
    ofstream ofile("ObjectCode.txt");
    while(name.size() < 6){
        name =name+' ';
    }
    while(length.size() < 6){
        length = '0' + length;
    }
    while(start.size() < 6){
        start = '0' + start;
    }
    ofile<<"H"<<name<<start<<length;
    cout<<"H"<<name<<start<<length;

    for (int i=1;i< object_code.size();i++){
        int n = 0;
        string temp;
        string temp2 = intToHex(instructs[i].get_address());
         while(temp2.size() < 6){
          temp2 = "0"+temp2;
        }
        // cout<<endl<<"start"<<instructs[i].get_address()<<endl;
        while(i<object_code.size()){
        if(n+object_code[i].size()<=60 && object_code[i] != "BREAK" ){
            temp+=object_code[i];
            n+=object_code[i].size();
            i++;
        }
        else
            break;}
        records.push_back({temp2, temp});
    }
    for(int i = 0;i < records.size(); i++){
        if(records[i].second.size()==0)continue;
        ofile<<"\nT"<<records[i].first<<intToHex(records[i].second.size()/2)<<records[i].second;
        cout<<"\nT"<<records[i].first<<intToHex(records[i].second.size()/2)<<records[i].second;
    }
    ofile<<"\nE"<<start;
    cout<<"\nE"<<start;
}
