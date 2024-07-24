// 151. 翻转字符串里的单词
// 给定一个字符串，逐个翻转字符串中的每个单词。
// 示例 1：
// 输入: "the sky is blue"
// 输出: "blue is sky the"
// 示例 2：
// 输入: " hello world!  "
// 输出: "world! hello"
// 解释：输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
// 示例 3：
// 输入: "a good   example"
// 输出: "example good a"
// 解释：如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。

#include <iostream>
#include <string>
using namespace std;


// 扩展知识，移除多余空格
//-----------------------------------------------------------------------------
// 使用 erase() 移除多余空格
// 时间复杂度O(n^2)
void removeExtraSpaces_1(string & s)
{
    // 连续空格只保留一个
    for(int i=s.size()-1; i>0; i--) // 从后往前删，可以稍微减少一点元素移动的次数
    {
        if(s[i]==s[i-1] && s[i]==' ')
            s.erase(s.begin()+i);
    }
    // 删除字符串后面的空格
    while(s.size()>0 && s[s.size()-1] == ' ')  // 防止全是空格，而删过头
        s.erase(s.begin() + s.size()-1);
    // 删除字符串前面的空格
    while(s.size()>0 && s[0] == ' ')
        s.erase(s.begin());
}

// 使用双指针移除多余空格
void removeExtraSpaces_2(string & s)
{
    int slow = 0;
    int fast = 0;
    while(s.size()>0 && fast<s.size() && s[fast]==' ')  // 移除字符串前面的字符
        fast++;
    for( ; fast<s.size(); fast++)
    {
        // 去除重复空格 (中间及结尾)
        if(fast>1 && s[fast]==s[fast-1] && s[fast]==' ') // fast>1 防止越界访问
            continue;
        else
            s[slow++] = s[fast];    // 移动单词及单词间空格
        if(slow>1 && s[slow-1]==' ')    // 结尾是否有空格
            s.resize(slow-1);
        else
            s.resize(slow);
    }
}

// 使用双指针移除多余元素，去除所有空格并在相邻单词间添加空格
void removeExtraSpaces_3(string & s)
{
    int slow = 0;
    for(int fast=0; fast<s.size(); fast++)
    {
        if(s[fast]!=' ')   // 遇到非空格就处理
        {
            // 以多个空格和后面的一个单词为处理单元
            if(slow!=0) // 只有在中间遇到空格的时候才需要
                s[slow++] = ' ';
            while(fast<s.size() && s[fast]!=' ')    // 在下一次遇到空格之前复制单词
                s[slow++] = s[fast++];
        }
    }
    s.resize(slow);
}


class Solution {
public:
    // 单词反转
    void reverse(string & s, int start, int end)
    {
        for(int i=start, j=end; i<j; i++, j--)
        {
            // swap(s[i], s[j]);
            s[i] ^= s[j];
            s[j] ^= s[i];
            s[i] ^= s[j];
        }
    }
    // 删除多余空格
    void removeExtraSpaces(string & s)
    {
        int slow = 0;
        int fast = 0;
        for( ; fast<s.size(); fast++)
        {
            if(s[fast] != ' ')
            {
                if(slow!=0)
                    s[slow++] = ' ';
                while(fast<s.size() && s[fast] != ' ')
                    s[slow++] = s[fast++];
            }
        }
        s.resize(slow);
    }
    string reverseWords(string s)
    {
        removeExtraSpaces(s);   // 去除多余空格
        reverse(s, 0, s.size()-1);
        int start = 0;
        for(int i=0; i<=s.size(); ++i)
        {
            if(i==s.size() || s[i]==' ')
            {
                reverse(s, start, i-1);
                start = i+1;
            }
        }
        return s;
    }
}
