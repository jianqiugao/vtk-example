
#include <factory_test.h>

class apple : public fruit // 继承fruit类获得接口，可以create_fruit可以使用appel作为返回值
{
public:
	static const std::string typeName;
	apple() { std::cout << "apple" << std::endl; }

	void print_hello()
	{
		cout << "hello" << endl;
	}
};

const std::string apple::typeName = "apple";


add_fruit_to_dictor<apple> fruittable; // 这个函数的构造函数会自动的把typeName和apple类型传递进去


int factory_test()

{
	apple* apple_ = static_cast<apple*>(create_fruit("apple")); //工厂函数生成的是父类类型的，由于没有多态(没有写虚函数)因此这里采用static_cast转换为子类
	apple_->print_hello();
	return 0;
};