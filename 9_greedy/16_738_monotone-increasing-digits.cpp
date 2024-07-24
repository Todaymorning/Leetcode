// 738. 单调递增的数字
// 中等
// 当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。
// 给定一个整数 n ，返回 小于或等于 n 的最大数字，且数字呈 单调递增 。

// 示例 1:
// 输入: n = 10
// 输出: 9

// 示例 2:
// 输入: n = 1234
// 输出: 1234

// 示例 3:
// 输入: n = 332
// 输出: 299

// 提示:
// 0 <= n <= 10^9


#include<iostream>
#include<vector>
#include<string>
using std::string;
using std::vector;
class Solution {
public:
    int monotoneIncreasingDigits(int n) {

    }
};


// 10:29--10:42(超出时间限制)
// n = 954508339
#if 0
class Solution_M1 {
    bool isValid(int n) {
        int low = n % 10;
        int high = (n / 10) % 10;
        while(n/10 > 0) {
            if(high > low) return false;
            n /= 10;
            low = n % 10;
            high = (n / 10) % 10;
        }
        return true;
    }
public:
    int monotoneIncreasingDigits(int n) {
        while(! isValid(n)) n--;
        return n;
    }
};

class Solution_D1 {
private:
    // 判断一个数字的各位上是否是递增
    bool checkNum(int num) {
        int max = 10;
        while (num) {
            int t = num % 10;
            if (max >= t) max = t;  // 从低位到高位检查，高位低于低位时max替换为更小的，否则返回 false
            else return false;
            num = num / 10;
        }
        return true;
    }
public:
    int monotoneIncreasingDigits(int N) {
        for (int i = N; i > 0; i--) { // 从大到小遍历
            if (checkNum(i)) return i;
        }
        return 0;
    }
};
#endif

// 10:46--10:52(只从前往后替换完全错误)--10:55(错误,只从后往前，没有从前往后)--11:04
// 转化为字符串后 先后向替换 再 前向替换
// 输入
// n =
// 954508339
// 输出
// 899497939
// 预期结果
// 899999999
class Solution_M2 {
public:
    int monotoneIncreasingDigits(int n) {
        if(n < 10) return n;
        string s = std::to_string(n);
        // 正序修改，记录被修改的最高位
        int pos = -1;
        for(int i=s.size() - 2; i>=0; i--) {
            if(s[i] > s[i+1]) {
                pos = i;
                s[i]--;
                s[i+1] = '9';
            }
        }
        // 最高位被替换后，后面的可以全部替换为 9
        // ***
        if(pos == -1) return std::stoi(s);
        for(int i=pos+1; i<s.size(); i++) {
            s[i] = '9';
        }
        return std::stoi(s);
    }
};


class Solution_M2_2 {
public:
    int monotoneIncreasingDigits(int n) {
        if(n < 10) return n;
        string s = std::to_string(n);
        int pos = s.size(); // ***
        for(int i=s.size() - 2; i>=0; i--) {
            if(s[i] > s[i+1]) {
                pos = i;
                s[i]--;
                s[i+1] = '9';
            }
        }
        // if(pos == -1) return std::stoi(s);
        for(int i=pos+1; i<s.size(); i++) {
            s[i] = '9';
        }
        return std::stoi(s);
    }
};



// 时间复杂度：O (n)，n 为数字长度
// 空间复杂度：O (n)，需要一个字符串，转化为字符串操作更方便
class Solution_D2_copy {
public:
    int monotoneIncreasingDigits(int N) {
        string strNum = std::to_string(N);
        // flag用来标记赋值9从哪里开始
        // 设置为这个默认值，为了防止第二个for循环在flag没有被赋值的情况下执行
        int flag = strNum.size();
        for (int i = strNum.size() - 1; i > 0; i--) {
            if (strNum[i - 1] > strNum[i] ) {
                flag = i;
                strNum[i - 1]--;
            }
        }
        for (int i = flag; i < strNum.size(); i++) {
            strNum[i] = '9';
        }
        return std::stoi(strNum);
    }
};