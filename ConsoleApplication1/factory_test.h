#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

using namespace std;

class fruit // дһ����Ϊ�ӿڵĻ���
{
public:
	fruit() { cout << "ˮ��" << endl; };
};

typedef fruit* (*fruit_func)(); //���庯������
typedef std::unordered_map<std::string, fruit_func> dictor; //�����ֵ�
static dictor* dictor_ptr; //����һ����̬���͵��ֵ䣬Ϊ�˱����ظ������Ḳ���ֵ��е����ݣ����ﲻֱ��new����������һ����̬����ȥ����


static void construct_dictor()
{
	static bool constructed = false;
	if (!constructed)
	{
		constructed = true;
		dictor_ptr = new dictor;
	}
}

// �����������ʵ�������ֵ�

// ģ����Ĵ���
template <typename fruittype> //ģ�庯��һ��ͷ�ͷ�ļ�������ֿ��Ż�ͦ�鷳����Ҫ����������ָ������
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