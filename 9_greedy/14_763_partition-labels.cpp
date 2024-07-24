// 763. 划分字母区间
// 中等
// 给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。
// 注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。
// 返回一个表示每个字符串片段的长度的列表。

// 示例 1：
// 输入：s = "ababcbacadefegdehijhklij"
// 输出：[9,7,8]
// 解释：
// 划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
// 每个字母最多出现在一个片段中。
// 像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。 

// 示例 2：
// 输入：s = "eccbbbbdec"
// 输出：[10]

// 提示：
// 1 <= s.length <= 500
// s 仅由小写英文字母组成


#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;

class Solution {
public:
    vector<int> partitionLabels(string s) {

    }
};

// 20:50--21:15
// 每个字符串个数尽量少----字符串尽量多
// 从字符串中截取首尾字符相同的字符串
// 由子字符串中的元素更新结尾位置
class Solution_M1 {
    // 从后往前找第一个与给定字符相同的字符位置
    int find_last_char(string& s, char c, int i) {
        int size = s.size();
        int pos = -1;
        for(int j=size-1; j>i; j--) {
            if(s[j] == c) {
                pos = j;
                break;
            }
        }
        return pos;
    }
public:
    vector<int> partitionLabels(string s) {
        int size = s.size();
        vector<int> result;
        for(int i=0; i<size; ) {
            // 截取子字符串[i, pos]，其中s[i] = s[pos]
            char c = s[i];
            int pos = find_last_char(s, c, i);  // 找到一个结尾
            // pos 处有相同的字符，[i, pos]是一个子字符串，从s中找(i, pos)中相同的字符来更新结尾
            if(pos != -1) {
                for(int k=i+1; k<=pos; k++) {
                    int temp = find_last_char(s, s[k], k);
                    if(temp > pos) pos = temp;  // 更新结尾
                }
                result.push_back(pos - i + 1);
                i = pos+1;
            }
            else {
                result.push_back(1);
                i++;
            }
        }
        return result;
    }
};


// 21:15--21:22(看 D1 思路)--
// 统计每个字符出现的最后的位置，
// 从头遍历字符，并更新字符的最远出现下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点
class Solution_D1_M2 {
public:
    vector<int> partitionLabels(string s) {
        // 统计每个字符最后出现的位置
        // 从后往前统计，没有下面的简单
        int hash[26] = {0};
        for(int i=s.size()-1; i>=0; i--) {
            if(hash[s[i] - 'a'] == 0) hash[s[i] - 'a'] = i;
        }
        // 从前往后统计
        // for(int i=0; i<s.size(); i++) {
        //     hash[s[i] - 'a'] = i;
        // }
        vector<int> result;
        for(int i=0; i<s.size(); ) {    // 没有了i++，i在里面更新    // ***
            int pos = hash[s[i] - 'a'];
            for(int j=i+1; j<pos; j++) {
                int temp = hash[s[j] - 'a'];    // s[j]不是s[i] // ***
                if(temp > pos) pos = temp;  // 更新结尾
            }
            if(pos == 0) {
                result.push_back(1);
                i++;
            }
            else{
                result.push_back(pos - i + 1);
                i = pos + 1;
            }
        }
        return result;
    }
};



// 9:49--9:54--10:01
// 看过 D1 的思路和代码
// 时间复杂度：O (n)
// 空间复杂度：O (1)，使用的 hash 数组是固定大小
class Solution_D1 {
public:
    vector<int> partitionLabels(string s) {
        int hash[26] = {0};
        // 记录每个字母在字符串中出现的位置
        for(int i=0; i<s.size(); i++) {
            hash[s[i] - 'a'] = i;
        }
        vector<int> result;
        int left = 0;
        int right = 0;
        for(int i=0; i<s.size(); i++) {
            right = std::max(right, hash[s[i] - 'a']);
            if(i == right) {
                result.push_back(right - left + 1);
                // 忘记 +1
                left = right + 1;   // ***
            }
        }
        return result;
    }
};