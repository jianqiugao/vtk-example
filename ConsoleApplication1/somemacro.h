#pragma once
#include <iostream>
using namespace std;
#define MUL(x, y)\
 (x * y)
#define STRING(x) #x
//// �ú����򻯴���
#define Print(x)\
std::cout << "Value: " << x << std::endl

class myname
{
public:
	int a = 5;
	myname();
};
//
//
//// ���涨����һ������ĺ�,�������creat��Ȼ��opencv�е�һ��creat���غ���
#define _create(name ,classtype) \
myname name = classtype();

#define SOMEMACRO 123456
#define MACROPARAM(x) new int(x);
#define MACROTOSTR2(x) #x
#define PRINTMACRO(x) #x " = " MACROTOSTR2(x)
#pragma message(PRINTMACRO(MACROPARAM(SOMEMACRO))) //Ԥ�����ʱ����ӡ
#define _trace_(fmt, ...) printf("%s \n %d \n %s\n %s\n"##fmt, __FILE__, __LINE__,__DATE__,__TIME__, ##__VA_ARGS__)
#define _segment_(seg) seg


void  macrotest();