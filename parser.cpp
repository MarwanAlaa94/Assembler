#include "parser.h"
#include"regexbuilder.h"
#include"process_utils.h"
Parser::Parser(string file_name){
    rgx_builder.read_regx(file_name);
    //cout << rgx_builder.get_format2_regx().size()<<endl;
}



Instruction Parser::read_line(string line){
    transform(line.begin(),line.end(),line.begin(),::tolower);
    Instruction inst;
    smatch sm;
    bool found = false;
    regex rgx("^"+rgx_builder.get_comment_regx());
    if( regex_match(line,rgx) ){
        regex_search(line,sm,rgx);
        inst.set_is_comment(true);
        found = true;
    }
    rgx = regex(rgx_builder.get_ret_sub_regx());
    if( regex_match(line,rgx) ){
        regex_search(line,sm,rgx);
        process_utils::check_adressing_mode(inst,sm[1],sm[2],"","",3 , rgx_builder);
        found = true;
    }
    for(int i=0;!found && i<8;i++){
        rgx = regex(rgx_builder.get_dir_regx(i));
        if( regex_match(line,rgx) ){
            regex_search(line,sm,rgx);
            process_utils::process_directive(inst,sm[1],sm[2],sm[3] , rgx_builder);
            found = true;
        }
    }
    map<string,string>mp = rgx_builder.get_format2_regx();
    map<string,string>::iterator it =  mp.begin();
    while(!found && it != mp.end()){
        rgx = regex("^\\s*(?:("+rgx_builder.get_label_regx()+")\\s+){0,1}"+it->second);

        if( regex_match(line,rgx) ){
          //  cout<<"matched "<<it->second<<endl;

            regex_search(line,sm,rgx);
            string last = "";
            if(sm.size() >= 4)last = sm[4];
            process_utils::check_adressing_mode(inst,sm[1] , sm[2], sm[3], last,2 , rgx_builder);
            found = true;
            break;
        }
        it++;
    }
    mp = rgx_builder.get_format3_4_regx();
    it =  mp.begin();
    while(!found && it != mp.end()){
        rgx = regex("^\\s*(?:("+rgx_builder.get_label_regx()+")\\s+){0,1}"+it->second);
        //cout << "^\\s*(?:("+rgx_builder.get_label_regx()+")\\s+){0,1}"+it->second<<endl;
        if( regex_match(line,rgx) ){
            regex_search(line,sm,rgx);
            process_utils::check_adressing_mode(inst,sm[1] , sm[2], sm[3], "",3, rgx_builder);
            found = true;
            break;

        }
        it++;
    }
    if(!found)
           inst.set_error(true);
    return inst;
}

//ctor
