#pragma once
#include <iostream>
#include<unordered_map>

typedef void(*func_1)(float&,float&); // ���庯�������ͣ���������ֵ�

typedef std::unordered_map<std::string, func_1> map; // �����ֵ�

void maptest(std::string str);

