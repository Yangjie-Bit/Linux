1.统计回文
**题目描述**
统计回文 | 时间限制：1秒 | 内存限制：32768K
“回文串”是一个正读和反读都一样的字符串，比如“level”或者“noon”等等
就是回文串。花花非常喜欢这种拥有对称美的回文串，生日的时候她得到两个礼物
分别是字符串A和字符串B。现在她非常好奇有没有办法将字符 串B插入字符串A使
产生的字符串是一个回文串。你接受花花的请求，帮助她寻找有多少种插入办法
可以使新 串是一个回文串。如果字符串B插入的位置不同就考虑为不一样的办法。
例如：
A = “aba”，B = “b”。这里有4种把B插入A的办法：
* 在A的第一个字母之前: "baba" 不是回文
* 在第一个字母‘a’之后 : "abba" 是回文
* 在字母‘b’之后 : "abba" 是回文
* 在第二个字母'a'之后 "abab" 不是回文
所以满足条件的答案为2

**输入描述**
每组输入数据共两行。第一行为字符串A 第二行为字符串B 字符串长度均小于100
且只包含小写字母 输出描述： 输出一个数字，表示把字符串B插入字符串A之后
构成一个回文串的方法数

**示例1: 输入 aba b 输出 2 * *

**题目解析**
回文串也就是前后对称的字符串。本题是判断是否是回文串的变形题。字符串本身
不一定是回文，把第二个字符串插入进去看是否是回文。

**解题思路**
本题使用暴力求解方式计算即可，遍历str1，将str2 insert进入str1的每个位置，
判断是否是回文，是就 ++count；需要注意的是这里不能 str1.insert(i, str2)，
这样的话str1改变了，判断下一个位置就不对了。所 以每次使用str1拷贝构造一个
str，然后str.insert(i, str2)，再判断

#include<iostream> 
#include<string> 
using namespace std;
// 判断是否是回文 
bool IsCircleText(const string& s) {
	size_t begin = 0;
	size_t end = s.size() - 1;
	while (begin < end){
		if (s[begin] != s[end]){
			return false;
		}
		++begin;
		--end;
	}
	return true;
}

int main() {
	std::string str1, str2;
	getline(cin, str1);
	getline(cin, str2);
	size_t count = 0;
	for (size_t i = 0; i <= str1.size(); ++i){
		// 将字符串2插入到字符串1的每个位置，再判断是否是回文        
		string str = str1;
		str.insert(i, str2);
		if (IsCircleText(str)){
			++count;
		}
	}
	cout << count << endl;
	return 0;
}

2.连续最大和
**题目解析**
连续最大和 | 时间限制：1秒 | 内存限制：32768K 一个数组有 N 个元素，求连续
子数组的最大和。 例如：[-1, 2, 1]，和最大的连续子数组为[2, 1]，其和为3

**输入描述**
输入为两行。 第一行一个整数n(1 <= n <= 100000)，表示一共有n个元素 第二行
为n个数，即每个元素, 每个 整数都在32位int范围内。以空格分隔。

**输出描述**
所有连续子数组中和最大的值。 示例1 : 输入 3 - 1 2 1 输出 3

**题目解析**
本题是一个经典的动规问题，简称dp问题非，就是求哪一段的子数组的和最大。

**解题思路**
假设sum[i - 1]是以数组中第nums[i - 1]为最后一个元素的一段子数组最大和， 
sum[i]是以数组中第nums[i]为最后一个元素的一段子数组最大和，那么sum[i] 
= max(sum[i - 1], 0) + nums[i]，理解了这个，下面代码中用sum1表示
sum[i - 1]，sum2表示 sum[i]，如果计算出更大的子数组和则保存到result中。
如果sum[i]，及sum2都小于0了，则置为0，因为他 加上数组下一个数，不会计算
出更大的子数组和。

#include <iostream> 
#include<vector> 
using namespace std;

int main() {
	int size;
	cin >> size;
	vector<int> nums(size);
	for (size_t i = 0; i < size; ++i){
		cin >> nums[i];
	}
	int result = nums[0];
	int sum1 = 0, sum2 = 0;
	for (int i = 0; i < nums.size(); i++){
		// 计算到num[i]的子数组的最大和       
		sum2 = sum1 >= 0 ? sum1 + nums[i] : nums[i];
		if (sum2 > result){
			result = sum2;
		}
		if (sum2 < 0){
			sum2 = 0;
		}
		sum1 = sum2;
	}
	cout << result << endl;
	return 0;
}
