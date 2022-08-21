//
// Created by crasher on 2022/7/29.
//

#include "Create_account.h"
#include "string_solution.h"
bool Create_account::check(const User *tmp) {
    std::ifstream is;
    /*file_root["LOGIN"] +
file_specific["login"]*/
    std::ifstream in("login.txt");
    if (!in){
        std::ofstream out("login.txt");
        out.close();
    }
    in = std::ifstream ("login.txt");
    if (in) {
        return check_string_in_file(is, tmp->get_name(), tmp->get_number());
    } else
        return false;//失败
}


//Create_account* Create_account::build(){
//        static Create_account *tmp=nullptr;
//        if(tmp==nullptr){
//            tmp=new Create_account;
//        }
//        return tmp;
//}


std::pair<bool, const User *> Create_account::create_account(const User *tmp) {
    std::ofstream os("login.txt");
    if (os) {
        string_into_file(os, tmp->get_name(), tmp->get_number());
        return std::make_pair(true, tmp);
    }
    return std::make_pair(false, nullptr);
}


std::pair<bool, const User *> Create_account::try_to_create() {
    User *user = new User(std::cin);
    if (check(user)) {
        return create_account(user);
    } else {
        return std::make_pair(false, nullptr);
    }
}