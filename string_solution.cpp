//
// Created by crasher on 2022/7/21.
//

#include "string_solution.h"

const static int MAX_SIZE=7;

map<string,string> file_root={{"LOGIN",R"(C:\Users\crasher\CLionProjects\game_project\data\data_login)"}};

map<string,string> file_specific{{"login",R"(\login.txt)"},
                                      {"pre_login",R"(\pre_login.txt)"}};

//检察文明用语
bool civil_check(const string &tmp){
    return true;
}

string& delete_blank(string& word){
    auto begin=word.begin();
    while(begin!=word.end()){
        if(*begin<=32)
            begin=word.erase(begin);
        else
            ++begin;
    }
    return word;
}


bool check_string_name(const string &tmp){
    bool upper_flag=false,number_flag=false,civil_flag=true,size_flag=false,lower_flag=false;
    civil_flag= civil_check(tmp);
    size_flag=tmp.size() > MAX_SIZE;
    for(const auto letter:tmp){
        if(std::isupper(letter))
            upper_flag=true;
        if(std::isdigit(letter))
            number_flag=true;
        if(std::islower(letter))
            lower_flag=true;
    }
    return (upper_flag&&number_flag&&civil_flag&&size_flag&&lower_flag);
}

bool check_string_number(const string &tmp){
    return tmp.size()>=MAX_SIZE;
}