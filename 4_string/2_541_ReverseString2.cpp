// 给定一个字符串 s 和一个整数 k，从字符串开头算起, 
// 每计数至 2k 个字符，就反转这 2k 个字符中的前 k 个字符。
// 如果剩余字符少于 k 个，则将剩余字符全部反转。
// 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 调用库函数 reverse
string reverseStr_D1(string s, int k)
{
	for(int i=0; i<s.size(); i+=(2*k))	// 每 2k 进行判断
	{
		// 每隔 2k 的前 k 进行反转，
		// 剩余字符大于等于 k 小于 2k ,反转前k字符
		if(i+k <= s.size())
			reverse(s.begin()+i, s.begin()+i+k);
		else { // 剩余字符小于 k
			reverse(s.begin()+i, s.end());
		}
	}
	return s;
}

// 自己实现 reverse, 	交换[start, end]
void myReverse(string & s, int start, int end)
{
	for(int i=start, j=end; i<j; i++, j--)
	{
		// swap(s[i], s[j]);
		s[i] ^= s[j];
		s[j] ^= s[i];
		s[i] ^= s[j];
	}
}

string reverseStr_D2(string s, int k)
{
	for(int i=0; i<s.size(); i+=(2*k))
	{
		if(i+k<=s.size())
			myReverse(s, i, i+k-1);
		else {
			myReverse(s, i, s.size()-1);
		}
	}
	return s;
}


// 另一种思路，使用 while 循环
string reverseStr_D3(string s, int k)
{
	int n=s.size(), pos=0;
	while(pos<n)
	{
		if(pos+k<n)
			reverse(s.begin()+pos, s.begin()+pos+k);
		else {
			reverse(s.begin()+pos, s.end());
		}
		pos += (2*k);
	}
	return s;
}

