// // https://leetcode.cn/problems/longest-substring-without-repeating-characters
// 3. 无重复字符的最长子串
// labuladong 题解


#include<iostream>
#include<string>
#include<unordered_map>
using std::unordered_map;
using std::string;

class Solution {
public:
    int lengthOfLongestSubstring (string s) {
        // 2024 年 5 月 4 日，19 点 32 分
        if (s.size () == 0) return 0;
        unordered_map<char, int> mp;
        int res = 0;
        for (int left = 0 , right = 0; right<s.size (); right++) {
            char ch = s [right];
            if (mp.find (ch) == mp.end ()) {
                mp.insert ({ch, 1});
            }
            else {
                mp [ch]++;
            }
            // 保证窗口内无重复
            while (mp [ch] > 1) {   // mp.count(ch) > 1 错误
                mp [s [left]]--;
                left++;
            }
            int temp = right - left + 1;
            if (temp > res) {
                res = temp;
            }
        }
        return res;
    }
};