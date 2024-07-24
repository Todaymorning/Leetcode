// 139. 单词拆分
// labuladong 题解思路
// 中等
// 给你一个字符串 s 和一个字符串列表 wordDict 作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
// 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

// 示例 1：
// 输入: s = "leetcode", wordDict = ["leet", "code"]
// 输出: true
// 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。

// 示例 2：
// 输入: s = "applepenapple", wordDict = ["apple", "pen"]
// 输出: true
// 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
//      注意，你可以重复使用字典中的单词。

// 示例 3：
// 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
// 输出: false

// 提示：
// 1 <= s.length <= 300
// 1 <= wordDict.length <= 1000
// 1 <= wordDict[i].length <= 20
// s 和 wordDict[i] 仅由小写英文字母组成
// wordDict 中的所有字符串 互不相同


#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using std::unordered_set;
using std::vector;
using std::string;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {

    }
};


// 19:51--20:14--20:25(爆栈)
// 完全背包，排列
// 先背包再物品，相当于排列，每个物品可以使用多次
// 回溯-----爆栈了
#if 0
class Solution_M1 {
    bool backtracking(string& s, vector<string>& wordDict, int s_idx) {
        if(s_idx == s.size()) return true;
        for(int i=0; i<wordDict.size(); i++) {
            int size = wordDict[i].size();
            string temp(s.begin() + s_idx, s.begin() + s_idx + size);
            if(!(wordDict[i] == temp)) continue;
            if(backtracking(s, wordDict, s_idx + size)) return true;
        }
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        if(s.size() == 0) return true;
        return backtracking(s, wordDict, 0);
    }
};
#endif

// 
class Solution_L1_M1 {
    // 备忘录
    vector<int> memo;
    // 定义：返回 s[i..] 是否能够被 wordDict 拼出
    bool dp(const string& s, const vector<string>& wordDict, int idx) {
        // base case，整个 s 都被拼出来了
        if(idx >= s.size()) return true;
        // 防止冗余计算
        if(memo[idx] != -1) {
            return memo[idx] == 1 ? true : false;
        }
        // 遍历所有单词，尝试匹配 s[i..] 的前缀
        for(int i=0; i<wordDict.size(); i++) {
            int len = wordDict[i].size();
            if(idx + len > s.size()) continue;
            string temp(s.begin() + idx, s.begin() + idx + len);
            // string temp = s.substr(idx, len);
            if(temp != wordDict[i]) {
                continue;
            }   // s[i..] 的前缀被匹配，去尝试匹配 s[i+len..]
            else if(dp(s, wordDict, idx + len)) {
                // s[i..] 可以被拼出，将结果记入备忘录
                memo[idx] = 1;
                return true;
            }
        }
        // s[i..] 不能被拼出，结果记入备忘录
        memo[idx] = 0;
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 备忘录，-1 代表未计算，0 代表 false，1 代表 true
        memo = vector<int>(s.size(), -1);
        // 根据函数定义，判断 s[0..] 是否能够被拼出
        return dp(s, wordDict, 0);
    }
};


// 会超时
// 时间复杂度：O (2^n)，因为每一个单词都有两个状态，切割和不切割
// 空间复杂度：O (n)，算法递归系统调用栈的空间
class Solution_D1 {
private:
    bool backtracking (const string& s, const unordered_set<string>& wordSet, int startIndex) {
        if (startIndex >= s.size()) {
            return true;
        }
        for (int i = startIndex; i < s.size(); i++) {
            string word = s.substr(startIndex, i - startIndex + 1);
            if (wordSet.find(word) != wordSet.end() && backtracking(s, wordSet, i + 1)) {
                return true;
            }
        }
        return false;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        return backtracking(s, wordSet, 0);
    }
};


// 21:03--21:17--21:21(超时)
// 看过 D1 的代码，尝试
// 使用 memory 数组保存每次计算的以 startIndex 起始的计算结果，如果 memory [startIndex] 里已经被赋值了，直接用 memory [startIndex] 的结果。
#if 0
class Solution_M2 {
    bool backtracking(const string& s, const unordered_set<string>& wordSet, vector<bool>memo, int startIdx) {
        if(startIdx >= s.size()) return true;
        if(memo[startIdx] == true) return true;
        for(int i=startIdx; i<s.size(); i++) {
            string temp = s.substr(startIdx, i - startIdx + 1); // 左闭右开 [startIdx, i+1), 至少有一个字符
            // string temp(s.begin() + startIdx, s.begin() + i + 1);
            if(wordSet.find(temp) == wordSet.end()) {
                continue;
            }
            else if(backtracking(s, wordSet, memo, i + 1)) {
                memo[i+1] = true;
                return true;
            }
        }
        return false;

    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> memo(s.size(), false);
        return backtracking(s, wordSet, memo, 0);
    }
};
#endif

// 在上面的基础上做出如下更改
class Solution_D2 {
    bool backtracking(const string& s, const unordered_set<string>& wordSet, vector<bool>&memo, int startIdx) { // 忘了memo 的 &，导致超时
        if(startIdx >= s.size()) return true;
        // 默认可以拆分，这里已经查询到以startIdx开头的字符串不可拆分，直接返回 false
        if(memo[startIdx] == false) return false;   // ***
        for(int i=startIdx; i<s.size(); i++) {
            string temp = s.substr(startIdx, i - startIdx + 1); // 左闭右开 [startIdx, i+1), 至少有一个字符
            // string temp(s.begin() + startIdx, s.begin() + i + 1);
            if(wordSet.find(temp) == wordSet.end()) {
                continue;
            }
            else if(backtracking(s, wordSet, memo, i + 1)) {
                return true;
            }
        }
        memo[startIdx] = false;     // 以 startIdx开始的字符串不可拆分  ***
        return false;

    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> memo(s.size(), true);  // 默认可以拆分     ***
        return backtracking(s, wordSet, memo, 0);
    }
};

// 结合 L1 修改如下
class Solution_D2_L1 {
    bool backtracking(const string& s, const unordered_set<string>& wordSet, vector<int>&memo, int startIdx) { // 忘了memo 的 &，导致超时
        if(startIdx >= s.size()) return true;
        // 防止冗余计算：memo[i] = 1：s[i...] 可以被拆分，memo[i] = 0：s[i...]不能被拆分
        if(memo[startIdx] != -1) return memo[startIdx] == 1 ? true : false;   // ***
        for(int i=startIdx; i<s.size(); i++) {
            string temp = s.substr(startIdx, i - startIdx + 1); // 左闭右开 [startIdx, i+1), 至少有一个字符
            // string temp(s.begin() + startIdx, s.begin() + i + 1);
            if(wordSet.find(temp) == wordSet.end()) {
                continue;
            }
            else if(backtracking(s, wordSet, memo, i + 1)) {
                memo[startIdx] = 1; // 可以被拆分
                return true;
            }
        }
        memo[startIdx] = 0;     // 以 startIdx开始的字符串不可拆分  ***
        return false;

    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<int> memo(s.size(), -1);  // 还未被探索
        return backtracking(s, wordSet, memo, 0);
    }
};




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 背包问题
// 单词就是物品，字符串 s 就是背包，单词能否组成字符串 s，就是问物品能不能把背包装满。
// 拆分时可以重复使用字典中的单词，说明就是一个完全背包！

// 16:11
// 完全背包，排列，内层正向遍历
// 先遍历物品再遍历背包是组合
// 先遍历背包再遍历物品是排列
// 时间复杂度：O (n^3)，因为 substr 返回子串的副本是 O (n) 的复杂度（这里的 n 是 substring 的长度）
// 空间复杂度：O (n)
class Solution_D2 {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size()+1, false);
        dp[0] = true;
        for(int j=1; j<=s.size(); j++) {    // 遍历背包
            for(int i=0; i<j; i++) {        // 遍历物品
                string temp = s.substr(i, j-i); // [i, j-1]
                if(wordSet.find(temp) != wordSet.end() && dp[i]) {
                    dp[j] = true;
                }
            }
        }   
        return dp.back();
    }
};