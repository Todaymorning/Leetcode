// https://leetcode.cn/problems/minimum-window-substring
// 76. 最小覆盖子串
// labuladong 题解
// 思路
// 困难
// 相关标签
// 相关企业
// 提示
// 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

// 注意：
// 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
// 如果 s 中存在这样的子串，我们保证它是唯一的答案。

// 示例 1：
// 输入：s = "ADOBECODEBANC", t = "ABC"
// 输出："BANC"
// 解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。

// 示例 2：
// 输入：s = "a", t = "a"
// 输出："a"
// 解释：整个字符串 s 是最小覆盖子串。

// 示例 3:
// 输入: s = "a", t = "aa"
// 输出: ""
// 解释: t 中两个字符 'a' 均应包含在 s 的子串中，
// 因此没有符合条件的子字符串，返回空字符串。

// 提示：
// m == s.length
// n == t.length
// 1 <= m, n <= 10^5
// s 和 t 由英文字母组成

// 进阶：你能设计一个在 o(m+n) 时间内解决此问题的算法吗？



#include<iostream>
#include<string>
#include<unordered_map>
using std::unordered_map;
using std::string;


class Solution {
public:
    string minWindow(string s, string t) {

    }
};


// 2024年4月29日
//16:54--17:16--错误-17点35分
#if 0
class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        // 大小不满足
        if(m < n) return "";
        unordered_map<char, int> smap;
        unordered_map<char, int> tmap;
        for(auto & ch : s) {
            if(smap.find(ch) == smap.end()) {
                smap.insert({ch, 1});
            }
            else {
                smap[ch]++;
            }
        }
        for(auto & ch : t) {    // 写成了 s
            if(tmap.find(ch) == tmap.end()) {
                tmap.insert({ch, 1});
            }
            else {
                tmap[ch]++;
            }
        }
        // 字符种类不满足
        if(smap.size() < tmap.size()) return "";
        // 某一种类个数不满足
        for(auto & temp : tmap) {
            if(smap.find(temp.first) == smap.end()) return "";
            if(temp.second > smap[temp.first]) return "";
        }
        smap.clear();
        int left, right;
        for(left = 0, right = 0; right < m; right++) {
            char ch = s[right];
            if(smap.find(ch) == smap.end()) {
                smap.insert({ch, 1});
            }
            else {
                smap[ch]++;
            }
            // 需要左侧字符且该字符较多
            while(left < right && tmap.find(s[left]) != tmap.end() && tmap[s[left]] < smap[s[left]]) {
                smap[s[left]]--;
                left++;
            }
            // 不需要左侧字符
            while(left < right && tmap.find(s[left]) == tmap.end()) {
                smap[s[left]]--;
                left++;
            }
        }

        // 不需要右侧字符
        while(left < right && tmap.find(s[right]) == tmap.end()) {
            smap[s[right]]--;
            right--;
        }

        // 某一种类个数不满足
        for(auto & temp : tmap) {
            if(smap.find(temp.first) == smap.end()) return "";
            if(temp.second > smap[temp.first]) return "";
        }

        return s.substr(left, right + 1);
    }
};
#endif



// 2024年4月29日
// 18:30--19:07
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        for(auto & ch : t) need[ch]++;  // 没有时自动初始化
        int left, right;
        int count = 0;  // 统计窗口中有几种有效字符 (种类和数量都满足)
        int start = 0, min_len = INT_MAX;
        for(left=0, right=0; right<s.size(); right++) {
            // 将 right 放入窗口
            char ch = s[right];     // ***
            // 右侧加入有效字符时更新窗口状态
            // 只关注 need 中需要的数据，即窗口状态只和需要的字符有关
            if(need.count(ch)) {
                window[ch]++;
                if(window[ch] == need[ch]) count++; // 该种字符的数量满足
            }
            // 种类足够，才收缩
            // 窗口满足条件后才开始尝试缩小窗口，直到不满足条件
            // 窗口不满足条件不用管
            while(count == need.size()) {   // ***
                // 更新结果
                if(right - left + 1 < min_len) {
                    start = left;
                    min_len = right - left + 1;
                }
                // 左移窗口
                char d = s[left];
                left++;
                // 左侧减少有效字符时更新窗口状态
                if(need.count(d)) {
                    if(window[d] == need[d]) count--;
                    window[d]--;
                }
            }
        }
        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};