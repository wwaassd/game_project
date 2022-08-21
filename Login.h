//
// Created by crasher on 2022/7/10.
//

#ifndef GAME_PROJECT_LOGIN_H
#define GAME_PROJECT_LOGIN_H

#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include "main_function.h"
#include <thread>


using std::map;
using std::string;
using std::set;
using std::vector;

class User;
class Pre_User;
class Login :public Uncopyable {
public:
    static Login* build_login(); //构造使用函数
    std::pair<bool,const User*> try_to_log();
    void finish() const;
    ~Login() override;
private:
    bool flag=false;
    Pre_User *pre_user;
    bool login_flag; //登录是否成功
    Login();
    bool find_user_message(std::ifstream&,const User&) const;
};  //登录使用类


class Pre_User: public Uncopyable{
    friend class Login;
    enum{MAX_SIZE=10};
public:
    //构造函数和析构函数需要自己写
    Pre_User()=default;
    ~Pre_User() override=default;
    bool empty(){return pre_set.empty();}
    set<User*>::iterator cbegin() {return pre_set.cbegin();}
    set<User*>::iterator cend() {return pre_set.cend();}
    set<User*>::iterator begin() {return pre_set.begin();}
    set<User*>::iterator end() {
        return pre_set.end();}
    set<User*>::iterator insert(User*);
    bool size_check(){
        return pre_set.size()<MAX_SIZE;
    }
private:
    set<User*> pre_set;
};  //最近用户列表的封装类


class User{
    friend class Login;
friend set<User*>::iterator Pre_User::insert(User*);
public:
 explicit User(std::istream &is){
        User_build(is);
    }
    User()=default;
    User(string nname,string nnumber):name(std::move(nname)),number(std::move(nnumber)){}
    [[nodiscard]] bool check_user(std::string,std::string)const; //检查账号是否正确
    bool operator<(const User& tmp) {
        return this->name < tmp.name;
    }
    bool operator==(const User &tmp)const {return ((name==tmp.name)&&(number==tmp.number));}
    bool operator!=(const User &tmp)const {return (!this->operator==(tmp));}
    ~User()=default;
    User(const User &)=default;
    [[nodiscard]] const string& get_name()const {return name;}
    [[nodiscard]] const string& get_number()const {return number;}
private:
    void User_build(std::istream &is);
    std::string name;
    std::string number;
    [[nodiscard]] bool check()const; //检查账号是否合规,注册账号时使用
};  //用户类 //可能需要和用户的角色信息相关联
#endif//GAME_PROJECT_LOGIN_H
