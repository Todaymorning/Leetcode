// 1047. 删除字符串中的所有相邻重复项
// 给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
// 在 S 上反复执行重复项删除操作，直到无法继续删除。
// 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。

// 示例：
// 输入："abbaca"
// 输出："ca"
// 解释：例如，在 "abbaca" 中，我们可以删除 "bb" 由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串 "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。

// 提示：
// 1 <= S.length <= 20000
// S 仅由小写英文字母组成。

# include<iostream>
# include<stack>
# include<algorithm>
using namespace std;

class Solution_M {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        int size = s.size();
        for(int i=0; i<size; i++) {
            if(!st.empty()) {
                if(s[i] == st.top()) {
                    // 每次只删除两个相邻字符，因此没有下面这句
                    // while(i<size-1 && s[i] == s[i+1]) i++;
                    st.pop();
                }
                else
                    st.push(s[i]);
            }
            else
                st.push(s[i]);
        }
        size = st.size();
        string S(size, ' ');
        for(int i=size-1; i>=0; i--) {
            S[i] = st.top();
            st.pop();
        }
        return S;
    }
};


// 使用 s:S 和 reverse
class Solution_D1 {
public:
    string removeDuplicates(string S) {
        stack<char> st;
        for(char s:S) {
            if(st.empty() || s!=st.top()) {
                st.push(s);
            }
            else {
                st.pop();    // 相等
            }
        }
        // stack to string
        string result = "";
        while(!st.empty()) {
            result += st.top();
            st.pop();
        }
        // reverse
        reverse(result.begin(), result.end());
        return result;
    }
};


// 将string直接作为stack使用，不用再将其反转
class Solution_D2 {
public:
    string removeDuplicates(string S) {
        string result;
        for(char s:S) {
            if(!result.empty()) {
                if(s == result.back()) {
                    result.pop_back();
                }
                else {
                    result.push_back(s);
                }
            }
            else {
                result.push_back(s);
            }
        }
        return result;
    }
};

int main()
{
    return 0;
}
