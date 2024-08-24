// https://leetcode.cn/problems/group-anagrams/description/?envType=study-plan-v2&envId=top-100-liked
// 49. 字母异位词分组
// 已解答
// 中等
// 相关标签
// 相关企业
// 给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
// 字母异位词 是由重新排列源单词的所有字母得到的一个新单词。

// 示例 1:
// 输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
// 输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

// 示例 2:
// 输入: strs = [""]
// 输出: [[""]]

// 示例 3:
// 输入: strs = ["a"]
// 输出: [["a"]]

// 提示：
// 1 <= strs.length <= 10^4
// 0 <= strs[i].length <= 100
// strs[i] 仅包含小写字母

#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

    }
};



// 用排序后的字符作为 key 原本字符作为 value
class Solution_G1_copy {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 每个单词都按字母排序，以字母序为key，存放在 mp 中
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);
        }
        vector<vector<string>> ans;
        // 用迭代器遍历
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};



// 注意到每个字符串字符的个数不超过 100，且都是小写字母
// 使用字符串的每一位统计每个字符的个数 string count(26, '0')
class Solution_L1_copy {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 编码到分组的映射
        unordered_map<string, vector<string>> codeToGroup;
        for (const string& s : strs) {
            // 对字符串进行编码
            string code = encode(s);
            // 把编码相同的字符串放在一起
            codeToGroup[code].push_back(s);
        }

        // 获取结果
        vector<vector<string>> res;
        for (auto& group : codeToGroup) {
            res.push_back(group.second);
        }

        return res;
    }

private:
    // 利用每个字符的出现次数进行编码
    string encode(const string& s) {
        string count(26, '0');
        for (char c : s) {
            int delta = c - 'a';
            count[delta]++;
        }
        return count;
    }
};




// 类似 L1 不过这里用的是vector<int> count(26, 0)
// 字符种类 26 个，字符个数可以非常大，但是字符串加减比较慢
// string = to_string(num)
class Solution_M1 {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 19点40分
        // 计数
        unordered_map<string, vector<string>> mp;
        for(string & s : strs) {
            vector<int> counts(26, 0);
            for(char ch : s) {
                counts[ch - 'a']++;
            }
            string key;
            for(int i=0; i<26; i++) {
                key = key + to_string(counts[i]) + ' '; // 需要空格区分不同字母的个数
            }
            mp[key].emplace_back(s);
        }
        vector<vector<string>> res;
        for(auto it = mp.begin(); it != mp.end(); ++it) {
            res.emplace_back(it->second);
        }
        return res;
    }
};


// 2024年7月22日 // 20点11分
// 自定义数组的 hansh 函数，避免 M1 的缺点
class Solution_M2 {
    // 自定义 array<int, 26> 的哈希函数
    struct arrayHash {
        std::size_t operator()(const array<int, 26>& arr) const {
            auto fn = hash<int>{};
            size_t h = 0;
            for(int i=0; i<26; i++) {
                h = (h << 1) ^ fn(arr[i]);
            }
            return h;
        }
    };
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<array<int, 26>, vector<string>, arrayHash> map;
        for(string& s : strs) {
            array<int, 26> count{0};
            for(char c : s) {
                count[c - 'a']++;
            }
            map[count].emplace_back(s);
        }
        vector<vector<string>> res;
        for(auto& m : map) {            
            res.emplace_back(m.second);
        }
        return res;
    }
};