//unary_function��binary_function���
/*******
unary_function��binary_function���

1.unary_function��binary_function����
1.1 unary_function����
unary_function������Ϊһ��һԪ��������Ļ��࣬��ֻ�����˲����ͷ���ֵ�����ͣ����������أ������������������Ӧ�ý���������ȥ��ɡ�

1.2 unary_functionԴ��
 template <class Arg, class Result>
 struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

��Ա����	����	ע��
argument_type	��һ��ģ�����(Arg)	()���غ����Ĳ�������
result_type	�ڶ���ģ�����(Result)	()���غ����ķ���ֵ����
*/

// unary_function example
#include <iostream>     // std::cout, std::cin
#include <functional>   // std::unary_function
#include <vector>
#include <map>
#include <string>
using namespace std;
struct IsOdd : public std::unary_function<int,bool> {
  bool operator() (int number) {return (number%2!=0);}
};

class vector_finder
{
public:
    vector_finder(const int a) :m_i_a(a) {}
    bool operator ()(const std::vector<struct value_t>::value_type &value)
    {
        return value.a == m_i_a;
    }
private:
    int m_i_a;
};


int main () {
  IsOdd IsOdd_object;
  IsOdd::argument_type input;
  IsOdd::result_type result;

  std::cout << "Please enter a number: ";
  std::cin >> input;

  result = IsOdd_object (input);

  std::cout << "Number " << input << " is " << (result?"odd":"even") << ".\n";

  vector<int> test1;
  test1.push_back(1);
  test1.push_back(2);
  auto xx = find(test1.begin(),test1.end(),2);

  map<int,string> test_map;
  test_map.insert(make_pair());
  test_map.push_back(2);
  find(test_map.begin(),test_map.end(),);

  getchar();
  getchar();
  return 0;
}
/*
2. binary_function����
2.1 binary_function����
binary_function������Ϊһ����Ԫ��������Ļ��࣬��ֻ�����˲����ͷ���ֵ�����ͣ����������أ������������������Ӧ�ý���������ȥ��ɡ�

2.2 binary_functionԴ��
1 template <class Arg1, class Arg2, class Result>
2   struct binary_function {
    3     typedef Arg1 first_argument_type;
    4     typedef Arg2 second_argument_type;
    5     typedef Result result_type;
    6
};

��Ա����	����	ע��
first_argument_type	��һ��ģ�����(Arg1)	()���غ����ĵ�һ����������
second_argument_type	��һ��ģ�����(Arg2)	()���غ����ĵڶ�����������
return_type	��һ��ģ�����(Result)	()���غ����ķ���ֵ����
2.3 ����
*/

/*
// binary_function example
#include <iostream>     // std::cout, std::cin
#include <functional>   // std::binary_function

struct Compare : public std::binary_function<int,int,bool> {
  bool operator() (int a, int b) {return (a==b);}
};

int main () {
  Compare Compare_object;
  Compare::first_argument_type input1;
  Compare::second_argument_type input2;
  Compare::result_type result;

  std::cout << "Please enter first number: ";
  std::cin >> input1;
  std::cout << "Please enter second number: ";
  std::cin >> input2;

  result = Compare_object (input1,input2);

  std::cout << "Numbers " << input1 << " and " << input2;
  if (result)
      std::cout << " are equal.\n";
  else
      std::cout << " are not equal.\n";

  return 0;
}
*/

