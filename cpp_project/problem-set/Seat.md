There are m seats in the room, numbered from 1 to m. There are also n groups of people where the i-th group has a 
i
​
  people and all of them require their seat number to be a multiple of b 
i
​
 .

Each seat can be assigned to at most one person. Are there enough seats in the room?

房间里有 m 个座位，编号从 1 到 m。另外还有 n 组人，其中第 i 组有 a 
i
​
  人，且每个人都要求他们的座位编号是 b 
i
​
  的倍数。

每个座位至多分配给一个人，问房间内是否有足够的座位。

## Input
There are multiple test cases. The first line of the input contains an integer T (1≤T≤10 
3
 ) indicating the number of test cases. For each test case:

The first line contains two integers n and m (1≤n≤20, 1≤m≤10 
18
 ) indicating the number of groups of people and the number of seats.

The second line contains n integers a 
1
​
 ,a 
2
​
 ,⋯,a 
n
​
  (1≤a 
i
​
 ≤10 
18
 ) where a 
i
​
  indicates the number of people in the i-th group.

The third line contains n integers b 
1
​
 ,b 
2
​
 ,⋯,b 
n
​
  (1≤b 
i
​
 ≤10 
18
 ) where all people in the i-th group require their seat number to be a multiple of b 
i
​
 .

It's guaranteed that the sum of a 
i
​
  of each test case will not exceed 10 
18
 , and also there are at most 10 test cases satisfying n>10.

有多组测试数据。第一行输入一个整数 T（1≤T≤10 
3
 ）代表测试数据组数。对于每组测试数据：

第一行输入两个整数 n 和 m（1≤n≤20，1≤m≤10 
18
 ）表示组数以及座位数。

第二行输入 n 个整数 a 
1
​
 ,a 
2
​
 ,⋯,a 
n
​
 （1≤a 
i
​
 ≤10 
18
 ），其中 a 
i
​
  是第 i 组的人数。

第三行输入 n 个整数 b 
1
​
 ,b 
2
​
 ,⋯,b 
n
​
 （1≤b 
i
​
 ≤10 
18
 ），其中第 i 组人都要求他们的座位编号是 b 
i
​
  的倍数。

保证每组数据 a 
i
​
  之和不超过 10 
18
 ，且至多只有 10 组数据满足 n>10。

## Output
For each test case output one line. If there are enough seats for all people output "Yes" (without quotes), otherwise output "No" (without quotes).

每组数据输出一行。若房间内有足够的座位输出 "Yes"（不输出引号），否则输出 "No"（不输出引号）。

## Sample Input
```
2
3 9
4 2 1
2 3 1
3 8
4 2 1
2 3 1
```
## Sample Output
```
Yes
No
```
## Hint
For the first sample test case, we can assign seat 2, 4, 6 and 8 to the first group, seat 3 and 9 to the second group and seat 7 to the third group. It is easy to notice that we must have at least 9 seats to meat everyone's requirement.

对于第一组样例数据，我们可以把座位 2，4，6 和 8 分给第一组，座位 3 和 9 分给第二组，座位 7 分给第三组。另外容易注意到，至少需要 9 个座位才能满足所有人的要求。