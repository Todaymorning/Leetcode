// https://leetcode.cn/problems/remove-duplicate-letters
// 316. 去除重复字母
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 提示
// 给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 返回结果的
// 字典序
// 最小（要求不能打乱其他字符的相对位置）。

// 示例 1：
// 输入：s = "bcabc"
// 输出："abc"

// 示例 2：
// 输入：s = "cbacdcbc"
// 输出："acdb"

// 提示：
// 1 <= s.length <= 10^4
// s 由小写英文字母组成
// 注意：该题与 1081 https://leetcode-cn.com/problems/smallest-subsequence-of-distinct-characters 相同


#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>
using std::unordered_map;
using std::unordered_set;
using std::string;
using std::vector;



class Solution {
public:
    string removeDuplicateLetters(string s) {

    }
};


// 2024年4月27日
// 16:12
// 字典序不理解
// 单调栈

class Solution {
public:
    string removeDuplicateLetters(string s) {
        string stk; // 字典
        vector<int> counts(26, 0);      // 统计字符个数
        vector<int> used(26, false);    // 字典中是否有该字符
        // 统计每个字符的个数
        for(int i=0; i<s.size(); i++) {
            counts[s[i] - 'a']++;
        }
        for(auto ch : s) {
            // 每遍历一个字符，后面剩余该字符的个数减一
            counts[ch - 'a']--;
            // 字典中没有该字符
            if(!used[ch - 'a']) {
                // 栈顶元素比当前字符大，且字符串后面还有栈顶元素，为了减小字典序数，从字典中移除
                while(!stk.empty() && ch < stk.back() && counts[stk.back() - 'a']) {
                    used[stk.back() - 'a'] = false; // 从字典中移除
                    stk.pop_back();
                }
                stk.push_back(ch);
                used[ch - 'a'] = true;
            }
        }
        return stk;
    }
};



// 2024年5月8日
// 15:52--15:56
// 可以有多种字符
class Solution {
public:
    string removeDuplicateLetters(string s) {
        unordered_map<char, int> mp;
        unordered_set<char> used;
        string stk;
        for(auto& ch : s) {
            mp[ch]++;
        }
        for(auto& ch : s) {
            mp[ch]--;
            if(used.find(ch) == used.end()) {
                while(!stk.empty() && stk.back() > ch && mp[stk.back()] > 0) {
                    used.erase(stk.back());
                    stk.pop_back();
                }
                stk.push_back(ch);
                used.insert(ch);
            }
        }
        return stk;
    }
};