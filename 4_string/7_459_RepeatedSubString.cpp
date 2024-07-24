// 459.重复的子字符串
// 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。给定的字符串只含有小写英文字母，并且长度不超10000。
// 示例 1:
// 输入: "abab"
// 输出: True
// 解释: 可由子字符串 "ab" 重复两次构成。

// 示例 2:
// 输入: "aba"
// 输出: False

// 示例 3:
// 输入: "abcabcabcabc"
// 输出: True
// 解释: 可由子字符串 "abc" 重复四次构成。 (或者子字符串 "abcabc" 重复两次构成。)



# include <iostream>
# include <string>
# include <cstdio>
using std::string;

// 方法一：枚举 / 暴力
// 字符串s是子字符串s'的倍数
// 字符串长度n是子字符串长度n'的倍数
// 从1到n/2枚举即可（子字符串至少重复两遍）
//
// 复杂度分析：
// time  O(n^2)
// space O(1)

class Solution_G1
{
public:
    bool repeatedSubstringPatten(string s)
    {
        int n = s.size();
        for(int i=1; i * 2 <= n; ++i)	// i从1开始:[j-i]=0; 子字符串至少重复两次:n/2
        {
            if(n % i == 0)				// 子字符串是字符串的倍数
            {
                bool match = true;
                for(int j=i; j<n; ++j)	// 以i为间距从前往后比较（一直到结尾）
                {
                    if(s[j] != s[j-i])
                    {
                        match = false;
                        break;
                    }
                }
                if(match == true)
                    return true;
                // for(int j=0; j<n-i; ++j)
                // {
                // 	if(s[j] != s[j+i])
                // 	{
                // 		match = false;
                // 		break;
                // 	}
                // }
            }
        }
        return false;	
    }
};




// 方法二：字符串匹配
// 如果字符串s重复，则 s+s 的中间会出现s
class Solution_G2
{
public:
    bool repeatedSubstringPatten(string s)
    {
        return (s+s).find(s, 1) != s.size();	// 索引从1开始，是在中间找到的；索引不是n，不是结尾的s
    }
};