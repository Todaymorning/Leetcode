// 503. 下一个更大元素 II
// labuladong 题解
// 中等
// 给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回 nums 中每个元素的 下一个更大元素 。
// 数字 x 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 。

// 示例 1:
// 输入: nums = [1,2,1]
// 输出: [2,-1,2]
// 解释: 第一个 1 的下一个更大的数是 2；
// 数字 2 找不到下一个更大的数； 
// 第二个 1 的下一个最大的数需要循环搜索，结果也是 2。

// 示例 2:
// 输入: nums = [1,2,3,4,3]
// 输出: [2,3,4,-1,4]

// 提示:
// 1 <= nums.length <= 10^4
// -10^9 <= nums[i] <= 10^9


#include<iostream>
#include<vector>
#include<stack>
using std::stack;
using std::vector;


class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {

    }
};


// 14:40--14:52--15:09(错误)
// 0 1 2 3, size=4;
// i=2, max<8-2=6
class Solution_M1 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> result(nums.size(), -1);
        stack<int> s;
        s.push(0);
        for(int i=1; i < 2*size-1; i++) {
            while(!s.empty() && nums[i % size] > nums[s.top() % size]) { // i % size 可以循环
                result[s.top() % size] = nums[i % size];
                s.pop();
            }
            s.push(i);
        }
        return result;
    }
};


// 优化
class Solution_M1_2 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> result(size, -1);
        stack<int> s;
        // s.push(0);
        for(int i=0; i < 2*size-1; i++) {
            while(!s.empty() && nums[i % size] > nums[s.top()]) {   // 出现 i 的都是 i % size
                result[s.top()] = nums[i % size];
                s.pop();
            }
            s.push(i % size);   // ***
        }
        return result;
    }
};




class Solution_D3_copy {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;
        stack<int> st;
        for (int i = 0; i < nums.size() * 2; i++) {
            // 模拟遍历两边nums，注意一下都是用i % nums.size()来操作
            while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
                result[st.top()] = nums[i % nums.size()];
                st.pop();
            }
            st.push(i % nums.size());
        }
        return result;
    }
};




// 版本一
class Solution_D1_copy {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        // 拼接一个新的nums
        vector<int> nums1(nums.begin(), nums.end());
        nums.insert(nums.end(), nums1.begin(), nums1.end());    // ***
        // 用新的nums大小来初始化result
        vector<int> result(nums.size(), -1);
        if (nums.size() == 0) return result;

        // 开始单调栈
        stack<int> st;
        st.push(0);
        for (int i = 1; i < nums.size(); i++) { 
            if (nums[i] < nums[st.top()]) st.push(i); 
            else if (nums[i] == nums[st.top()]) st.push(i);
            else { 
                while (!st.empty() && nums[i] > nums[st.top()]) {
                    result[st.top()] = nums[i];
                    st.pop();
                }
                st.push(i);
            }
        }
        // 最后再把结果集即result数组resize到原数组大小
        result.resize(nums.size() / 2);
        return result;
    }
};