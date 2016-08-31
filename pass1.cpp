#include "pass1.h"
#include "parser.h"
#include"process_utils.h"
using namespace std;

Pass1::Pass1(string path) {
    this->path = path;
    read_file();
}

bool Pass1::is_completed() {
    return completed;
}

unordered_map<string , int>Pass1::get_sym_table(){
    return sym_table;
}

vector<Instruction>Pass1::get_instruction(){
    return instruction_vector;
}

map<string,int>Pass1::get_lit_table(){
    return  process_utils::get_lit_tab();
}


void Pass1::read_file(){

    Parser parser("optable.txt");
    ifstream file(path);
    ofstream ofile("LIST.txt");

    if(!file){
        cout<<"not found";
        return;
    }

    string word_temp;
    string word;

    while(getline(file, word_temp)) {
        word = "";

        for(int i=0;i<word_temp.size();i++){
            if(word_temp[i] != 13)word += word_temp[i];
        }

        Instruction instruct = parser.read_line(word);

        if(instruct.get_is_comment()){
            ofile<< word<<"\n";
            continue;
        }

        int temp = 0;
        string error = "";

        if (endf) error = "statement should not follow END statement\n";

        if (!instruct.get_error()){

            if(instruct.get_op_label() == "start" && !start) {
                start  = true;
                std::stringstream ss;
                ss << std::hex << instruct.get_op1();
                ss >> location_counter;
            }

            else if(instruct.get_op_label() == "start"){
                completed = false;
                error =  "duplicate or misplaced START statement\n";
            }

            if(!start) {
                start = true;
                location_counter = 0;
            }

            if(instruct.get_op_label() == "end" && !endf){
                location_counter = process_utils::process_lit(location_counter);
                endf = true;
            }
            else if(instruct.get_op_label() == "end"){
                error = "Duplicate END instrtuction\n";
            }

            temp  = location_counter;



            if(instruct.get_label().size() > 0){
                if(sym_table.find(instruct.get_label()) == sym_table.end()){
                    sym_table[instruct.get_label()] = location_counter;
                    commands.push_back(instruct.get_label());
                   //edited
                }
                else {
                    error = "Error: DUBLICATE SYMBOL\n";
                    completed = false;
                    if(instruct.get_format() < 0)
                        location_counter += instruct.get_format();
                    else
                        location_counter -= instruct.get_format();
                }
            }

            if(instruct.get_op_label() == "ltorg"){
                location_counter = process_utils::process_lit(location_counter);
            }

            else if(instruct.get_op_label() == "equ"){
                sym_table[instruct.get_label()] = process_utils::eval_expression(sym_table , instruct);
            }

            else if(instruct.get_op_label() == "org"){
                location_counter = process_utils::eval_expression(sym_table , instruct);
            }



            if(instruct.get_format() < 0)
                location_counter -= instruct.get_format();
            else
                location_counter += instruct.get_format();

            instruct.set_address(location_counter);
            //if(instruct.get_label()  == "loopa")instruct.print();
            instruction_vector.push_back(instruct);

        }

        else {
            error = "Error: Invalid Instruction\n";
            completed = false;
        }

        ofile <<hex << temp <<"\t"<<word<<"\n";
        if(error.size()>0)ofile<<error<<"\n";

    }

    if(!endf){
        ofile <<  "Error: No END\n";
        completed = false;
    }

    ofile<<"\n\n***symbol table:\n\n";

    for(int i = 0; i < commands.size(); i++) {
        ofile << hex << sym_table[commands[i]] <<"\t" << commands[i] << "\n";
    }


    if(completed){
        ofile << "\nComplete Assembly "   ;

    }else{
        ofile << "\nInComplete Assembly !!!";
    }

}
