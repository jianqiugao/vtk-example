#pragma once

#include <direct.h>
#include<string>
#include<iostream>
#include <Windows.h>
#include <iostream>
#include <cassert>
#include<vector>
#include <algorithm> // 包含算法库
#include <random>
#include <typeinfo>
using namespace std;

void getcurentpath_method1();
std::string current_working_directory(); 
void getcurentpath();



//函数模板定义和申明分开
template<typename T> void Print_value(T value);


//类模板定义和申明分开
template <class T>  //这里应该是在申明变量
class stack
{

public:
    static std::unique_ptr <vector<T>> mystack ;
    stack(){};
    void push(T values);
    T pop();
};

void use_template();
void sort_values();
void random_number_generate();