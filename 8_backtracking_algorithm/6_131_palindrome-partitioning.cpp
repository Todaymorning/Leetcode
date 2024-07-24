// 131. 分割回文串
// 中等
// 给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
// 回文串 是正着读和反着读都一样的字符串。

// 示例 1：
// 输入：s = "aab"
// 输出：[["a","a","b"],["aa","b"]]

// 示例 2：
// 输入：s = "a"
// 输出：[["a"]]
 

// 提示：
// 1 <= s.length <= 16
// s 仅由小写英文字母组成

#include<iostream>
#include<vector>
#include<string>
using std::string;
using std::vector;

class Solution {
public:
    vector<vector<string>> partition(string s) {

    }
};


// 21:24--21:44(不会，每一层回溯记录个数)--22:10(报错)--22:18(解决报错 <=)
// 输入s = "a"
// 输出 []
// 预期结果 [["a"]]
class Solution_M1 {
    vector<vector<string>> result;
    vector<string> track;
    int sum = 0;    //
    bool isPalindrome(string& s) {
        int size = s.size();
        int i;
        for(i=0; i < size / 2; i++) {
            if(s[i] != s[size-1-i]) break;
        }
        if(i == size/2) return true;
        return false;
    }
    void backtrack(const string& s) {
        if(sum >= s.size()) {
            if(sum == s.size()) result.push_back(track);
            return;
        }
        for(int i=1; i <= s.size(); i++) {   // i=1, i <= s.size(), 分割的子字符串大小至少为1 最大为字符串本身 ***
            if(sum + i > s.size()) return;  // 长度超标，结束递归
            string temp(s.begin() + sum, s.begin() + sum + i);
            if(!isPalindrome(temp)) continue;   // temp不是回文时，再分割长点
            sum += i;
            track.push_back(temp);
            backtrack(s);
            sum -= i;
            track.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        track.clear();
        backtrack(s);
        return result;
    }
};


// 9:43--9:53
// 回溯函数有idx参数
// 时间复杂度: O (n * 2^n)
// 空间复杂度: O (n^2)
class Solution_D1_M2 {
    vector<vector<string>> result;
    vector<string> track;   // 存放已经回文的子字符串
    // 判断s的 [strat, end] 是否是回文数
    bool isPalindrome(const string& s, int start, int end) {
        for(int i=start, j=end; i < j; i++, j--) {
            if(s[i] != s[j]) return false;
        }
        return true;
    }
    void backtrack(const string& s, int idx) {
         // 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
        if(idx >= s.size()) {
            if(idx == s.size()) result.push_back(track);
            return;
        }
        // 截取的是 [idx, i]
        for(int i=idx; i<s.size(); i++) {
            if(!isPalindrome(s, idx, i)) continue;
            track.push_back(string(s.begin()+idx, s.begin()+i+1));  // 这里面是左闭右开，因此右边需要加 1
            backtrack(s, i+1);  // i已经截过了，后面需要从i+1开始截取
            track.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        track.clear();
        backtrack(s, 0);
        return result;
    }
};


// 上面的代码还存在一定的优化空间，在于如何更高效的计算一个子字符串是否是回文字串。
// 上述代码 isPalindrome 函数运用双指针的方法来判定对于一个字符串 s, 
// 给定起始下标和终止下标，截取出的子字符串是否是回文字串。但是其中有一定的重复计算存在:
// 例如给定字符串 "abcde", 在已知 "bcd" 不是回文字串时，不再需要去双指针操作 "abcde" 而可以直接判定它一定不是回文字串。
// 具体来说，给定一个字符串 s, 长度为 n, 它成为回文字串的充分必要条件是 s[0] == s[n-1] 且 s[1:n-1] 是回文字串。
// 大家如果熟悉动态规划这种算法的话，我们可以高效地事先一次性计算出，针对一个字符串 s, 
// 它的任何子串是否是回文字串，然后在我们的回溯函数中直接查询即可，省去了双指针移动判定这一步骤.
class Solution_D2 {
    vector<vector<string>> result;
    vector<string> track;   // 存放已经回文的子字符串
    vector<vector<bool>> isPalindrome;   // 放事先计算好的是否回文子串的结果
    
    // isPalindrome[i][j] 代表 s[i:j](双边包括)是否是回文字串
    void computePalindrome(const string& s) {
        isPalindrome.clear();
        isPalindrome.resize(s.size(), vector<bool>(s.size(), false));   // ***
        // 需要倒序计算, 保证在i行时, i+1行已经计算好了
        for(int i=s.size()-1; i>=0; i--) {
            for(int j=i; j<s.size(); j++) {
                if(i == j) isPalindrome[i][j] = true;
                else if(j-i==1) isPalindrome[i][j] = (s[i] == s[j]);
                else isPalindrome[i][j] = (s[i] == s[j] && isPalindrome[i+1][j-1]);
            }
        }
    }

    void backtrack(const string& s, int idx) {
         // 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
        if(idx >= s.size()) {
            if(idx == s.size()) result.push_back(track);
            return;
        }
        // 截取的是 [idx, i]
        for(int i=idx; i<s.size(); i++) {
            if(!isPalindrome[idx][i]) continue; // ***
            track.push_back(string(s.begin()+idx, s.begin()+i+1));  // 这里面是左闭右开，因此右边需要加 1
            backtrack(s, i+1);  // i已经截过了，后面需要从i+1开始截取
            track.pop_back();
        }
    }
public:
    vector<vector<string>> partition(string s) {
        result.clear();
        track.clear();
        isPalindrome.clear();
        computePalindrome(s);
        backtrack(s, 0);
        return result;
    }
};