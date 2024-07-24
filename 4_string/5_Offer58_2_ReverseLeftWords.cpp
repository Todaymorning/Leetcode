#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 344.反转字符串 ，第一次讲到反转一个字符串应该怎么做，使用了双指针法。
// 541. 反转字符串II，这里开始给反转加上了一些条件，当需要固定规律一段一段去处理字符串的时候，要想想在在for循环的表达式上做做文章。
// 151.翻转字符串里的单词中，要对一句话里的单词顺序进行反转，发现先整体反转再局部反转 是一个很妙的思路。
// 最后再讲到本题，本题则是先局部反转再 整体反转。


// 不使用额外空间：
// 反转区间为前n的子串
// 反转区间为n到末尾的子串
// 反转整个字符串
// 时间复杂度O(n)，空间复杂度O(1)
string reverseLeftWords_D1(string s, int n)
{
	reverse(s.begin(), s.begin()+n);
	reverse(s.begin()+n, s.end());
	reverse(s.begin(), s.end());
	return s;
}


// 字符串切片
// 复杂度分析：
// 时间复杂度：O(N)
// 空间复杂度：O(N)
string reverseLeftWord_W1(string s, int n)
{
	if(0 == s.size())
		return s;
	string s1 = s.substr(0, n); // 第二参数为切片字符数
	string s2 = s.substr(n, s.size()-n);
	s = s2 + s1;
	return s;
}

// 字符串遍历
// 首先，n如果是str长度的倍数，那么最终目标串target是和str一样的，令left = n%len。
// 如果left = 0 ,那么直接返回原串，否则进行字符串遍历。
// target每个位置的字符为str[ (left+i)%str.size()] ,i代表当前位置

string reverseLeftWord_W2(string s, int n)
{
	
	int left = n%s.size();	// n 是否是 长度的整数倍，是则返回原字符串
	string result(s);
	if(left != 0)
	{
		int index = 0;
		for(int i=0; i<s.size(); i++)
		{
			index = (left+i)%s.size();
			result[i] = s[index];
		}
	}
	return result;
}






















