// 647. 回文子串
// 中等
// 给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
// 回文字符串 是正着读和倒过来读一样的字符串。
// 子字符串 是字符串中的由连续字符组成的一个序列。
// 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

// 示例 1：
// 输入：s = "abc"
// 输出：3
// 解释：三个回文子串: "a", "b", "c"

// 示例 2：
// 输入：s = "aaa"
// 输出：6
// 解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"

// 提示：
// 1 <= s.length <= 1000
// s 由小写英文字母组成



#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;


class Solution {
public:
    int countSubstrings(string s) {

    }
};



// 11:08--11:51(遍历顺序老是错误)
// 确定 dp 数组（dp table）以及下标的含义
// 如果大家做了很多这种子序列相关的题目，在定义 dp 数组的时候 很自然就会想题目求什么，我们就如何定义 dp 数组。
// 绝大多数题目确实是这样，不过本题如果我们定义，dp [i] 为 下标 i 结尾的字符串有 dp [i] 个回文串的话，我们会发现很难找到递归关系。
// dp [i] 和 dp [i-1] ，dp [i + 1] 看上去都没啥关系。
// 我们在判断字符串 S 是否是回文，那么如果我们知道 s [1]，s [2]，s [3] 这个子串是回文的，那么只需要比较 s [0] 和 s [4] 这两个元素是否相同，
// 如果相同的话，这个字符串 s 就是回文串。
// 那么此时我们是不是能找到一种递归关系，也就是判断一个子字符串（字符串的下表范围 [i,j]）是否回文，依赖于，子字符串（下表范围 [i + 1, j - 1]）） 是否是回文。
// 所以为了明确这种递归关系，我们的 dp 数组是要定义成一位二维 dp 数组。
// 布尔类型的 dp [i][j]：表示区间范围 [i,j] （注意是左闭右闭）的子串是否是回文子串，如果是 dp [i][j] 为 true，否则为 false。

// 确定递推公式
// 在确定递推公式时，就要分析如下几种情况。
// 整体上是两种，就是 s [i] 与 s [j] 相等，s [i] 与 s [j] 不相等这两种。
// 当 s [i] 与 s [j] 不相等，那没啥好说的了，dp [i][j] 一定是 false。
// 当 s [i] 与 s [j] 相等时，这就复杂一些了，有如下三种情况
//      情况一：下标 i 与 j 相同，同一个字符例如 a，当然是回文子串
//      情况二：下标 i 与 j 相差为 1，例如 aa，也是回文子串
//      情况三：下标：i 与 j 相差大于 1 的时候，例如 cabac，此时 s [i] 与 s [j] 已经相同了，
//              我们看 i 到 j 区间是不是回文子串就看 aba 是不是回文就可以了，那么 aba 的区间就是 i+1 与 j-1 区间，
//              这个区间是不是回文就看 dp [i + 1][j - 1] 是否为 true。
class Solution {
public:
    int countSubstrings(string s) {
        int size = s.size();
        vector<vector<bool>> dp(size, vector<bool>(size, false));
        int result = 0;
        for(int i=size-1; i>=0; i--) {
            for(int j=i; j<size; j++) { // 注意遍历顺序
                if(s[i] != s[j]) {
                    dp[i][j] = false;
                }
                else {
                    if(i == j) dp[i][j] = true;
                    else if(i+1 == j) dp[i][j] = true;
                    else if(dp[i+1][j-1]) dp[i][j] = true;  // i+1 要求 i 倒序，j-1要求 j 正序，且需要 i <= j
                    else dp[i][j] = false;

                    if(dp[i][j]) result++;
                }
            }
        }
        return result;
    }
};

// 时间复杂度：O (n^2)
// 空间复杂度：O (n^2)
class Solution_D1 {
public:
    int countSubstrings(string s) {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;
        for (int i = s.size() - 1; i >= 0; i--) {  // 注意遍历顺序
            for (int j = i; j < s.size(); j++) {
                if (s[i] == s[j]) {
                    if (j - i <= 1) { // 情况一 和 情况二
                        result++;
                        dp[i][j] = true;
                    } else if (dp[i + 1][j - 1]) { // 情况三
                        result++;
                        dp[i][j] = true;
                    }
                }
            }
        }
        return result;
    }
};


// 双指针法
// 动态规划的空间复杂度是偏高的，我们再看一下双指针法。
// 首先确定回文串，就是找中心然后向两边扩散看是不是对称的就可以了。
// 在遍历中心点的时候，要注意中心点有两种情况。
// 一个元素可以作为中心点，两个元素也可以作为中心点。
// 那么有人同学问了，三个元素还可以做中心点呢。其实三个元素就可以由一个元素左右添加元素得到，四个元素则可以由两个元素左右添加元素得到。
// 所以我们在计算的时候，要注意一个元素为中心点和两个元素为中心点的情况。
// 时间复杂度：O (n^2)
// 空间复杂度：O (1)
class Solution {
public:
    int countSubstrings(string s) {
        int result = 0;
        for (int i = 0; i < s.size(); i++) {
            result += extend(s, i, i, s.size()); // 以 i 为中心
            result += extend(s, i, i + 1, s.size()); // 以 i 和 i+1 为中心
        }
        return result;
    }
    int extend(const string& s, int i, int j, int n) {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) {
            i--;
            j++;
            res++;
        }
        return res;
    }
};