//
// Created by crasher on 2022/7/10.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Login.h"
#include "string_solution.h"

void User::User_build(std::istream &is){
input:try {
        std::cout <<"please input your name:";
        is >>name;
               std::cout <<"please input your number:";
        is >>number;
        if(!check())
            throw std::runtime_error("your name or number is illegal");
    } catch (std::runtime_error e) {
        //账号非法处理
        std::cout << e.what()<< std::endl;
        std::cout << "return and try to input again!"<< std::endl;
        system("pause");
        goto input;
    }
}

bool User::check()const {
    return ((check_string_name(name))&&(check_string_number(number)));
}

inline bool User::check_user(std::string string_name,std::string string_number) const{
    return ((string_name==this->name)&&(string_number==this->number));
}

Login::Login():login_flag(false),pre_user(new Pre_User){
    std::ifstream is(loginFilePath);
    if(is) {
        string line;
        User user;
        while (std::getline(is, line)) {
            std::istringstream is_string(line);
            is_string >> user.name >> user.number;
            pre_user->insert(&user);
        }
    }
    else //Login构建过程中出错
        exit(-1024);
}

Login* Login::build_login(){
    static Login* tmp=nullptr;
    if(tmp==nullptr){
        tmp=new Login;
    }
    return tmp;
}

// 将登录信息写入pre_user
bool Login::find_user_message(std::ifstream& is,const User& user) const{
    string name;
    string number;
    string line;
    //寻找的方式需要改进
    while(getline(is,line)){
        std::istringstream is_string(line);
        is_string >> name >> number;
        const auto flag_user=user.check_user(name,number);
        if(flag_user){
            //将信息写到文件中
            std::ifstream pre_is(loginFilePath);
            if(pre_is){
                auto fflag= check_string_in_file(pre_is,name,number);
           if(fflag){
               std::ofstream os(loginFilePath,
                                std::ofstream::binary|std::ofstream::app);
               if(os)
                   string_into_file(os,name,number);
           }
            return true;
            }
        }
    }
    return false;
}


std::pair<bool,const User*> Login::try_to_log() {
    const User * user=new User(std::cin);
    if(!pre_user->empty()) {
        auto be = std::find_if(pre_user->cbegin(),
                          pre_user->cend(),
                          [&](User *tmp) -> bool {
                                     return *user == *tmp; });
        if (be != pre_user->cend()) {
            login_flag = true;
            return {login_flag, user};
        }
    }
        try {
            std::ifstream is;
            is.open(loginFilePath,
                    std::ifstream::binary);
            if (is) {
               login_flag=find_user_message(is,*user);
               return {login_flag,user};
            } else
                throw std::runtime_error("failed to open the file");
        } catch (std::runtime_error e) {
            std::cout << e.what() << std::endl;
            system("pause");
            return{false,user};
        }
    }


void Login::finish() const {
    if(!flag)
        return ;
    std::ofstream os(loginFilePath,
                     std::ofstream::app | std::ofstream::binary);
    if(os){
        string line;
        for(const auto uu:pre_user->pre_set){
            line=uu->name+" "+uu->number;
            os << line << std::endl;
        }
    }
    else{
        exit(-1);
    }
}
 Login::~Login(){
     try {
         flag=true;
         finish();
     } catch (...) {
         exit(-1024);
     }
 }

 set<User*>::iterator Pre_User::insert(User *tmp){
     if(size_check())
         return pre_set.emplace(tmp).first;
     else{
         pre_set.erase(pre_set.begin());
         return pre_set.emplace(tmp).first;
     }
 }
