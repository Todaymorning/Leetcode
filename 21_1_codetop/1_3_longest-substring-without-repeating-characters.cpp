// // https://leetcode.cn/problems/longest-substring-without-repeating-characters
// 3. 无重复字符的最长子串
// labuladong 题解
// 思路
// 中等
// 相关标签
// 相关企业
// 给定一个字符串 s ，请你找出其中不含有重复字符的 最长
// 子串
//  的长度。

// 示例 1:
// 输入: s = "abcabcbb"
// 输出: 3 
// 解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。

// 示例 2:
// 输入: s = "bbbbb"
// 输出: 1
// 解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

// 示例 3:
// 输入: s = "pwwkew"
// 输出: 3
// 解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
//      请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
 

// 提示：
// 0 <= s.length <= 5 * 10^4
// s 由英文字母、数字、符号和空格组成


#include<iostream>
#include<string>
#include<unordered_map>
using std::unordered_map;
using std::string;

// 10:17--10:25--10:27
// 滑动窗口
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        unordered_map<char, int> smap;
        for(int left=0, right=0; right<s.size(); right++) {
            char ch = s[right];
            if(smap.find(ch) != smap.end()) {
                smap[ch]++;
            }
            else {
                smap.insert({ch, 1});
            }
            while(smap[ch] > 1) {
                smap[s[left]]--;    // ***
                left++;
            }
            int temp = right - left + 1;
            result = result > temp ? result : temp;
        }
        return result;
    }
};