// https://leetcode.cn/problems/decode-string
// 394. 字符串解码
// 中等
// 相关标签
// 相关企业
// 给定一个经过编码的字符串，返回它解码后的字符串。
// 编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。
// 你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
// 此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

// 示例 1：
// 输入：s = "3[a]2[bc]"
// 输出："aaabcbc"

// 示例 2：
// 输入：s = "3[a2[c]]"
// 输出："accaccacc"

// 示例 3：
// 输入：s = "2[abc]3[cd]ef"
// 输出："abcabccdcdcdef"

// 示例 4：
// 输入：s = "abc3[cd]xyz"
// 输出："abccdcdcdxyz"
 

// 提示：
// 1 <= s.length <= 30
// s 由小写英文字母、数字和方括号 '[]' 组成
// s 保证是一个 有效 的输入。
// s 中所有整数的取值范围为 [1, 300] 



#include<iostream>
#include<string>
#include<stack>
using std::string;
using std::stack;



class Solution {
public:
    string decodeString(string s) {

    }
};


// 2024年4月24日
// 19:45--20:10
// 递归
class Solution_M1 {
public:
    string decodeString(string s) {
        string result;
        stack<char> stk;
        // 遍历
        for(int i=0; i<s.size(); i++) {
            // 数字 (扩增倍数)  [] 前面一定有数字，数字后面一定有 []
            if(s[i] >= '0' && s[i] <= '9') {
                int num = s[i] - '0';
                i++;
                while(s[i] != '[') {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                // 括号
                stk.push('[');  // [
                string temp;
                while(!stk.empty()) {
                    i++;
                    if(s[i] == '[') stk.push('[');
                    else if(s[i] == ']') stk.pop();
                    temp += s[i];
                }
                temp.pop_back();    // ]
                string next = decodeString(temp);
                for(int j=0; j<num; j++) {
                    result += next;
                }
            }
            // 字母
            else {
                result += s[i];
            }
        }
        return result;
    }
};




// 2024年5月12日
// 10:47--11:28
// s[i++] 耦合度较大，i++ 分离后逻辑较好处理，建议用上面的解法
class Solution {
public:
    string decodeString(string s) {
        string result;
        int n = s.size();
        for(int i=0; i<n; i++) {
            if(isalpha(s[i])) {
                // 不用扩增的字母
                result += s[i];
                // while(i<n && isalpha(s[i])) result += s[i++];    // ***
            }
            else if(isdigit(s[i])) {    // [] 前面一定有数字，数字后面一定有 []
                // 扩增倍数
                int num = 0;
                while(i<n && isdigit(s[i])) num = num * 10 + (s[i++] - '0');
                // 处理括号和递归
                int stk = 1;
                i++;    // 跳过左括号
                string sub;
                while(stk > 0) {    // 获取最外层 [] 中的字符， 这里stk为空前 i 不会超过 n
                    if(s[i] == '[') stk++;
                    else if(s[i] == ']') stk--;
                    sub += s[i++];  // 可以不用判断 i<n，会把最右侧 ] 放入 sub
                }
                i--;    // 多增了一个       // ***
                sub.pop_back(); // 跳过右括号
                // 递归
                string temp = decodeString(sub);
                while(num > 0) {
                    result += temp;
                    num--;
                }
            }
        }
        return result;
    }
};