// https://leetcode.cn/problems/find-all-anagrams-in-a-string/?envType=study-plan-v2&envId=top-100-liked
// 438. 找到字符串中所有字母异位词
// 已解答
// 中等
// 相关标签
// 相关企业
// 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
// 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。

// 示例 1:
// 输入: s = "cbaebabacd", p = "abc"
// 输出: [0,6]
// 解释:
// 起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
// 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。

//  示例 2:
// 输入: s = "abab", p = "ab"
// 输出: [0,1,2]
// 解释:
// 起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
// 起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
// 起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。

// 提示:
// 1 <= s.length, p.length <= 3 * 104
// s 和 p 仅包含小写字母



#include<iostream>
#include<vector>
#include<unordered_map>
#include<string>
#include<algorithm>
using namespace std;


class Solution {
public:
    vector<int> findAnagrams(string s, string p) {

    }
};




// 2024年7月25日
// 19点11分
// 比较复杂，不推荐
class Solution_M1 {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> result;
        if(s.size() < p.size()) return result;
        // 统计个数
        vector<int> set(26, INT_MIN);   // 每个字符的个数
        for(const char& ch : p) {
            int idx = ch - 'a';
            if(set[idx] == INT_MIN) set[idx] = 1;
            else set[idx]++;
        }
        // 滑动窗口
        for(int left=0, right=0; right < s.size(); right++) {
            int idx = s[right] - 'a';
            if(set[idx] == INT_MIN) {
                // 遇到没有的字符，需要清空窗口
                while(left < right) {
                    set[s[left] - 'a']++;   // 加回来
                    left++;
                }
                left++; // 定位到idx下一个字符
            }
            else if(set[idx] == 0) {
                // 遇到多一个 s[right] 字符，左边需要腾出一个 s[right]
                while(left < right && s[left] != s[right]) {
                    set[s[left] - 'a']++;
                    left++;
                }
                // set[s[left] - 'a']++;
                left++; // 定位到左侧 s[left] == s[right] 的下一个字符
            }
            else {
                // 遇到一个正常字符
                set[idx]--;
                // 总数满足要求，左边腾出一个
                if(right - left + 1 == p.size()) {
                    result.emplace_back(left);
                    set[s[left] - 'a']++;
                    left++;
                }
            }
        }
        return result;
    }
};



// 滑动窗口流程：多加上判断非法字符跳过
// 右边的字符加入hash表，while处理直到窗口满足条件，处理结果
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char,int> mp;
        for(const char & ch : p) {
            if(mp.find(ch) == mp.end()) {
                mp.insert({ch, 1});
            }
            else {
                mp[ch]++;
            }
        }
        // 滑动窗口
        vector<int> result;
        for(int left=0, right=0; right < s.size(); right++) {
            char ch = s[right];
            // 遇到非法字符，直接重开
            if(mp.find(ch) == mp.end()) {
                while(left < right) {
                    mp[s[left]]++;
                    left++;
                }
                left++; // 下一个
                continue;
            }
            // 加入窗口
            mp[ch]--;
            // 收缩窗口直到满足条件
            while(mp[ch] < 0) {
                mp[s[left]]++;
                left++;
            }
            // 处理结果
            if(right - left + 1 == p.size()) {
                result.push_back(left);
            }
        }
        return result;
    }
};