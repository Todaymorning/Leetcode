// 17. 电话号码的字母组合
// 中等
// 给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
// 给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

// 提示：
// 0 <= digits.length <= 4
// digits[i] 是范围 ['2', '9'] 的一个数字。

// 注意：
// 题目描述中没有除了数字之外的字符，但是笔试、面试的时候可能会有相关的陷阱，需要考虑相应的情况处理

#include<iostream>
#include<vector>
#include<string>
using std::string;
using std::vector;

const string letterMap[10] = {
    "", // 0
    "", // 1
    "abc", // 2
    "def", // 3
    "ghi", // 4
    "jkl", // 5
    "mno", // 6
    "pqrs", // 7
    "tuv", // 8
    "wxyz", // 9
};


// 11:28--11:50
// 15:09(开始)--15:21(写)--15:26(改错)
// 时间复杂度: O (3^m * 4^n)，其中 m 是对应四个字母的数字个数，n 是对应三个字母的数字个数
// 空间复杂度: O (3^m * 4^n)
class Solution_M1 {
    const string letterMap[10] = {
    "", // 0
    "", // 1
    "abc", // 2
    "def", // 3
    "ghi", // 4
    "jkl", // 5
    "mno", // 6
    "pqrs", // 7
    "tuv", // 8
    "wxyz", // 9
    };
    vector<string> result;
    string track;
    void backtrack(const string& digits, int idx) {
        if(track.size() == digits.size()) {
            result.push_back(track);
            return;
        }
        // 字符转为对应的数字 '2' - '0'
        string temp = letterMap[digits[idx] - '0']; // digits idx位上的数字对应的字符串 ***
        for(int i=0; i<temp.size(); i++) {
            track.push_back(temp[i]);
            backtrack(digits, idx+1);   // 下一位数字 ***
            track.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        result.clear();
        track.clear();
        // 针对 digits = "" 应该返回 [] 应该加上下面这句话，否则会返回[""]
        if(digits.size() == 0) return result;   // ***
        backtrack(digits, 0);
        return result;
    }
};


// 将回溯的过程隐藏在递归的参数中
class Solution_D2_copy {
private:
        const string letterMap[10] = {
            "", // 0
            "", // 1
            "abc", // 2
            "def", // 3
            "ghi", // 4
            "jkl", // 5
            "mno", // 6
            "pqrs", // 7
            "tuv", // 8
            "wxyz", // 9
        };
public:
    vector<string> result;
    void getCombinations(const string& digits, int index, const string& s) { // 注意参数的不同
        if (index == digits.size()) {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0';
        string letters = letterMap[digit];
        for (int i = 0; i < letters.size(); i++) {
            getCombinations(digits, index + 1, s + letters[i]);  // 注意这里的不同
        }
    }
    vector<string> letterCombinations(string digits) {
        result.clear();
        if (digits.size() == 0) {
            return result;
        }
        getCombinations(digits, 0, "");
        return result;

    }
};