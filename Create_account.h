//
// Created by crasher on 2022/7/29.
//

#ifndef GAME_PROJECT_CREATE_ACCOUNT_H
#define GAME_PROJECT_CREATE_ACCOUNT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Login.h"
#include "main_function.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Create_account:public Uncopyable {
public:
    //static Create_account* build();
    [[nodiscard]] static std::pair<bool,const User*> try_to_create();
private:
    static bool check(const User*);
    static std::pair<bool,const User*> create_account(const User*);
    Create_account()=default;
}; //创建账号类


#endif//GAME_PROJECT_CREATE_ACCOUNT_H
