#include <stdlib.h> //��Ҫ�õ�Cʽ�ڴ���亯��
#include<iostream>
class Resource{
public:
	Resource()
	{
		m_num=0;
	}
	Resource(int num)
	{
		m_num=num;
	}
	void setNum(int num)
	{
		m_num=num;
	}
	void printNum()const
	{
		std::cout<<m_num<<std::endl;
	}
private:
	int m_num;
}; //������Ҫ����װ����Դ��
class NoHashObject
{
private:
	Resource* ptr ;//ָ�򱻷�װ����Դ
	void* operator new(size_t size) //���ϸ�ʵ�֣�����ʾ��֮��
	{
			return malloc(size) ;
	}
	void operator delete(void* pp) //���ϸ�ʵ�֣�����ʾ��֮��
	{
		free(pp) ;
	}
public:
	NoHashObject()
	{
		//�˴����Ի����Ҫ��װ����Դ������ptrָ��ָ�����Դ
		ptr = new Resource() ;
	}
	~NoHashObject()
	{
		delete ptr ; //�ͷŷ�װ����Դ
	}
	void setResource(int num)
	{
		ptr->setNum(num);
	}
	void printResource()const
	{
		ptr->printNum();
	}
};

int main(void)
{
//NoHashObject���ھ���һ����ֹ�Ѷ�������ˣ������д�����´��룺
//	NoHashObject* fp = new NoHashObject() ; //�����ڴ���
//	delete fp ;

	char* temp = new char[sizeof(NoHashObject)] ;
//ǿ������ת��������ptr��һ��ָ��NoHashObject�����ָ��
	NoHashObject* obj_ptr = (NoHashObject*)temp ;
	temp = NULL ; //��ֹͨ��tempָ���޸�NoHashObject����
//��һ��ǿ������ת������rpָ��ָ�����NoHashObject�����ptr��Ա
	Resource* rp = (Resource*)obj_ptr ;
//��ʼ��obj_ptrָ���NoHashObject�����ptr��Ա
	rp = new Resource() ;
//���ڿ���ͨ��ʹ��obj_ptrָ��ʹ�ö��е�NoHashObject�����Ա��
	rp->setNum(4);
//	rp->printNum();
//	obj_ptr->setResource(4);
	obj_ptr->printResource();
	delete rp ;//�ͷ���Դ
	temp = (char*)obj_ptr ;
	obj_ptr = NULL ;//��ֹ����ָ�����
	delete [] temp ;//�ͷ�NoHashObject������ռ�Ķѿռ䡣
}