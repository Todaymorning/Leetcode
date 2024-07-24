// https://leetcode.cn/problems/valid-parentheses/
// 20. 有效的括号
// labuladong 题解
// 思路
// 已解答
// 简单
// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
// 有效字符串需满足：
// 左括号必须用相同类型的右括号闭合。
// 左括号必须以正确的顺序闭合。后遇到的左括号要先闭合
// 注意空字符串可被认为是有效字符串。


// 分析：后遇到的左括号要先闭合
// 括号匹配是使用栈解决的经典问题。
// 不匹配有三种情况：
// 1左括号多余
// 2右括号多余
// 3左右类型不匹配

// 小技巧: 右括号入栈而不是左括号入栈，这样匹配的时候简单判断是否相等即可
// 如果是左括号入栈，判断是否匹配还得做个转换，每直接比较简单

// 第一种情况：已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以 return false
// 第二种情况：遍历字符串匹配的过程中，发现栈里没有要匹配的字符。所以 return false
// 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false

# include<iostream>
# include<stack>
# include<unordered_map>
using namespace std;


// 时间 O(n)
// 空间 O(n)
class Solution_D1 {
public:
    bool is_Valid(string s) {
        int size = s.size();
        if(size % 2) {
            return false;
        }
        stack<char> st;
        for(int i=0; i<size; i++) {
            if(s[i]=='(')       // 处理左括号，都是入栈
                st.push(')');
            else if(s[i]=='[')
                st.push(']');
            else if(s[i]=='{')
                st.push('}');   // 处理右括号
            // 第二、三种情况
            else if(st.empty() || st.top() != s[i])
                return false;   // 少对应的右括号：已经弹完或不匹配
            else
                st.pop();   // s[i]和栈顶相同，匹配上了
        }
        return st.empty();   // 第一种情况
    }
};


class Solution_G1 {
public:
    bool is_Valid(string s) {
        int size = s.size();
        if(size % 2 != 0) return false;
        stack<char> st;
        unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        for(char ch:s) {
            // ch是右括号的时候
            if(pairs.count(ch)) {
                // 没匹配上
                if(st.empty() || st.top() != pairs[ch]) {
                    return false;
                }
                // 匹配上了
                st.pop();
            }
            else
                st.push(ch);    // ch 是左括号
        }
        return st.empty();
    }
};



// 2024年4月29日
// 22:12--22:21(错误)
#if 0
class Solution {
    char pairs[3][2] = {'(', ')', '[', ']', '{', '}'};
public:
    bool isValid(string s) {
        int n = s.size();
        if(n % 2) return false;
        stack<char> stk;
        stk.push(s[0]);
        for(auto ch : s) {
            if(ch == pairs[0][0] || ch == pairs[1][0] || ch == pairs[2][0]) stk.push(ch);
            else if(!stk.empty() && stk.top() == ch) {
                stk.pop();
            }
            else {
                return false;
            }
        }
        if(!stk.empty()) return false;
        return true;
    }
};
#endif


// 2024年4月29日
// 23:44--23:55
class Solution_1 {
public:
    bool isValid(string s) {
        if(s.size() % 2) return false;
        unordered_map<char,char> pairs = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
        stack<char> stk;
        for(auto ch : s) {
            if(pairs.find(ch) != pairs.end()) {
                stk.push(ch);   // 左
            }
            else if(!stk.empty() && pairs[stk.top()] == ch) {
                stk.pop();
            }
            else {
                return false;
            }
        }
        if(!stk.empty()) return false;
        return true;
    }
};




// 2024年5月6日
// 20:53--21:22
class Solution_2 {
public:
    bool isValid(string s) {
        int n = s.size();
        if(n % 2) return false;
        unordered_map<char, char> pairs = {{')', '('}, {']', '['}, {'}', '{'}};
        stack<char> stk;
        for(int i=0; i<n; i++) {
            if(pairs.find(s[i]) == pairs.end()) stk.push(s[i]);
            else if(stk.empty() || stk.top() != pairs[s[i]]) return false;  // ***
            else stk.pop();         // stk.top() != pairs[s[i]]
        }
        return stk.empty();
    }
};
