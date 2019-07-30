> 给自己一个放松的理由, 别让太多承载负重了心灵,
> 给自己一个释然的方式, 别让太多琐碎凌乱了平静;
> 以风的执念飞翔, 以雨的心胸求索, 在平淡中快乐, 在精彩中淡然!

**题目描述**
两种排序方法 | 时间限制：1秒 | 内存限制：32768K 考拉有n个字符串字符串，
任意两个字符串长度都是不同的。

考拉最近学习到有两种字符串的排序方法： 
1.根 据字符串的字典序排序。例如：
"car" < "carriage" < "cats" < "doggies < "koala"

2.根据字符串的长度排序。例如：
"car" < "cats" < "koala" < "doggies" < "carriage"

考拉想知道自己的这些字符串排列顺序是否满足这两种排序方法，考拉要忙着吃
树叶，所以需要你来帮忙验证。

**输入描述**
输入第一行为字符串个数n(n ≤ 100) 接下来的n行, 每行一个字符串, 字符串
长度均小于100，均由小写字母组成

**输出描述**
如果这些字符串是根据字典序排列而不是根据长度排列输出"lexicographically",
如果根据长度排列而不是字典序排列输出"lengths";
如果两种方式都符合输出"both"，否则输出"none"

**示例**
输入 3 a aa bbb
输出 both

**解题思路**
思路很简单，将接受的字符串都放到vector容器中，利用string的operator >= 
运算符重载来按ascii比较字符 串，利用string的size来比较字符串的长度

#include<iostream> 
#include<vector> 
#include<string> 
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<string> v;
	v.resize(n);
	for (auto& str : v){
		cin >> str;
	}
	bool lenSym = true, lexSym = true;

	// 这里要注意从i=1开始遍历，前后比较，比较长度 
	for (size_t i = 1; i < v.size(); ++i) {
		if (v[i - 1].size() >= v[i].size()){
			lenSym = false;
			break;
		}
	}

	//比较ASCII码 
	for (size_t i = 1; i < v.size(); ++i){
		if (v[i - 1] >= v[i]){
			lexSym = false;
			break;
		}
	}
	if (lenSym&& lexSym){
		cout << "both" << endl;
	}
	else if (!lenSym && lexSym){
		cout << "lexicographically" << endl;
	}
	else if (lenSym && !lexSym){
		cout << "lengths" << endl;
	}
	else if (!lenSym&&!lexSym){
		cout << "none" << endl;
	}
	return 0;
}


> 不要急着让生活给与你所有的答案.
> 有时候, 你要拿出耐心等待.
> 即便你向空谷喊话, 也要等一会儿, 才会听见绵长的回音.
> 也就是说, 生活总会给你答案, 但不会马上把一切都告诉你!--马德

**题目描述**
求最小公倍数 | 时间限制：1秒 | 内存限制：32768K 正整数A和正整数B 的最小
公倍数是指 能被A和B整除的最小的正整数值，设计一个算法，求输入A和B的最小 
公倍数。

**输入描述**
输入两个正整数A和B。

**输出描述**
输出A和B的最小公倍数。

**解题思路**
最小公倍数 = 两数之积除以最大公约数，这里使用碾转相除法进行最大公约数的
求解：即a与b的最大公约数 可以转化为a、b之间的余数为两者之间最小的数之间
的公约数。所以对于输入的两个数进行连续求余，直到余数为0，求余的分母即为
结果。


#include<iostream> 
using namespace std;
int gcd(int a, int b){
	int r;
	while (r = a%b){
		a = b;
		b = r;
	}
	return b;
}


int main(){
	int a, b;
	while (cin >> a >> b){
		cout << a*b / gcd(a, b) << endl;
	}
	return 0;
}


