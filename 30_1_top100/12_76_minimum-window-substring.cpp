// https://leetcode.cn/problems/minimum-window-substring
// 76. 最小覆盖子串
// labuladong 题解
// 滑动窗口 + 两个hash表

// 2024年7月28日
// 忘记咋写


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

// 2024年7月28日
// 9:11--9:22(错误)--9:34
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> needs, window;
        for(auto ch : t) needs[ch]++;
        int start = 0;
        int min_len = INT_MAX;
        int count=0;
        for(int left=0, right=0; right < s.size(); right++) {
            // 加入窗口，只有需要的字符才进行处理
            char ch = s[right];
            if(needs.count(ch)) {
                window[ch]++;
                // 只有相等时 count++，超过不需要自增
                if(window[ch] == needs[ch]) count++;    // ***
            }
            // 收缩窗口，直到不满足条件
            while(count == needs.size()) {  // ***
                char l = s[left];
                // 更新结果，不论左边是啥字符，现在窗口满足条件，都更新结果
                int cur = right - left + 1;
                if(cur < min_len) {
                    start = left;
                    min_len = cur;
                }
                // 左边收缩，只有需要的字符才进行处理
                left++;
                if(needs.count(l)) {
                    if(window[l] == needs[l]) count--;
                    window[l]--;
                }
            }
        }
        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};