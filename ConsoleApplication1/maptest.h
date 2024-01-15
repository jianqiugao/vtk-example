#pragma once
#include <iostream>
#include<unordered_map>

typedef void(*func_1)(float&,float&); // 定义函数的类型，方便放入字典

typedef std::unordered_map<std::string, func_1> map; // 定义字典

void maptest(std::string str);

