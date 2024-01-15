#pragma once
#include <iostream>
using namespace std;
#define MUL(x, y)\
 (x * y)
#define STRING(x) #x
//// 用宏来简化代码
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
//// 下面定义了一个构造的宏,这里面的creat居然和opencv中的一个creat给重合了
#define _create(name ,classtype) \
myname name = classtype();

#define SOMEMACRO 123456
#define MACROPARAM(x) new int(x);
#define MACROTOSTR2(x) #x
#define PRINTMACRO(x) #x " = " MACROTOSTR2(x)
#pragma message(PRINTMACRO(MACROPARAM(SOMEMACRO))) //预处理的时候会打印
#define _trace_(fmt, ...) printf("%s \n %d \n %s\n %s\n"##fmt, __FILE__, __LINE__,__DATE__,__TIME__, ##__VA_ARGS__)
#define _segment_(seg) seg


void  macrotest();