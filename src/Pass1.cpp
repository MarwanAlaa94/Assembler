#include <bits/stdc++.h>
#include "Pass1.h"
#include "parser.h"
using namespace std;

Pass1::Pass1(string path) {
    this->path = path;
}
bool Pass1::is_completed() {
    return completed;
}
void Pass1::read_file(){
    ifstream file("in.txt");
    ofstream ofile("LISA.txt");
    if(!file){
        cout<<"not found";
        return;
    }
    string word;
    while(getline(file, word)) {
        instruction instruct = parser.get_instrunction(word);
        instructions.push_back(instruct);
        if(!instruct.get_error()){
            if(instruct.get_label().size() > 0){
                if(sym_table.find(instruct.get_label()) == sym_table.end()){
                    ofile <<location_counter<<"     "<<word<<"\n";
                    sym_table[instruct.get_label()] = location_counter;
                    instruct.set_address(location_counter);
                }
                else {
                    ofile <<"Error: DUBLICATE SYMBOL\n";
                    completed = false;
                    if(instruct.get_format() < 0)
                        location_counter += instruct.get_format();
                    else
                        location_counter -= instruct.get_format();
                }
            }
            if(instruct.get_format() < 0)
                location_counter -= instruct.get_format();
            else
                location_counter += instruct.get_format();
        }
        else {
            ofile <<"Error: Invalid Instruction\n";
            completed = false;
        }
    }
}
