// 383. 赎金信
// 给定一个赎金信 (ransom) 字符串和一个杂志 (magazine) 字符串，
// 判断第一个字符串 ransom 能不能由第二个字符串 magazines 里面的字符构成。
// 如果可以构成，返回 true ；否则返回 false。
// (题目说明：为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。
// 杂志字符串中的每个字符只能在赎金信字符串中使用一次。)
// 你可以假设两个字符串均只含有小写字母。

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 字符统计，用数组当 hash 表
// . 如果字符串 magazine 的长度小于字符串 ransomNote 的长度,直接返回false.
// . 首先统计 magazine 中每个英文字母 a 的次数 cnt[a],再遍历统计 ransomNote 中每个英
// 文字母的次数,如果发现 ransomNote 中存在某个英文字母c的统计次数大于 magazine
// 中该字母统计次数cnt[c],则此时我们直接返回 false.
bool canConstruct_G1(string ransomNote, string magazine)
{
    if(ransomNote.size() > magazine.size())
        return false;
    int count[26] = {0};  // vector<int> count(26, 0);
    for(char & ch : magazine)
        count[ch-'a']++;
    for(char & ch : ransomNote)
    {
        count[ch-'a']--;
        if(count[ch-'a'] < 0)
            return false;
    }
    return true;
}

// 暴力解法
bool canConstruct_D1(string ransomNote, string magazine)
{
    int rNum = ransomNote.size();
    int mNum = magazine.size();
    if(rNum > mNum)
        return false;
    for(int i=0; i<mNum; i++)   // 拿着 magazine中的字符往 ransomNode上贴
    {
        for(int j=0; j<rNum; j++)
        {
            if(magazine[i] == ransomNote[j])
            {
                ransomNote.erase(ransomNote.begin() + j);
                rNum--;
                break;
            }
        }
    }
    if(ransomNote.size() == 0)
        return true;
    return false;
}