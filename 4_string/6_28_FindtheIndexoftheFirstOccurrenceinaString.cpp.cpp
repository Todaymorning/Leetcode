// 28. 实现 strStr()
// 给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。
// 示例 1: 输入: haystack = "hello", needle = "ll" 输出: 2
// 示例 2: 输入: haystack = "aaaaa", needle = "bba" 输出: -1
// 说明: 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。 对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及 Java的 indexOf() 定义相符。

#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;

// 暴力匹配
// 时间复杂度：O((m-n)*n), 空间复杂度：O(1)
class Solution_G1
{
public:
	int strStr(string haystack, string needle)
	{
		int hay_size = haystack.size();	// n
		int nee_size = needle.size();	// m
		if(nee_size == 0)
			return 0;
		if(hay_size >= nee_size)	// 前提
		{
			for(int i=0; i <= hay_size+nee_size; i++)	// 用i遍历hay中所有起点
			{
				int j = 0;	// 用j索引needle并进行比较
				while((j<nee_size) && (haystack[i+j] == needle[j])) j++;
				if(j == nee_size)
					return i;
			}
		}
		return -1;
	}
};


// KMP
int strStr_G2(string haystack, string needle)
{
	int n = haystack.size();
	int m = needle.size();
	if(m==0)	return 0;
	vector<int> pi(m, 0);
	for(int i=1,j=0; i<m; i++)
	{
		while(j>0 && needle[i]!=needle[j])
			j = pi[j-1];
		if(needle[i] == needle[j])
			j++;
		pi[i] = j;
	}
	for(int i=0,j=0; i<n; i++)
	{
		while(j>0 && haystack[i]!=needle[j])
			j = pi[j-1];
		if(haystack[i]==needle[j])
			j++;
		if(j == m)
			return (i-m+1);
	}
	return -1;
};



// KMP: 最大公共前后缀
// 前缀表减一，方便索引
// 时间复杂度：O(n) 空间复杂度：O(m)
void getNext_D1(int * next, const string & s)
{
	int j = -1;
	next[0] = j; // 第一个不用计算
	for(int i=1; i<s.size(); i++)	// i 从 1 开始
	{
		while(j>=0 && s[i]!=s[j+1])	// 前后缀不同，向前回退
			j = next[j];
		if(s[i] == s[j+1])	// 前后缀相同，数目加一
			j++;
		next[i] = j;	// 当前位置前缀长度
	} 
}
int strStr_D1(string haystack, string needle)
{
	int hay_size = haystack.size();
	int nee_size = needle.size();
	if(nee_size == 0)	return 0;
	if(hay_size>=nee_size)
	{
		int next[nee_size];
		getNext_D1(next, needle);
		int j=-1;
		for(int i=0; i<hay_size; i++)
		{
			while(j>=0 && haystack[i]!=needle[j+1])
				j = next[j]; // 不匹配则回退
			if(haystack[i]==needle[j+1])
				j++;
			if(j==(nee_size-1))
				return (i-nee_size+1);
		}
	}
	return -1;
}

// 前缀表不减一
void getNext_D2(int * next, const string & s)
{
	int j=0;
	next[0]=j;
	for(int i=1; i<s.size(); i++)
	{
		while(j>0 && s[i] != s[j])
			j = next[j-1];
		if(s[i]==s[j])
			j++;
		next[i] = j;
	}
}

int strStr(string haystack, string needle)
{
	if(needle.size() == 0)	return 0;
	int next[needle.size()];
	getNext_D2(next, needle);
	int j=0;
	for(int i=0; i<haystack.size(); i++)
	{
		while(j>0 && haystack[i]!=needle[j])
			j = next[j-1];
		if(haystack[i] == needle[j])
			j++;
		if(j == needle.size())
			return (i-needle.size()+1);
	}
	return -1;
}