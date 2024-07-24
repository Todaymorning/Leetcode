// 题目：剑指 Offer 05. 替换空格
// 请实现一个函数，把字符串 s 中的每个空格替换成 "%20"。
// 示例 1： 输入：s = "We are happy."
// 输出："We%20are%20happy."

#include <iostream>
#include <string>
using namespace std;

// 双指针
// · 时间复杂度：O(n)
// · 空间复杂度：O(n)
string replaceSpace_D1(string & s)
{
    int count = 0;  // 统计
    int oldSize = s.size();
    for(char & ch:s)    // 统计空格个数
    {
        if(ch == ' ')
            count++;
    }
    s.resize(s.size() + 2 * count); // 扩充字符串大小
    int newSize = s.size();
    for(int i=oldSize-1, j=newSize-1; i>=0; i--, j--)   //必须有等于号
    {
        cout << "# " << i << endl;
        if(s[i]!=' ')
            s[j] = s[i];
        else
        {
            s[j] = '0';
            s[--j] = '2';
            s[--j] = '%';
        }
    }
    return s;
}