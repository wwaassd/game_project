//
// Created by crasher on 2022/7/21.
//

#ifndef GAME_PROJECT_STRING_SOLUTION_H
#define GAME_PROJECT_STRING_SOLUTION_H
#include <string>
#include <map>
using std::map;
using std::string;
//需要存储文件名称对用于封装打开文件操作的map
extern map<string,string> file_root;
extern map<string,string> file_specific;
string& delete_blank(string &word); //删除字符串中以空格为主的杂乱的字符
bool civil_check(const string&);
bool check_string_name(const string&);
bool check_string_number(const string&);
#endif//GAME_PROJECT_STRING_SOLUTION_H
