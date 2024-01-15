#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class fruit // 写一个作为接口的基类
{
public:
	fruit() { cout << "水果" << endl; };
};

typedef fruit* (*fruit_func)(); //定义函数类型
typedef std::unordered_map<std::string, fruit_func> dictor; //定义字典
static dictor* dictor_ptr; //申明一个静态类型的字典，为了避免重复创建会覆盖字典中的内容，这里不直接new出来而是用一个静态函数去创建


static void construct_dictor()
{
	static bool constructed = false;
	if (!constructed)
	{
		constructed = true;
		dictor_ptr = new dictor;
	}
}

// 调用这个函数实现生成字典

// 模板类的创建
template <typename fruittype> //模板函数一般就放头文件，如果分开放还挺麻烦，需要把所有类型指定出来
class add_fruit_to_dictor
{
public:
	static fruit* New()
	{
		return  new fruittype;
	}
	add_fruit_to_dictor(const std::string& str = fruittype::typeName)
	{
		construct_dictor();
		dictor_ptr->insert(dictor::value_type(str, New));
	}
};

static fruit* create_fruit(std::string str)
{
	dictor::iterator it = dictor_ptr->find(str);
	if (it != dictor_ptr->end())
	{
		return it->second();
	}
	else
	{
		return nullptr;
	}
}


int factory_test();