// https://leetcode.cn/problems/basic-calculator-ii
// 227. 基本计算器 II
// labuladong 题解
// 中等
// 相关标签
// 相关企业
// 给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值。
// 整数除法仅保留整数部分。
// 你可以假设给定的表达式总是有效的。所有中间结果将在 [-231, 231 - 1] 的范围内。
// 注意：不允许使用任何将字符串作为数学表达式计算的内置函数，比如 eval() 。

// 示例 1：
// 输入：s = "3+2*2"
// 输出：7

// 示例 2：
// 输入：s = " 3/2 "
// 输出：1

// 示例 3：
// 输入：s = " 3+5 / 2 "
// 输出：5

// 提示：
// 1 <= s.length <= 3 * 10^5
// s 由整数和算符 ('+', '-', '*', '/') 组成，中间由一些空格隔开
// s 表示一个 有效表达式
// 表达式中的所有整数都是非负整数，且在范围 [0, 2^31 - 1] 内
// 题目数据保证答案是一个 32-bit 整数

#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<numeric>
using std::accumulate;
using std::vector;
using std::stack;
using std::string;




class Solution {
public:
    int calculate(string s) {

    }
};




// 2024年5月7日
// 9:53--10:26
// 栈
class Solution_L1 {
    // 栈内所有数字求和
    int sum(stack<int> stk) {
        int res = 0;
        while(!stk.empty()) {
            res += stk.top();
            stk.pop();
        }
        return res;
    }
    // 将括号内的部分看作一个数，将数和数前面的符号一起放到栈内，*/单独处理
    // 遇到 左括号 递归调用，遇到 右括号 返回栈内数字和
    int helper(const string& s) {
        stack<int> stk;
        int num = 0;
        char sign = '+';    // 第一个数字前加上 + 方便计算
        for(int i=0; i<s.size(); i++) {
            char ch = s[i];
            // 不能直接 continue，否则如果最后一个字符是空格的话，可能每参与计算，如 "3+5/2 "中就没计算 /2
            // if(ch == ' ') continue;  // ***
            // 遇到左括号 递归
            if(ch == '(') {
                // 找到最外层括号，去掉最外层括号后送入递归
                int start = i + 1;
                int pairs=1;
                while(pairs) {
                    i++;
                    if(s[i] == ')') pairs--;
                    else if(s[i] == '(') pairs++;
                }
                string temp(s.begin() + start, s.begin() + i);
                num = helper(temp);
            }
            // 遇到数字，计算 num
            if(ch >= '0' && ch <= '9') num = num * 10 + (ch - '0');
            // 遇到非数字且非空格（即运算符）或遇到最后一个数
            if(ch != ' ' && ch < '0' || ch > '9' || i == s.size() - 1) {
                if(sign == '+')
                    stk.push(num);
                else if(sign == '-')
                    stk.push(-num);
                else if(sign == '*') {
                    stk.top() *= num;
                    // int temp = stk.top();
                    // stk.pop();
                    // stk.push(temp * num);
                }
                else if(sign == '/') {
                    stk.top() /= num;
                    // int temp = stk.top();
                    // stk.pop();
                    // stk.push(temp / num);
                }
                // 重置符号和数字
                num = 0;
                sign = ch;
            }
        }
        return sum(stk);
    }
public:
    // 默认 s 有效
    int calculate(string s) {
        return helper(s);
    }
};




// 化简，用 vector 替代栈，传参替代 string temp
class Solution_L1_M2 {
    // [start, end)
    int helper(const string& s, int start, int end) {
        vector<int> stk;
        int num = 0;
        char sign = '+';    // 第一个数字前加上 + 方便计算
        for(int i=start; i<end; i++) {
            char ch = s[i];
            // 遇到左括号 递归
            if(ch == '(') {
                // 找到最外层括号，去掉最外层括号后送入递归
                int left = i + 1;
                int pairs=1;
                while(pairs) {
                    i++;
                    if(s[i] == ')') pairs--;
                    else if(s[i] == '(') pairs++;
                }
                num = helper(s, left, i);   // s[i] == ')'
            }
            // 遇到数字，计算 num
            if(ch >= '0' && ch <= '9') num = num * 10 + (ch - '0');
            // 遇到非数字且非空格（即运算符）或遇到最后一个数
            if(ch != ' ' && ch < '0' || ch > '9' || i == end - 1) {
                if(sign == '+')
                    stk.push_back(num);
                else if(sign == '-')
                    stk.push_back(-num);
                else if(sign == '*') {
                    stk.back() *= num;
                }
                else if(sign == '/') {
                    stk.back() /= num;
                }
                // 重置符号和数字
                num = 0;
                sign = ch;
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);
    }
public:
    // 默认 s 有效
    int calculate(string s) {
        return helper(s, 0, s.size());
    }
};





// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/basic-calculator-ii/solutions/648647/ji-ben-ji-suan-qi-ii-by-leetcode-solutio-cm28/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G1 {
public:
    int calculate (string s) {
        vector<int> stk;
        char preSign = '+';
        int num = 0;
        int n = s.length ();
        for (int i = 0; i < n; ++i) {
            if (isdigit (s [i])) {
                num = num * 10 + int (s [i] - '0');
            }
            if (!isdigit (s [i]) && s [i] != ' ' || i == n - 1) {
                switch (preSign) {
                    case '+':
                        stk.push_back (num);
                        break;
                    case '-':
                        stk.push_back (-num);
                        break;
                    case '*':
                        stk.back () *= num;
                        break;
                    default:
                        stk.back () /= num;
                }
                preSign = s [i];
                num = 0;
            }
        }
        return accumulate (stk.begin (), stk.end (), 0);
    }
};