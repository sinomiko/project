#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account
{
	unsigned int id;
	char citizen_id[19];
	char name[32];
	char address[128];
	unsigned int balance; // ���

	Account* next; 
};

// -1, ��ʾ��������0����ʾ������ȷ��
// 1, ��ʾ�ж�����
int input(Account* acc)
{
	char buf[128];

	// ����ID
	printf("ID: ");
	gets(buf);
	acc->id = atoi(buf); //a to i
	if(acc->id == 0)
	{
		return 1;
	}

	// �������֤��
	printf("���֤��: ");
	gets(acc->citizen_id);

	// ��Ч�Լ��
	if(strlen(acc->citizen_id) != 4)
	{
		printf("������18λ�����֤��!\n");
		return -1;
	}

	// ��������
	printf("����: ");
	gets(acc->name);

	printf("��ַ: ");
	gets(acc->address);

	printf("���: ");
	gets(buf);
	acc->balance = atoi(buf); //a to i

	return 0;
}

Account m_head = {0}; // ��ͷ�����ͷ�ڵ�

void add(const Account* acc)
{
	// ����һ������
	Account* pnew = (Account*)malloc(sizeof(Account));
	*pnew = *acc; // ��������s

	// ���½ڵ���ӵ�������
	pnew->next = m_head.next;
	m_head.next = pnew;
}

Account* find(const char* name)
{
	Account* p = m_head.next;
	while(p)
	{
		if( strcmp (name, p->name) == 0 )
		{
			return p;
		}
		p = p->next;
	}

	return NULL;
}

int main()
{
	// �����û�����, ���浽����
	while(1)
	{
		Account acc;
		int ret = input(&acc);
		if(ret == 1)
		{
			break;
		}
		else if(input(&acc) < 0)
		{
			printf("**** ��������� ****!\n");
		}
		else
		{
			add(&acc);
			printf(" ����ڵ� !!! \n");
		}
	}

	// ����
	char buf[128];
	printf("����Ҫ��������: ");
	gets(buf);
	Account* p = find(buf);
	if(p != NULL)
	{
		printf("�ҵ��ʻ�\n");
		printf("ID: %d, ����: %s \n", p->id, p->name);
	}
	else
	{
		printf("�޴��ʻ�!\n");
	}
	return 0;
}