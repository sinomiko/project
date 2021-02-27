#include <string>
#include <iostream>
#include <future>       // std::packaged_task, std::future
#include <list>
#include <queue>
#include <thread>
#include <map>
#include <set>
#include <vector>
#include <assert.h>

using namespace std;

template <typename T>
class ClassA
{
public:
    class NestClass 
    {
    public:
        int a = 1;
    };
    NestClass getNestClass();
};

/**
 * \brief 
 * \return 
 */
template<typename T>
typename ClassA<T>::NestClass ClassA<T>::getNestClass()
{
    return NestClass();
}
/*
���ƹ��캯������ֵ�������������������һ������ľͲ�������

���帳ֵ�������������ƶ����죬�ƶ���ֵ�Ͳ���Ч��

�������Ϊ������������Ϊdefault���ñ������Զ����ɿ��Ա����ƶ�������ƶ����Ʋ��Զ�����
*/
class DefaultClass 
{
public:
    DefaultClass() = default;
    DefaultClass(const string& name_)
        :name(name)
    {
        cout << "DefaultClass string constructor" << endl;
    }
    DefaultClass(const DefaultClass& dc)
    {
        name = dc.name;
        cout << "DefaultClass copy constructor" << endl;
    }
/*    virtual ~DefaultClass() = default;*/
    virtual ~DefaultClass()//�����������������������ƶ����죬���й�����ø��ƹ��캯��
    {
        cout << "deconstructor" << endl;
    }
//     DefaultClass(DefaultClass&& dc)
//     {
//         name = std::move(dc.name);
//         cout << "DefaultClass move copy  constructor" << endl;
//     }
    string name;
};

class MapCompare {
public:
    struct AA {
        string name;
        set<string> address;
        bool operator==(const AA& a)const
        {
            if (name == a.name)
            {
                return true;
            }
            return false;
        }
    };
    bool operator==(const MapCompare& mc)const
    {
        return mc.testMap == testMap;
    }
    map<string, AA> testMap;
};

// bool operator==(const MapCompare::AA& lhs, const MapCompare::AA& rhs)
// {
//     if (lhs.name != rhs.name)
//     {
//         return false;
//     }
//     return true;
// }

int main(int argc, char* argv[])
{
//     ClassA<int> testA;
//     ClassA<int>::NestClass na=testA.getNestClass();
//     std::cout << na.a;

//     DefaultClass dc("111");
//     DefaultClass dc2 = std::move(dc);

     MapCompare mc;
     MapCompare::AA aa1;
     aa1.name = "aa1";
     aa1.address.insert("1");
     mc.testMap["1"] = aa1;

     MapCompare mc2;
     MapCompare::AA aa2;
     aa2.name = "aa2";
     aa2.address.insert("2");
     mc2.testMap["2"] = aa2;

    if (mc == mc2)
    {
        cout << "map equal" << endl;
    }
    else
    {
        cout << "map not equal" << endl;
    }
    mc2.testMap.erase("1");
    getchar();
    return 0;
}


