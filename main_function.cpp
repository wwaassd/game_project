//
// Created by crasher on 2022/7/10.
//
#include <iostream>
#include "main_function.h"
#include "Login.h"
#include "Create_account.h"
using std::cout;
using std::cin;
using std::endl;
const bool const_flag=true;
string flag_number=" ";

void login_window_print(){
    while(const_flag){
        system("cls");
        cout << "--------------------login window--------------------"<<endl;
        cout << "1.log in"<<endl;
        cout << "2.create an account"<<endl;
        cout << "3.command"<<endl;
        cout << "4.command"<<endl;
        cout << "5.command"<<endl;
        cout << "6.exit"<<endl;
        cout << "please input a number:";
        cin >> flag_number;
        if(flag_number.size()>1){
            throw input_size_erro("you are only allowed to input one number !");
        }
        solve_flag_number(flag_number.at(0));
    }
}

void problem_solving(decltype(login_window_print)* function_ptr){
start:
    try{
        function_ptr();
    } catch (failed_operation &e) {
        cout << e.what()<<endl;
        cout << "this has been operated !"<<endl;
        system("pause");
        system("cls");
        goto start;
    } catch (input_size_erro &e) {
        cout << e.what()<<endl;
        system("pause");
        system("cls");
        goto start;
    }
    catch(std::invalid_argument &e) {
        cout << e.what() <<endl;
        cout << "you will return to the input process!"<< endl;
        system("pause");
        system("cls");
        getchar();
        goto start;
    } catch (std::runtime_error &e) {
        cout << e.what()<<endl;
        cout << "you will return to log again!"<<endl;
        system("pause");
        system("cls");
        goto start;
    }
}

void solve_flag_number(const char ch){
    switch (ch) {
        case '1':{
                auto Log_pointer=Login::build_login();
                auto manipulator=Log_pointer->try_to_log(); //ff 判断是否登陆成功
                if(!manipulator.first)
                    throw failed_operation("failed to log in");
                else{
                    cout << "welcome back my friend! :";
                    delete manipulator.second;

                    manipulator.second=nullptr;
                    system("pause");
                    exit(10024);
                    //需要获得一个 User类
                    /*

                      登陆成功后的操作

                     */
                }
        }
        case '2':{
            auto manipulator=Create_account::try_to_create();
            if (manipulator.first) {
                //创建成功
                //直接使用户登录成功
                cout << "welcome my friend!" << endl;
                system("pause");

                delete manipulator.second;
                manipulator.second = nullptr;
                exit(10024);
                //需要获得一个 User类
                /*

                登陆成功后的操作

                */
            } else {
                throw failed_operation("failed to create an account");
            }
        }
        default:
            throw std::invalid_argument("you should input a number!");
    }
}

Uncopyable::~Uncopyable()=default;

void string_into_file(std::ofstream &os,const string &word1 ,const string &word2){
    if(os.is_open()){
        string line=word1+ " " +word2;
        os << line << endl;
    }
    else{}
}

bool check_string_in_file(std::ifstream &is,const string &name,const string &number){
    string line;
    while(std::getline(is,line)){
        std::istringstream istring(line);
        string file_name;
        string file_number;
        istring >>file_name >> file_number;
        if(name==file_name||number==file_number)
            return false;
    }
    return true;
}