#include <iostream>
//https://www.cnblogs.com/steven_oyj/archive/2010/05/22/1741376.html
/*
1������
      �����㷨ʵ����һ������ö�ٵ��������Թ��̣���Ҫ�����������Թ�����Ѱ������Ľ⣬�������Ѳ������������ʱ���͡����ݡ����أ����Ա��·����

   ���ݷ���һ��ѡ������������ѡ��������ǰ�������ԴﵽĿ�ꡣ����̽����ĳһ��ʱ������ԭ��ѡ�񲢲��Ż�ﲻ��Ŀ�꣬���˻�һ������ѡ�������߲�ͨ���˻����ߵļ���Ϊ���ݷ������������������ĳ��״̬�ĵ��Ϊ�����ݵ㡱��

     ��ิ�ӵģ���ģ�ϴ�����ⶼ����ʹ�û��ݷ����С�ͨ�ý��ⷽ���������ơ�

2������˼��
   �ڰ�����������н�Ľ�ռ����У�����������������Ĳ��ԣ��Ӹ����������̽����ռ�������̽����ĳһ���ʱ��Ҫ���жϸý���Ƿ��������Ľ⣬����������ʹӸý���������̽����ȥ������ý�㲻��������Ľ⣬������������Ƚ����ݡ�����ʵ���ݷ����Ƕ���ʽͼ��������������㷨����

       ���û��ݷ�����������н�ʱ��Ҫ���ݵ������Ҹ��������п��е�������Ҫ�ѱ�������Ž�����

       ����ʹ�û��ݷ�����һ����ʱ��ֻҪ�����������һ����Ϳ��Խ�����

3���û��ݷ������һ�㲽�裺
    ��1������������⣬ȷ������Ľ�ռ䣺

            ����Ӧ��ȷ��������Ľ�ռ䣬����Ľ�ռ�Ӧ���ٰ��������һ�������ţ��⡣

    ��2��ȷ��������չ��������

    ��3����������ȷ�ʽ������ռ䣬���������������ü�֦����������Ч������

4���㷨���
 ��1��������

������Ľ���һ��nά����(a1,a2,������,an),Լ��������ai(i=1,2,3,��..,n)֮������ĳ����������Ϊf(ai)��
	  
��2���ǵݹ���ݿ��
 int a[n],i;
 ��ʼ������a[];
 i = 1;
 while (i>0(��·����)   and  (δ�ﵽĿ��))  // ��δ���ݵ�ͷ
 {
     if(i > n)                                              // ������Ҷ���
     {   
           ������һ���⣬�����
     }
     else                                                   // �����i��Ԫ��
     { 
           a[i]��һ�����ܵ�ֵ��
           while(a[i]�ڲ�����Լ���������������ռ���)
           {
               a[i]��һ�����ܵ�ֵ��
           }
           if(a[i]�������ռ���)
          {
               ��ʶռ�õ���Դ��
               i = i+1;                              // ��չ��һ�����
          }
          else 
         {
               ������ռ��״̬�ռ䣻            // ����
               i = i �C1; 
          }
 }
  
��3���ݹ���㷨���
���ݷ��ǶԽ�ռ�����������������һ�������ʹ�õݹ麯����ʵ�ֻ��ݷ��Ƚϼ򵥣�����iΪ��������ȣ��������

int a[n];
try(int i)
{
    if(i>n)
       ������;
     else
    {
       for(j = �½�; j <= �Ͻ�; j=j+1)  // ö��i���п��ܵ�·��
       {
           if(fun(j))                 // �����޽纯����Լ������
             {
                a[i] = j;
              ...                         // ��������
                try(i+1);
              ����ǰ������������a[i]�ÿ�ֵ�ȣ�;
              }
         }
     }
}
*/
//�˻ʺ�����
using namespace std;
#define  NUM 8
int a[NUM][NUM] = { 0 };
int sum = 0;

bool check(int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        if (a[i][c])
        {
            return false;
        }
    }

    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--)
    {
        if (a[i][j])
        {
            return false;
        }
    }
    for (int i = r, j = c; i >= 0 && j < 8; i--, j++)
    {
        if (a[i][j])
        {
            return false;
        }
    }
    return true;
}

/*����ڷŽ��*/
void print()
{
    cout << "solution: " << ++sum << endl;
    for (int i = 0; i < NUM; i++)
    {
        for (int j = 0; j < NUM; j++)
        {
            if (a[i][j])
            {
                cout << "�� ";
            }
            else
            {
                cout << "�� ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void Queue(int r)
{
    if (r == NUM)
    {
        print();
        return;
    }
    for (int c = 0; c < NUM; c++)
    {
        if (check(r, c))
        {
            //
            a[r][c] = 1;
            Queue(r + 1);
            a[r][c] = 0;
            //
        }
    }
}


#include <stdio.h>
/*
https://blog.csdn.net/yangliuy/article/details/7194199
�������ȳ������������λ����logN�㷨 ���η�
��Ŀ����������Ϊn�ķǵݼ�����A��B����B����A�ĺ����ɳ�Ϊ2n������C������㷨��C����λ������nС������

˼·��O(n)���㷨�������ҵ����ؼ����ö��ֵ�˼�����logn�㷨������ؼ����ú�a��b�����нű��Ϊ��ֵ��Ԫ�صĴ�С��ϵ��
            ֱ���뷨�ǣ������λ��������a�У�
			��ô��a[m]<b[n-m-2]����ʱ��a[m]С�������ֻ��n-2������a[m]������Ϊ��nС����
			ƫС�������;��a[m]> b [n-m-1],��ʱ��a[m]С����������n����a[m]������Ϊ��nС����ƫ������ҽ�;
			��a[m]����b[n-m-2]��b [n-m-1]��a[m]ǡ��Ϊ��nС���� ��λ��������b�е�������ơ�
*/
int findNthNumber(int a[], int b[], int n){  
    int l = 0, r = n -1;  
    int m;  
    while(l <= r){  
        m = (l + r) / 2;  
        if(m == n - 1 || a[m] < b[n - m -2]){  
            //��ʱ��a[m]С�������ֻ��n-2������a[m]������Ϊ��nС����ƫС�������  
            l = m + 1;  
        }  
        else if (a[m] < b [n - m - 1]){  
            //��ʱ��a[m]С����ǡ����n-1����a[m]���ǵ�nС��������  
            return a[m];  
        }  
        else r = m - 1;//��ʱ��a[m]С����������n������a[m]������Ϊ��nС����ƫ������ҽ�  
    }  
    //��λ����b�����е����������������  
    l = 0, r = n -1;  
    while(l <= r){  
        m = (l + r) / 2;  
        if(m == n - 1 || b[m] < a[n - m -2]){  
            l = m + 1;  
        }  
        else if (b[m] < a [n - m - 1]){  
            return b[m];  
        }  
        else r = m - 1;  
    }  
}  

//Ҳ����ȡa[m]��b[n-m-2]�нϴ��һ����Ȼ����a[m+1]��b[n-m-1]���Ƚϣ��򻯺�Ĵ�������
int findNthNumber(int a[], int b[], int n){  
    int l = 0, r = n -1;  
    int m, tmp;  
    while(l <= r){  
        m = (l + r) / 2;  
        tmp = (a[m] < b [n - m - 2] ? b[n - m - 2] : a[m]);  
        //tmpȡa[m]��b[n-m-2]�нϴ��һ����Ȼ����a[m+1]��b[n-m-1]���Ƚ�  
        if(tmp > b [n - m - 1]){  
            r = m - 1;  
        }  
        else if(tmp > a [m + 1]){  
            l = m + 1;  
        }  
        else return tmp;  
    }  
}  

double getMedian(int arr1[], int arr2[], int n)

{
    int i = 0, j = 0; //�ֱ��� arr1�� arr2�ĵ�ǰ�±�
    int m1 = -1, m2 = -1; //����������λ��. ������2n�����϶���������λ��
    for (int cnt = 0; cnt <= n; cnt++)

    {
        if (i < n && (arr1[i] < arr2[j] || j >= n))

        {
            m1 = m2;
            m2 = arr1[i++];
        }

        else

        {
            m1 = m2;
            m2 = arr2[j++];
        }
    }
    return (m1 + m2) / 2.0;
}

/* ������A��B��������λ�� */
int find_median(int *A, int *B, int m, int n, int s, int t)
{
    int  p, c;

    c = (m + n - 1) / 2;  /* �ж��ٸ���С������λ�� */
    p = (s + t) / 2;

    /* �������λ������A�У��ʹ�����B�� */
    if (s > t) {
        return find_median(B, A, n, m, 0, n - 1);
    }

    /* ����A����p����С��A[p], ���ҽ�������B����c-p����С��A[p], A[p]������λ�� */
    if (A[p] >= B[c - p - 1] && A[p] <= B[c - p]) {
        return A[p];
    }

    /* A[p]̫С�ˣ�������A����һ������������� */
    if (A[p] < B[c - p - 1]) {
        return find_median(A, B, m, n, p + 1, t);
    }

    /* A[p]̫���ˣ�������A����һ����С�������� */
    return find_median(A, B, m, n, s, p - 1);
}
/**
 *  \brief Brief description
 *  
 *  \return Return description
 *  
 *  \details More details
 *  
 *  
 */
 const int N = 8;//�ʺ�ĸ���
int positon[N];//��Żʺ��λ��
int solCount = 0;//��¼�ж����ְڷ�

              /*�жϵ�row�з��õ�λ���Ƿ�����Ҫ��*/
bool valid(int row)
{
    for (int i = 0; i < row; ++i)
    {
        // �����ǰ��ź�λ�õĲ���ͬһ�У�Ҳ���ڶԽ����ϣ��򷵻�true�����򷵻�false
        if (positon[i] == positon[row] || abs(positon[i] - positon[row]) == abs(i - row))
            return false;
    }
    return true;
}

/*����ڷŽ��*/
void print()
{
    cout << "���ǵ�" << ++solCount << "�ְڷ���" << '\n';
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (positon[i] == j)
                cout << "�� ";
            else
                cout << "�� ";
        }
        cout << '\n';
    }
    cout << endl;
}

/*���ݷ������ڷ�λ��*/
void trail(int row = 0)
{
    // ���������N�У���������
    if (N == row)
    {
        print();
        return;
    }
    for (int column = 0; column < N; ++column)
    {
        positon[row] = column;// �����ڵ�row�е�column��
                              // ��������������������һ��
        if (valid(row)) trail(row + 1);
        // ����������������������һ��ѭ���������ݻ�ȥ�ڵ�row������Ѱ�Ұڷŵ�λ��
    }
}
/**
����ַ�����ȫ����
 */
 #include <stdio.h>  

void swap2(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
/* ��ӡ�ַ�����ȫ����*/
void permute(char *str, int i, int n)
{
    int j;
    if (i == n)
        printf("%s\n", str);
    else
    {
        for (j = i; j <= n; j++)
        {
            swap2((str + i), (str + j));
            permute(str, i + 1, n);
            swap2((str + i), (str + j)); //����  
        }
    }
}

int main()
{
	/*****�˻ʺ�********/
	Queue(0);
    /******������λ��N*******/
	int ar1[] = { 1, 12, 15, 26, 38 };
    int ar2[] = { 2, 13, 17, 30, 45 };

    int n1 = sizeof(ar1) / sizeof(ar1[0]);
    int n2 = sizeof(ar2) / sizeof(ar2[0]);

    printf("%d\n", find_median(ar1, ar2, n1, n2, 0, n1-1));
	
	/*****ȫ����********/
	char str[] = "ABC";
    int len = sizeof(str) / sizeof(char) - 2;
    permute(str, 0, len);
	
    getchar();
    return 0;
}
