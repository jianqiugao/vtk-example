
#include <somemacro.h>


myname::myname()
{
	cout << "123" << "was created" << endl;
}
void  macrotest()
{

	float a = 2.5;
	float b = 3.55;
	int res = MUL(a, b);
	cout << res << endl;
	const char* str = STRING(test);  // str 的内容是 "test"
	cout << *str << *(str + 1) << *(str + 2) << *(str + 3) << endl;
	Print("HELLO_WORLD");
	/*std::string he = "gao";*/

	_create(he, myname);// 通过宏来定义类，事先并没有申明he

	cout << "看一下值" << he.a << endl; //但确可以正常的使用

	_trace_("printf message%d %s\n", 20, "some reason");
	cout << __DATE__ << endl;
}