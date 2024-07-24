// 84. 柱状图中最大的矩形
// 困难
// 给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
// 求在该柱状图中，能够勾勒出来的矩形的最大面积。

// 示例 1:
// 输入：heights = [2,1,5,6,2,3]
// 输出：10
// 解释：最大的矩形为图中红色区域，面积为 10

// 示例 2：
// 输入： heights = [2,4]
// 输出： 4

// 提示：
// 1 <= heights.length <=10^5
// 0 <= heights[i] <= 10^4
// https://leetcode.cn/problems/largest-rectangle-in-histogram/



#include<iostream>
#include<vector>
#include<stack>
using std::stack;
using std::vector;
using std::max;
using std::min;


class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        return 0;
    }
};



#if 0
// 22:13--22:22(读题找思路)
// 单调上升栈
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        stack<int> s;
        for(int i=0; i<size; i++) {
            if(heights[i] == 0) {
                while(!s.empty()) s.pop();
                continue;
            }

        }
    }
};

// 22:25--22:35
// 双指针
// 找到左右最小的数
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        vector<int> leftL(size, -1);
        vector<int> rightL(size, -1);

        leftL[0] = heights[0];
        for(int i=1; i<size; i++) {
            leftL[i] = min(leftL[i-1], heights[i]);
        }

        rightL.back() = heights.back();
        for(int i=size-2; i>=0; i--) {
            rightL[i] = min(rightL[i+1], heights[i]);
        }
    }
};


// 22:35--22:43
// 动态规划
// dp[i][j] i 到 j 最大矩形面积 i <= j
// dp[i][j] 需要从dp[i+1][j-1]推出
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        vector<vector<int>> dp(size, vector<int>(size, 0));
        for(int i=size-1; i>=0; i--) {
            for(int j=i; j<size; j++) {
                
            }
        }
    }
};
#endif

// 暴力解法：超时
// 双指针
// 间复杂度是 O (n^2)
// 求以每个矩形的高为高，最长的作为长，求面积
// 求长时需要注意，求每个矩形左右边第一个较小的值作为长的基准
class Solution_D1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int sum = 0;
        for (int i = 0; i < heights.size(); i++) {
            int left = i;
            int right = i;
            // 左边第一个较小的值
            for (; left >= 0; left--) {
                if (heights[left] < heights[i]) break;
            }
            // 右边第一个较小的值
            for (; right < heights.size(); right++) {
                if (heights[right] < heights[i]) break;
            }
            int w = right - left - 1;
            int h = heights[i];
            std::cout << "i left right s: " << i << "\t" << left << "\t" << right << "\t" << w*h << std::endl;
            sum = max(sum, w * h);
        }
        return sum;
    }
};

// int main() {
//     Solution_D1 s;
//     vector<int> nums = {2,1,5,6,2,3};
//     s.largestRectangleArea(nums);
//     return 0;
// }
// // i left right s: 0       -1      1       2 
// // i left right s: 1       -1      6       6 
// // i left right s: 2       1       4       10
// // i left right s: 3       2       4       6 
// // i left right s: 4       1       6       8 
// // i left right s: 5       4       6       3 


// 23:05--23:14
// 双指针优化(单调栈)
class Solution_D1_M1 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = heights.size();
        // 存放索引
        vector<int> leftL(size, -1);    // ***
        vector<int> rightL(size, size); // ***
        stack<int> s;
        // 左边第一个小值，倒序，单调递增栈
        for(int i=size-1; i>=0; i--) {  // 单调栈，左边第一个小值
            while(!s.empty() && heights[i] < heights[s.top()]) {    // 单调递增栈
                leftL[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        while(!s.empty()) s.pop();

        // 右边第一个小值，正序，单调递增栈
        for(int i=0; i<size; i++) {
            while(!s.empty() && heights[i] < heights[s.top()]) {    // 单调递增栈
                rightL[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        int result = 0;
        for(int i=0; i<size; i++) {
            int h = heights[i];
            int w = rightL[i] - leftL[i] - 1;
            result = std::max(result, w * h);
        }

        return result;
    }
};


// 双指针优化 (不使用单调栈)
class Solution_D2_copy {
public:
    int largestRectangleArea(vector<int>& heights) {
        vector<int> minLeftIndex(heights.size());
        vector<int> minRightIndex(heights.size());
        int size = heights.size();

        // 记录每个柱子 左边第一个小于该柱子的下标
        minLeftIndex[0] = -1; // 注意这里初始化，防止下面while死循环            // 左边第一个较小值 *********
        for (int i = 1; i < size; i++) {
            int t = i - 1;
            // 这里不是用if，而是不断向左寻找的过程
            while (t >= 0 && heights[t] >= heights[i]) t = minLeftIndex[t];
            minLeftIndex[i] = t;
        }
        // 记录每个柱子 右边第一个小于该柱子的下标
        minRightIndex[size - 1] = size; // 注意这里初始化，防止下面while死循环  // 右边第一个较小值 *********
        for (int i = size - 2; i >= 0; i--) {
            int t = i + 1;
            // 这里不是用if，而是不断向右寻找的过程
            while (t < size && heights[t] >= heights[i]) t = minRightIndex[t];
            minRightIndex[i] = t;
        }
        // 求和
        int result = 0;
        for (int i = 0; i < size; i++) {
            int sum = heights[i] * (minRightIndex[i] - minLeftIndex[i] - 1);
            result = max(sum, result);
        }
        return result;
    }
};


// 单调栈
// 版本一
// 开头为什么要加元素 0？
// 如果数组本身是降序的，例如 [8,6,4,2]，在 8 入栈后，6 开始与 8 进行比较，此时我们得到 mid（8），rigt（6），但是得不到 left。
// （mid、left，right 都是对应版本一里的逻辑）
// 因为 将 8 弹出之后，栈里没有元素了，那么为了避免空栈取值，直接跳过了计算结果的逻辑。
// 之后又将 6 加入栈（此时 8 已经弹出了），然后 就是 4 与 栈口元素 8 进行比较，周而复始，那么计算的最后结果 resutl 就是 0。
class Solution_D3 {
public:
    int largestRectangleArea(vector<int>& heights) {
        int result = 0;
        stack<int> st;
        heights.insert(heights.begin(), 0); // 数组头部加入元素0，防止本身降序
        heights.push_back(0); // 数组尾部加入元素0，防止本身升序
        st.push(0);

        // 第一个元素已经入栈，从下标1开始
        for (int i = 1; i < heights.size(); i++) {
            if (heights[i] > heights[st.top()]) { // 情况一
                st.push(i);
            } else if (heights[i] == heights[st.top()]) { // 情况二
                st.pop(); // 这个可以加，可以不加，效果一样，思路不同
                st.push(i);
            } else { // 情况三
                while (!st.empty() && heights[i] < heights[st.top()]) { // 注意是while
                    int mid = st.top();
                    st.pop();
                    if (!st.empty()) {
                        int left = st.top();
                        int right = i;
                        int w = right - left - 1;
                        int h = heights[mid];
                        result = max(result, w * h);
                    }
                }
                st.push(i);
            }
        }
        return result;
    }
};


// 单调栈，精简版
// 版本二
class Solution_D4 {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        heights.insert(heights.begin(), 0); // 数组头部加入元素0
        heights.push_back(0); // 数组尾部加入元素0
        st.push(0);
        int result = 0;
        for (int i = 1; i < heights.size(); i++) {
            while (heights[i] < heights[st.top()]) {
                int mid = st.top();
                st.pop();
                int w = i - st.top() - 1;
                int h = heights[mid];
                result = max(result, w * h);
            }
            st.push(i);
        }
        return result;
    }
};
// 15:04--15:09--15:16(求size需要在添 0 之后)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        heights.insert(heights.begin(), 0); // 数组本身是单调递减的话，第一个数没法计算
        heights.push_back(0);               // 数组本身是单调递增的话，会将所有数字压入栈，不会计算面积了
        int size = heights.size();
        stack<int> s;
        int result = 0;
        for(int i=0; i<size; i++) {
            while(!s.empty() && heights[i] < heights[s.top()]) {    // 单调递增栈
                int mid = s.top();
                s.pop();
                int left = s.top();
                int right = i;
                int s = (right - left - 1) * heights[mid];
                if(s > result) result = s;
            }
            s.push(i);
        }
        return result;
    }
};






////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 左、右边第一个小值
// 左、右边第一个大值
// 左、右边最小值
// 左、右边最大值

// 这部分打算每个小部分用不同的方式实现，如暴力、单调栈、不带单调栈的跳转
// 这部分代码未调试，不知其正确性，且未完成
# if 1
// 左、右边第一个小值
// 单调栈
class Solution {
public:
    vector<int> nextSmallerElement(vector<int>& nums) {
        int size = nums.size();
        vector<int> leftL(size, -1);        // -1 左边没有更小的了
        vector<int> rightL(size, size);     // size 右边没有更小的了
        stack<int> s;

        // 左边第一个较小值，往左边找 倒序，单调递增栈 <
        for(int i=size-1; i>=0; i--) {
            while(!s.empty() && nums[i] < nums[s.top()]) {
                leftL[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        while(!s.empty()) s.pop();

        // 右边边第一个较小值，往右边找 正序，单调递增栈 <
        for(int i=0; i<size; i++) {
            while(!s.empty() && nums[i] < nums[s.top()]) {  // 单调递增栈
                rightL[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
    }
};

// 左、右边第一个大值
// 单调栈
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        int size = nums.size();
        vector<int> leftH(size, -1);        // -1左边没有更大的了
        vector<int> rightH(size, size);     // size 右边没有更大的了
        stack<int> s;

        // 左边第一个较大值，往左边找 倒序，单调递减栈
        for(int i=size-1; i>=0; i--) {
            while(!s.empty() && nums[i] > nums[s.top()]) {
                leftH[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }

        while(!s.empty()) s.pop();

        // 右边第一个较大值，往右边找 正序，单调递减栈
        for(int i=0; i<size; i++) {
            while(!s.empty() && nums[i] > nums[s.top()]) {
                rightH[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
    }
};


// 左、右边最小值
class Solution {
public:
    vector<int> nextSmallestElement(vector<int>& nums) {
        int size = nums.size();
        vector<int> leftS(size);
        vector<int> rightS(size);

        // 左边最小值，正序
        leftS[0] = nums[0]; // 左边第一个
        for(int i=1; i<size; i++) {
            leftS[i] = std::min(leftS[i-1], nums[i-1]);
        }

        // 右边最小值，倒序
        rightS[size-1] = nums[size-1];  // 右边第一个
        for(int i=size-2; i>=0; i--) {
            rightS[i] = std::min(rightS[i-1], nums[i-1]);
        }
    }
};

// 左、右最大值
class Solution {
public:
    int nextGreatestElement(vector<int>& nums) {
        int size = nums.size();
        vector<int> leftG(size);
        vector<int> rightG(size);

        // 左边最大值，正序
        leftG[0] = nums[0]; // 左边第一个
        for(int i=1; i<size; i++) {
            leftG[i] = std::max(leftG[i-1], nums[i-1]);
        }

        // 右边最大值，倒序
        rightG[size-1] = nums[size-1];  // 右边第一个
        for(int i=size-2; i>=0; i--) {
            rightG[i] = std::max(rightG[i-1], nums[i-1]);
        }
    }
};
#endif