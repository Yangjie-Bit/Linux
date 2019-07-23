> 每个人, 都有一段沉默的时光.
> 那段时光, 是付出了很多努力,
> 却得不到结果的日子, 我们把它叫做扎根!--习近平

1.删除公共字符串
#### 题目描述：
输入两个字符串，从第一字符串中删除第二个字符串中所有的字符。例如，
输入”They are students.”和”aeiou”，则删除之后的第一个字符串
变成”Thy r stdnts.”

#### 输入描述：
每个测试输入包含2个字符串

#### 输出描述：
输出删除后的字符串

#### 题目解析：
本题描述很简单，题目描述很清楚，读题即可
#### 解题思路：
本题如果使用传统的暴力查找方式，如判断第一个串的字符是否在第二个串中，在再挪动字符删除这个字符
的方式，效率为O(N ^ 2)，效率太低，很难让人满意。

- 将第二个字符串的字符都映射到一个hashtable数组中，用来判断一个字符在这个字符串。
- 判断一个字符在第二个字符串，不要使用删除，这样效率太低，因为每次删除都伴随数据挪动。这里可

**以考虑使用将不在字符添加到一个新字符串，最后返回新新字符串.**



```
#include<iostream>
#include<string>
using namespace std;
int main(){
	// 注意这里不能使用cin接收，因为cin遇到空格就结束了。
	// oj中IO输入字符串最好使用getline。
	string str1, str2;
	//cin>>str1;
	//cin>>str2;
	getline(cin, str1);
	getline(cin, str2);
	// 使用哈希映射思想先str2统计字符出现的次数
	int hashtable[256] = { 0 };
	for (size_t i = 0; i < str2.size(); ++i){
		hashtable[str2[i]]++;
	}
	// 遍历str1，str1[i]映射hashtable对应位置为0，则表示这个字符在
	// str2中没有出现过，则将他+=到ret。注意这里最好不要str1.erases(i)
	// 因为边遍历，边erase，容易出错。
	string ret;
	for (size_t i = 0; i < str1.size(); ++i){
		if (hashtable[str1[i]] == 0){
			ret += str1[i];
		}
	}
	cout << ret << endl;
	return 0;
}
```



#### 解法二:

```
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string s1, s2, s3;
	getline(cin, s1);
	getline(cin, s2);
	int num[1000] = { 0 };
	for (decltype(s2.size()) i = 0; i < s2.size(); ++i)
	{
		num[s2[i]]++;
	}
	for (decltype(s1.size()) j = 0; j < s1.size(); ++j)
	{
		if (num[s1[j]] != 1)
			s3 += s1[j];
	}
	cout << s3 << endl;
	return 0;
}
```
#### 解法三:

#include <iostream>
#include <string>
using namespace std;

int main() {
	string str, del;
	getline(cin, str);
	getline(cin, del);

	for (int i = 0; i < del.length(); i++)
	for (int j = 0; j < str.length(); j++)
	if (del[i] == str[j])
		str.erase(j--, 1);

	cout << str;
}
#### 解法四:

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	string str;
	string st;

	getline(cin, str);
	getline(cin, st);

	for (int i = 0; i< st.size(); i++){
		int index;

		while ((index = str.find(st[i])) != -1){//查找第一次出现该字符的位置
			str.erase(index, 1);//从index位置开始删除一个字符
		}
	}
	cout << str << endl;
	return 0;
}

```



>我不奢望长生不死, 我只想趁我活着的时候认真生活!
2.组队竞赛--求所有队伍中水平值总和最大值
#### 题目描述
牛牛举办了一次编程比赛, 参加比赛的有3*n个选手, 每个选手都有一个水平值a_i.
现在要将这些选手进行组队, 一共组成n个队伍, 即每个队伍3人.牛牛发现队伍的
水平值等于该队伍队员中第二高水平值。
一个队伍三个队员的水平值分别是3, 3, 3.那么队伍的水平值是3
一个队伍三个队员的水平值分别是3, 2, 3.那么队伍的水平值是3
一个队伍三个队员的水平值分别是1, 5, 2.那么队伍的水平值是2
为了让比赛更有看点, 牛牛想安排队伍使所有队伍的水平值总和最大。

如样例所示 :
如果牛牛把6个队员划分到两个队伍
如果方案为 :
team1 : {1, 2, 5}, team2 : {5, 5, 8}, 这时候水平值总和为7.
而如果方案为 :
team1 : {2, 5, 8}, team2 : {1, 5, 5}, 这时候水平值总和为10.
没有比总和为10更大的方案, 所以输出10.

#### 输入描述
输入的第一行为一个正整数n(1 ≤ n ≤ 10 ^ 5)
 第二行包括3*n个整数a_i(1 ≤ a_i ≤ 10 ^ 9), 表示每个参赛选手的水平值.

#### 输出描述
输出一个整数表示所有队伍的水平值总和最大值.

#### 示例1
输入
2
5 2 8 5 1 5
输出
10

#### 题目解析：
队伍的水平值等于该队伍队员中第二高水平值，为了所有队伍的水平值总和最大的
解法，也就是说每个队伍的第二个值是尽可能大的值。所以实际值把最大值放到最
右边，最小是放到最左边。

#### 解题思路：
本题的主要思路是贪心算法，贪心算法其实很简单，就是每次选值时都选当前能看到
的局部最解忧，所以这里的贪心就是保证每组的第二个值取到能选择的最大值就可以，
我们每次尽量取最大，但是最大的数不可能是中位数，所以退而求其次，取 每组中
第二大的排序，然后取下标为3n - 2，3n - 4 ，3n - 4...n + 2，n位置的元素累加
即可，相当下标为[0, n - 1]的n个数做每组的最左边的数，剩下的2个数据两个为
一组，大的值做最右边的数，次大的做中间值，这里就是把这个次大的值加起来。
例如
1 2 3 4 5 6 7 8 9组队

最大的方案是：

1 8 9

2 6 7

3 4 5

即8 + 6 + 4 = 18。

 - 先进行排序;
-然后再把最大两个数和最小的一个数放在一组;
-最后就可以依次类推找出其中的最大水平值.

#### 程序代码
###### 解法一

```
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
	// IO型OJ可能会有多组测试用例，所以这里要持续接收输入多组测试用例。
	int n;
	while (cin >> n){
		long long sum = 0;//这里需要注意一下，如果将sum定义为int类型可能会超出int的存储范围
		vector<int> a;
		a.resize(3 * n);
		for (int i = 0; i < (3 * n); i++){
			cin >> a[i];
		}
		/*
		排序，然后取下标为3n - 2，3n - 4 ，3n - 4... n+2，n位置的元素累加即可，
		相当下标为[0,n-1]的n个数做每组的最左边的数，剩下的2个数据两个为一组，
		大的值做最右边的数，次大的做中间值，这里就是把这个次大的值加起来
		*/
		std::sort(a.begin(), a.end());           //对成员的成绩进行排序 
		for (int i = n; i <= 3 * n - 2; i += 2){
			sum += a[i];
		}
		cout << sum << endl;
	}
}
```

