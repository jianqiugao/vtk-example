
#include <factory_test.h>

class apple : public fruit // �̳�fruit���ýӿڣ�����create_fruit����ʹ��appel��Ϊ����ֵ
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


add_fruit_to_dictor<apple> fruittable; // ��������Ĺ��캯�����Զ��İ�typeName��apple���ʹ��ݽ�ȥ


int factory_test()

{
	apple* apple_ = static_cast<apple*>(create_fruit("apple")); //�����������ɵ��Ǹ������͵ģ�����û�ж�̬(û��д�麯��)����������static_castת��Ϊ����
	apple_->print_hello();
	return 0;
};