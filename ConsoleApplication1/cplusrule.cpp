#include<cplusrule.h>



std::string current_working_directory()
{
    char buff[250];
    _getcwd(buff, 250);
    for (int i = 0; i < 100; i++) { if (buff[i] != '$') { cout << buff[i]; } else { cout << endl; break; } };

    std::string current_working_directory(buff);
    return current_working_directory;
}

void getcurentpath()
{
    std::cout << "Current working directory: " << current_working_directory() << std::endl;
}

void getcurentpath_method1()
{
    cout << MAX_PATH << endl;
    char buffer[MAX_PATH];
    _getcwd(buffer, MAX_PATH);
}




unique_ptr <vector<int>> vecAddVec(vector<int>const& a, vector<int> const& b)
{
    unique_ptr <std::vector<int>> numbers2 = make_unique<std::vector<int>>();//
    try
    {
        throw "Division by zero condition!";
        //assert(a.size() == b.size()); // c++�еĶ���
    }
    catch (const char* msg)
    {
        cerr << msg << endl;
    }
    ;
    cout << a.size() << b.size() << endl;
    for (int it = 0; it < a.size(); ++it)
    {
        numbers2->push_back(a[it] + b[it]);
    }
    return  numbers2;
}


// ����ģ�嶨��������ֿ�
template <typename T>  void Print_value(T value)
{
    std::cout << value << std::endl;
}

//��ģ�嶨��������ֿ�
template <class T> void stack<T>::push(T values)
{ 
    mystack->push_back(values);
};



template <class T> T stack<T>::pop()

{
    if (!mystack->empty()) 
    {
        T lastValue = mystack->back();
        return lastValue;
    }
}

template <class T>
std::unique_ptr <vector<T>> stack<T>::mystack = std::make_unique<vector<T>>();


template void Print_value<int>(int); // ��Ҫ��Щ��ô���䣬��ʵ�ֵ����͸�Ū���
template void Print_value<float>(float);

template class stack<int>; // ��Ҫ��Щ��ô���䣬��ʵ�ֵ����͸�Ū���
template class stack<float>;

void use_template()
{
    int a = 512.;
    Print_value(a);
    stack<int> test_stack;
    test_stack.push(a);
    int valus = test_stack.pop();
    cout << valus << endl;

}

void sort_values()
{
    std::vector<int> numbers1 = { 3,1,0,6,2 };
    sort(numbers1.begin(), numbers1.end());
    for (auto it = numbers1.begin(); it != numbers1.end(); ++it)
    {
        cout << *it << " ";
    };
}


void random_number_generate()
{
    int min = 0, max = 100;
    random_device seed; // Ӳ���������������
    mt19937 engine(seed()); // ���������������������
    //uniform_int_distribution<> distrib(min, max); // �����������Χ����Ϊ���ȷֲ�
    uniform_real_distribution<> distrib(min, max);
    double random = distrib(engine); // ���������
    cout << "�������" << random << endl;
}