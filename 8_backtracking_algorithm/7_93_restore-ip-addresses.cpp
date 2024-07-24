// 93. 复原 IP 地址
// 中等
// 有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
// 例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，
// 但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
// 给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，
// 这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。

// 示例 1：
// 输入：s = "25525511135"
// 输出：["255.255.11.135","255.255.111.35"]

// 示例 2：
// 输入：s = "0000"
// 输出：["0.0.0.0"]

// 示例 3：
// 输入：s = "101023"
// 输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
 
// 提示：
// 1 <= s.length <= 20
// s 仅由数字组成


#include<iostream>
#include<string>
#include<vector>
using std::string;
using std::vector;


class Solution {
public:
    vector<string> restoreIpAddresses(string s) {

    }
};

//10:28--10:50(有错误)--10:58
// 输入s ="101023"
// 输出["1.0.1.023","1.0.10.23","1.0.102.3","1.01.0.23","1.01.02.3","1.010.2.3","10.1.0.23","10.1.02.3","10.10.2.3","101.0.2.3"]
// 预期结果["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
// 时间复杂度: O (3^4)，IP 地址最多包含 4 个数字，每个数字最多有 3 种可能的分割方式，
// 则搜索树的最大深度为 4，每个节点最多有 3 个子节点。
// 空间复杂度: O (n)
class Solution_M1 {
    vector<string> result;
    vector<string> track;   // 分离存储子字符串
    // [begin, end]
    int str2num(const string str, int begin, int end) {
        int result = 0;
        for(int i=begin; i<=end; i++) {
            result = result*10 + (str[i] - '0');
        }
        return result;
    }

    // ******************************************************
    // 判断字符串s在左闭又闭区间[start, end]所组成的数字是否合法
    bool isValid(const string& s, int start, int end) {
        if (start > end) {
            return false;
        }
        // 不是一位数字且第一位为0
        if (s[start] == '0' && start != end) { // 0开头的数字不合法
                return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }
    // ********************************************************

    void backtrack(const string& s, int idx) {
        if(idx >= s.size() || track.size() == 4) {
            // 先拼接再放到 result中
            if(idx == s.size() && track.size() == 4) {
                string temp(track[0]);
                for(int i=1; i<4; i++) {
                    temp = temp + "." + track[i];
                }
                result.push_back(temp);
            }
            return;
        }
        // [idx, i]
        for(int i=idx; i<s.size(); i++) {
            // 两位数字时，第一个为 0
            if(i - idx == 1 && s[idx] == '0') return;
            // 三位数字大于255
            if(i - idx == 2 && str2num(s, idx, i) > 255) return;
            // 大于三位数字
            if(i - idx > 2) return;
            track.push_back(string(s.begin() + idx, s.begin() + i + 1));
            backtrack(s, i + 1);
            track.pop_back();
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        result.clear();
        if(s.size() < 4 || s.size() > 12) return result;
        backtrack(s, 0);
        return result;
    }
};
