//
// Created by crasher on 2022/7/10.
//

#ifndef GAME_PROJECT_MAIN_FUNCTION_H
#define GAME_PROJECT_MAIN_FUNCTION_H
#include <string>
#include <stdexcept>
using std::string;

extern const bool const_flag;
extern std::string flag_number;
class input_size_erro: public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};
class failed_operation :public std::runtime_error{
public:
    using std::runtime_error::runtime_error;
};
class Uncopyable {
public:
    Uncopyable(const Uncopyable&)=delete;
    Uncopyable& operator=(const Uncopyable&)=delete;
protected:
    Uncopyable(){}
    virtual ~Uncopyable()=0;
};
void string_into_file(std::ofstream&,const string&,const string&);
bool check_string_in_file(std::ifstream&,const string&,const string&);
void login_window_print();
void solve_flag_number(char);
void problem_solving(decltype(login_window_print)*);
#endif//GAME_PROJECT_MAIN_FUNCTION_H
