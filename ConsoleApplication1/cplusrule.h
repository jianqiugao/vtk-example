#pragma once

#include <direct.h>
#include<string>
#include<iostream>
#include <Windows.h>
#include <iostream>
#include <cassert>
#include<vector>
#include <algorithm> // �����㷨��
#include <random>
#include <typeinfo>
using namespace std;

void getcurentpath_method1();
std::string current_working_directory(); 
void getcurentpath();



//����ģ�嶨��������ֿ�
template<typename T> void Print_value(T value);


//��ģ�嶨��������ֿ�
template <class T>  //����Ӧ��������������
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