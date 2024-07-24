// 242. 有效的字母异位词
// 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
// 示例 1: 输入: s = "anagram", t = "nagaram" 输出: true
// 示例 2: 输入: s = "rat", t = "car" 输出: false
// 说明: 你可以假设字符串只包含小写字母。

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 排序后比较
// 复杂度分析
// . 时间复杂度: O(nlogn),其中 n为 s的长度.
//   排序的时间复杂度为 O(nlogn),比较两个字符串是否相等时间复杂度为 O(n),
//   因此总体时间复杂度为O(n logn +n) = O(n logn).
// . 空间复杂度:O(logn).排序需要O(logn)的空间复杂度.

bool isAnagram_G1(string s, string t)
{
    if(s.length() != t.length())
        return false;
    sort(s.begin(), s.end());
    sort(t.begin(), t.end());
    return s==t;
}

// 哈希表
// 构建数组统计字母
// 复杂度分析
// 时间复杂度:O(n),其中n为s的长度.
// 空间复杂度:O(S),其中S为字符集大小,此处S=26.
bool isAnagrm_G2(string s, string t)
{
    if(s.length() != t.length())
        return false;
    int table[26] = {0};
    for(int i=0; i<s.size(); i++)
    {
        table[s[i]-'a']++;
        table[t[i]-'a']--;
    }
    for(int i=0; i<26; i++)
        if(table[i] != 0)
            return false;
    return true;
}