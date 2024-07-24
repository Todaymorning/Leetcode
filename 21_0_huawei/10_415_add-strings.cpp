// https://leetcode.cn/problems/add-strings
// 415. 字符串相加
// 已解答
// 简单
// 相关标签
// 相关企业
// 给定两个字符串形式的非负整数 num1 和 num2 ，计算它们的和并同样以字符串形式返回。
// 你不能使用任何內建的用于处理大整数的库（比如 BigInteger）， 也不能直接将输入的字符串转换为整数形式。

// 示例 1：
// 输入：num1 = "11", num2 = "123"
// 输出："134"

// 示例 2：
// 输入：num1 = "456", num2 = "77"
// 输出："533"

// 示例 3：
// 输入：num1 = "0", num2 = "0"
// 输出："0"

// 提示：
// 1 <= num1.length, num2.length <= 10^4
// num1 和 num2 都只包含数字 0-9
// num1 和 num2 都不包含任何前导零


#include<iostream>
#include<string>
#include<stack>
#include<algorithm>
using std::reverse;
using std::stack;
using std::string;

using std::max;


class Solution {
public:
    string addStrings(string num1, string num2) {

    }
};



// 2024年5月8日
// 10:49--11:00
// 访问过末尾后就 pop_back()
class Solution_M1 {
public:
    string addStrings(string num1, string num2) {
        int size1 = num1.size();
        int size2 = num2.size();
        string stk;
        int cur = 0;
        int pre = 0;
        for(int i=0; i<max(size1, size2); i++) {
            int n1 = 0, n2 = 0;
            if(num1.size() > 0) {
                n1 = num1.back() - '0';
                num1.pop_back();
            }
            if(num2.size() > 0) {
                n2 = num2.back() - '0';
                num2.pop_back();
            }
            cur = n1 + n2 + pre;
            pre = cur / 10;
            cur %= 10;
            stk.push_back(cur + '0');
        }
        if(pre) stk.push_back(pre + '0');
        reverse(stk.begin(), stk.end());
        return stk;
    }
};



// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/add-strings/solutions/357938/zi-fu-chuan-xiang-jia-by-leetcode-solution/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G1 {
public:
    string addStrings (string num1, string num2) {
        int i = num1.length () - 1, j = num2.length () - 1, add = 0;
        string ans = "";
        while (i >= 0 || j >= 0 || add != 0) {
            int x = i >= 0 ? num1 [i] - '0' : 0;
            int y = j >= 0 ? num2 [j] - '0' : 0;
            int result = x + y + add;
            ans.push_back ('0' + result % 10);
            add = result / 10;
            i -= 1;
            j -= 1;
        }
        // 计算完以后的答案需要翻转过来
        reverse (ans.begin (), ans.end ());
        return ans;
    }
};