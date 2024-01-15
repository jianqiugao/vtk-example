#include"maptest.h"

void add_func(float &a,float & b)
{
	std::cout <<"add results is "<< (a + b) << std::endl;
}
void sub_func(float& a, float& b)
{
	std::cout << "sub results is " << (a - b) << std::endl;
}
static map* dictor_ptr = new map;


static void add_func()
{
	dictor_ptr->insert(map::value_type("add", add_func));
	dictor_ptr->insert(map::value_type("sub", sub_func));
}

void maptest(std::string str)
{
	add_func();
	map::iterator it = dictor_ptr->find(str);
	float s = 3.5;
	float b = 1.5;
	it->second(s,b);
}