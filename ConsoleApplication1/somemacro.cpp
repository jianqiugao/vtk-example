
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
	const char* str = STRING(test);  // str �������� "test"
	cout << *str << *(str + 1) << *(str + 2) << *(str + 3) << endl;
	Print("HELLO_WORLD");
	/*std::string he = "gao";*/

	_create(he, myname);// ͨ�����������࣬���Ȳ�û������he

	cout << "��һ��ֵ" << he.a << endl; //��ȷ����������ʹ��

	_trace_("printf message%d %s\n", 20, "some reason");
	cout << __DATE__ << endl;
}