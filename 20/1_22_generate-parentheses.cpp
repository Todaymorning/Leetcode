// https://leetcode.cn/problems/generate-parentheses/
// 22. 括号生成
// labuladong 题解
// 思路
// 已解答
// 中等
// 数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

// 示例 1：
// 输入：n = 3
// 输出：["((()))","(()())","(())()","()(())","()()()"]

// 示例 2：
// 输入：n = 1
// 输出：["()"]

// 提示：
// 1 <= n <= 8

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<unordered_set>
using std::unordered_set;
using std::string;
using std::vector;
using std::stack;

class Solution {
public:
    vector<string> generateParenthesis(int n) {

    }
};


// 10:49--11:11--11:21
// 回溯
// 重复加入
class Solution_M1 {
    unordered_set<string> result;
    string path;
    int num;
    string ch = "()";
    void backtracking(int left, int right) {
        //  括号分配完毕
        if(path.size() == num) {
            if(isValid(path) && !result.count(path)) {
                result.insert(path);
            }
            return;
        }
        // // 括号分配完毕
        // if(left < 1 && right < 1) return;
        for(int i=0; i<2; i++) {
            if(i == 0 && left >= 1) {
                path.push_back('(');
                backtracking(left-1, right);
                path.pop_back();
            }
            else if(right >= 1) {
                path.push_back(')');
                backtracking(left, right-1);
                path.pop_back();
            }
        }
    }
    bool isValid(const string& s) {
        int size = s.size();
        // 单数
        if(size % 2) return false;
        stack<char> stk;
        stk.push(s[0]);
        for(int i=1; i<size; i++) {
            if(s[i] == '(') {
                stk.push('(');  // 左括号入栈
            }
            else if(stk.empty()) {
                return false;   // 右括号匹配上了
            }
            else {
                stk.pop();      // 右括号没匹配上
            }
        }
        if(stk.empty()) return true;
        return false;
    }
public:
    vector<string> generateParenthesis(int n) {
        num = 2 * n;
        backtracking(n, n);
        vector<string> res;
        for(auto p : result) {
            res.push_back(p);
        }
        return res;
    }
};



// 用 left right 的数量关系校验，不用单独写函数
class Solution_M2 {
    vector<string> result;
    string path;
    int num;
    void backtracking(int left, int right) {
        // 只要右括号用的比左括号多，已经非法
        if(left > right) return;
        //  括号分配完毕
        if(path.size() == num) {
            result.push_back(path);
            return;
        }
        if(left >= 1) {
            path.push_back('(');
            backtracking(left-1, right);
            path.pop_back();
        }
        if(right >= 1) {
            path.push_back(')');
            backtracking(left, right-1);
            path.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        num = 2 * n;
        backtracking(n, n);
        return result;
    }
};



// 作者：负雪明烛
// 链接：https://leetcode.cn/problems/generate-parentheses/solutions/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_F1 {
public:
    vector<string> generateParenthesis (int n) {
        vector<string> res;
        int lc = 0, rc = 0;
        dfs (res, "", n, lc, rc);
        return res;
    }
    void dfs (vector<string>& res, string path, int n, int lc, int rc) {
        if (rc > lc || lc > n || rc > n) return;
        if (lc == rc && lc == n) {
            res.push_back (path);
            return;
        }
        dfs (res, path + '(', n, lc + 1, rc);
        dfs (res, path + ')', n, lc, rc + 1);
    }
};


// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/generate-parentheses/solutions/192912/gua-hao-sheng-cheng-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G1 {
    void backtrack (vector<string>& ans, string& cur, int open, int close, int n) {
        if (cur.size () == n * 2) {
            ans.push_back (cur);
            return;
        }
        if (open < n) {
            cur.push_back ('(');
            backtrack (ans, cur, open + 1, close, n);
            cur.pop_back ();
        }
        if (close < open) {
            cur.push_back (')');
            backtrack (ans, cur, open, close + 1, n);
            cur.pop_back ();
        }
    }
public:
    vector<string> generateParenthesis (int n) {
        vector<string> result;
        string current;
        backtrack (result, current, 0, 0, n);
        return result;
    }
};




//*****************************************************************************************************************************
// 16:52--16:54
// 回溯
// 左右括号各 n 个 backtracking(left, right, n)
class Solution {
    vector<string> result;
    string path;
    // left right 统计用了多少个左右括号
    void backtracking(int left, int right, int n) {
        if(left < right || left > n || right > n) return;
        if(left == n && right == n) result.emplace_back(path);

        path.push_back('(');
        backtracking(left+1, right, n);
        path.pop_back();

        path.push_back(')');
        backtracking(left, right+1, n);
        path.pop_back();
    }
public:
    vector<string> generateParenthesis(int n) {
        backtracking(0, 0, n);
        return result;
    }
};







// 多种括号