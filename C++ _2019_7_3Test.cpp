1.字符串中找出连续最长的数字串
**题目描述**
字符串中找出连续最长的数字串 | 时间限制：1秒 | 内存限制：32768K
读入一个字符串str，输出字符串str中的连续最长的数字串 .

**输入描述**
测试输入包含1个测试用例，一个字符串str，长度不超过255。 

**输出描述**
在一行内输出str中里连续最长的数字串。

示例1 : 输入 abcd12345ed125ss123456789
		输出 123456789

**解题思路**
遍历字符串，使用cur去记录连续的数字串，如果遇到不是数字字符，则表示一个
连续的数字串结束了，则将 数字串跟之前的数字串比较，如果更长，则更新更长
的数字串更新到res.

**程序代码**

#include<iostream>
#include<string> 
	  using namespace std;
int main(){
	string str, res, cur;
	cin >> str;
	for (int i = 0; i <= str.length(); i++){
		// 数字+=到cur        
		if (str[i] >= '0' && str[i] <= '9'){
			cur += str[i];
		}
		else{
			// 找出更长的字符串，则更新字符串            
			if (res.size() < cur.size()){
				res = cur;
			}
			else{
				cur.clear();
			}
		}
	}
	cout << res;
	return 0;
}

2.数组中出现次数超过一半的数字
**题目描述**
数组中出现次数超过一半的数字 | 时间限制：1秒 | 内存限制：32768K | 
语言限制：[Javascript_V8, Python, C++, Javascript, Php, C#, Java]
数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入
一个长度为9的数组{ 1, 2, 3, 2, 2, 2, 5, 4, 2 }。由于数字2在数组中出现
了5次，超过数组长度的一半，因此输出2。如果不存在则输出 0。

**题目解析**
本题题意很简单，需要找出超过一半的那个数字。

**解题思路**

**思路一**
数组排序后，如果符合条件的数存在，则一定是数组中间那个数。这种方法虽然
容易理解，但由于 涉及到快排sort，其时间复杂度为O(NlogN)并非最优；

**解法一**

class Solution{
public:
	int MoreThanHalfNum_Solution(vector<int> numbers){
		// 因为用到了sort，时间复杂度O(NlogN)，并非最优        
		if (numbers.empty()){
			return 0;
		}
		sort(numbers.begin(), numbers.end());
		// 排序，取数组中间那个数        
		int middle = numbers[numbers.size() / 2];
		int count = 0;
		// 出现次数        
		for (int i = 0; i<numbers.size(); ++i){
			if (numbers[i] == middle){
				++count;
			}
		}
		return (count>numbers.size() / 2) ? middle : 0;
	}
};

**解题思路2**
如果有符合条件的数字，则它出现的次数比其他所有数字出现的次数和还要多。
在遍历数组时保存两个值： 一是数组中一个数字，一是次数。遍历下一个数
字时，若它与之前保存的数字相同，则次数加1，否则次数减 1；若次数为0，
则保存下一个数字，并将次数置为1。遍历结束后，所保存的数字即为所求。
然后再判断它 是否符合条件即可.

**解法二**

class Solution {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers){
		if (numbers.empty()){
			return 0;
		}
		// 遍历每个元素，并记录次数；若与前一个元素相同，则次数加1，否则次数减1         
		int result = numbers[0];
		int times = 1; // 次数                 
		for (int i = 1; i<numbers.size(); ++i){
			if (times == 0){
				// 更新result的值为当前元素，并置次数为1                
				result = numbers[i];
				times = 1;
			}
			else if (numbers[i] == result){
				// 相同则加1
				++times;
			}
			else
			{
				// 不同则减1
				--times;
			}
		}
		// 判断result是否符合条件，即出现次数大于数组长度的一半        
		times = 0;
		for (int i = 0; i<numbers.size(); ++i){
			if (numbers[i] == result){
				++times;
			}
		}
		return (times > numbers.size() / 2) ? result : 0;
	}
};
