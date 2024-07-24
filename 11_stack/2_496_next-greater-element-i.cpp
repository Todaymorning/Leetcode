// 496. 下一个更大元素 I
// labuladong 题解思路
// 简单
// nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。
// 给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0 开始计数，其中 nums1 是 nums2 的子集。
// 对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定 nums2[j] 的 下一个更大元素 。
// 如果不存在下一个更大元素，那么本次查询的答案是 -1 。
// 返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。

// 示例 1：
// 输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
// 输出：[-1,3,-1]
// 解释：nums1 中每个值的下一个更大元素如下所述：
// - 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
// - 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
// - 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。

// 示例 2：
// 输入：nums1 = [2,4], nums2 = [1,2,3,4].
// 输出：[3,-1]
// 解释：nums1 中每个值的下一个更大元素如下所述：
// - 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
// - 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。

// 提示：
// 1 <= nums1.length <= nums2.length <= 1000
// 0 <= nums1[i], nums2[i] <= 10^4
// nums1 和 nums2 中所有整数 互不相同
// nums1 中的所有整数同样出现在 nums2 中

// 进阶：你可以设计一个时间复杂度为 O(nums1.length + nums2.length) 的解决方案吗？

#include<iostream>
#include<vector>
#include<stack>
#include<unordered_map>
using std::unordered_map;
using std::stack;
using std::vector;


class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

    }
};



// 11:51--11:55(读题找思路)--12:24
// 遍历长的，单调递减栈
class Solution_M1 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result1(nums1.size(), -1);
        vector<int> result2(nums2.size(), -1);  // 右侧比 nums2[0] 大的第一个元素是 nums[result2[0]]
        unordered_map<int,int> m;
        stack<int> s;
        s.push(0);
        m.insert({nums2[0], 0});
        for(int i=1; i<nums2.size(); i++) {
            m.insert({nums2[i], i});    // 通过元素找索引
            while(!s.empty() && nums2[i] > nums2[s.top()]) {    // 单调递减栈遇到比栈顶大的元素
                result2[s.top()] = nums2[i];   // 右侧比 nums2[s.top()] 大的第一个元素是 nums[i]
                s.pop();
            }
            s.push(i);  // 单调递减栈遇到小于等于栈顶的元素，压入
        }
        for(int i=0; i<nums1.size(); i++) {
            int idx = m[nums1[i]];
            result1[i] = result2[idx];
        }
        return result1;
    }
};


// 12:29--12:37(访问索引错误)
// map短的以供查找，遍历长的，判断map中是否有，没有的话可以跳过
// 这样可以减小内存占用
// nums1 短的，nums2 长的
class Solution_D1_M1 {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        vector<int> result(nums1.size(), -1);
        unordered_map<int, int> umap;
        // 根据元素的值找到索引
        for(int i=0; i<nums1.size(); i++) {
            umap.insert({nums1[i], i});
        }
        // 查找 nums2, 对 nums2 构造单调栈
        stack<int> s;   // 存索引
        s.push(0);
        for(int i=1; i<nums2.size(); i++) {
            while(!s.empty() && nums2[i] > nums2[s.top()]) {    // 单调递减栈遇到比栈顶大的元素
                if(umap.find(nums2[s.top()]) != umap.end()) {
                    result[umap[nums2[s.top()]]] = nums2[i];
                }
                s.pop();
            }
            s.push(i);  // 单调递减栈遇到小于等于栈顶的元素，压入
        }
        return result;
    }
};




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码不保证正确性，仅供参考。如有疑惑，可以参照我写的 java 代码对比查看。

// 倒着放入栈
class Solution_L1_copy {
public:
    vector<int> nextGreaterElement(std::vector<int>& nums) {
        int n = nums.size();
        // 存放答案的数组
        std::vector<int> res(n);
        std::stack<int> s; 
        // 倒着往栈里放
        for (int i = n - 1; i >= 0; i--) {
            // 判定个子高矮
            while (!s.empty() && s.top() <= nums[i]) {
                // 矮个起开，反正也被挡着了。。。
                s.pop();
            }
            // nums[i] 身后的更大元素
            res[i] = s.empty() ? -1 : s.top();
            s.push(nums[i]);
        }
        return res;
    }
};