// 42. 接雨水
// labuladong 题解思路
// 困难
// 给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

// 示例 1：
// 输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
// 输出：6
// 解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 

// 示例 2：
// 输入：height = [4,2,0,3,2,5]
// 输出：9

// 提示：
// n == height.length
// 1 <= n <= 2 * 10^4
// 0 <= height[i] <= 10^5

#include<iostream>
#include<vector>
#include<stack>
using std::stack;
using std::vector;
using std::max;
using std::min;

class Solution {
public:
    int trap(vector<int>& height) {

    }
};



// 15:41--15:50(读题找思路)--16:14--16:50(错误)
#if 0
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        vector<int> rightG(size, -1);
        stack<int> s;
        // 右侧第一个较大值
        for(int i=0; i<size; i++) {
            while(!s.empty() && height[i] > height[s.top()]) {
                rightG[s.top()] = i;
                s.pop();
            }
            s.push(i);
        }
        int result = 0;
        int left = 0;
        int right = 0;
        for(int i=0; i<size; i++) {
            if(rightG[i] == i + 1) continue;    // 相邻
            if(rightG[i] == -1) {
                while(i+1 < size && rightG[i+1] == -1) i++; // 后面连续 -1，i指向不是 -1 的前一个
                if(i == size -1) break;
                int j = i + 1;
                if(j < size && rightG[j] != -1) j++;        // j 指向下一个 -1，rightG最后一个一定是 -1，所以这里 j 一定不是末尾，否则早就 break 了
                int h = std::min(height[i], height[j]);
                for(int k=i+1; k<j; k++) {
                    result += h - height[k];
                }
                while(j+1 < size && rightG[j+1] == -1) i++;
                left = height[j];
            }
            else {
                int h = std::min(height[i], height[rightG[i]]);
                for(int k=i+1; k<rightG[i]; k++) {
                    result += h - height[k];
                }
                i = rightG[i] - 1;
            }
        }
        return result;
    }
};
#endif


// 暴力解法：超时
// 每个主子左侧最高和右侧最高
class Solution_D1_copy {
public:
    int trap(vector<int>& height) {
        int sum = 0;
        for (int i = 0; i < height.size(); i++) {
            // 第一个柱子和最后一个柱子不接雨水
            if (i == 0 || i == height.size() - 1) continue;

            int rHeight = height[i]; // 记录右边柱子的最高高度
            int lHeight = height[i]; // 记录左边柱子的最高高度
            for (int r = i + 1; r < height.size(); r++) {
                if (height[r] > rHeight) rHeight = height[r];
            }
            for (int l = i - 1; l >= 0; l--) {
                if (height[l] > lHeight) lHeight = height[l];
            }
            int h = std::min(lHeight, rHeight) - height[i];
            if (h > 0) sum += h;    // 不会出现 小于0 的情况，因此这一步是多余的
        }
        return sum;
    }
};




// 双指针法
class Solution_D1_M1 {
public:
    int trap(vector<int>& height) {
        int result = 0;
        int left = 0;
        int right = 0;
        for(int i=1; i<height.size()-1; i++) {  // 头尾接不了水
            left = height[i];   // 记录右边柱子的最高高度
            right = height[i];  // 记录左边柱子的最高高度
            for(int j = i-1; j>=0; j--) {
                if(height[j] > left) left = height[j];
            }
            for(int j=i+1; j<height.size(); j++) {
                if(height[j] > right) right = height[j];
            }
            result += std::min(left, right) - height[i];

        }
        return result;
    }
};

// --18:17
// 双指针优化，求最高的高度过程可以用数组记录
// 看到 D2 中上面这句话后尝试写
// 错了两处
class Solution_D2_M2 {
public:
    int trap(vector<int>& height) {

        vector<int> leftH(height.size(), 0);
        vector<int> rightH(height.size(), 0);
        // 记录每个柱子左边柱子最大高度
        leftH[0] = height[0];
        for(int i=1; i<height.size(); i++) {
            leftH[i] = leftH[i-1] > height[i-1] ? leftH[i-1] : height[i-1]; // height[i]本身没有参与比较
        }
        // 记录每个柱子右边柱子最大高度
        rightH.back() = height.back();
        for(int i=height.size()-2; i>=0; i--) { // i--          // ***
            rightH[i] = rightH[i+1] > height[i+1] ? rightH[i+1] : height[i+1];  // height[i]本身没有参与比较
        }
        // 求和
        int result = 0;
        for(int i=1; i<height.size()-1; i++) {  // 首尾接不了水
            // 这里不能保证 min(leftH[i], rightH[i]) >= height[i]，所以需要加个判断
            int h = std::min(leftH[i], rightH[i]) - height[i];  // ***
            if(h > 0) result += h;
        }

        return result;
    }
};

// 双指针优化
class Solution_D2_copy {
public:
    int trap(vector<int>& height) {
        if (height.size() <= 2) return 0;
        vector<int> maxLeft(height.size(), 0);
        vector<int> maxRight(height.size(), 0);
        int size = maxRight.size();

        // 记录每个柱子左边柱子最大高度
        maxLeft[0] = height[0];
        for (int i = 1; i < size; i++) {
            maxLeft[i] = max(height[i], maxLeft[i - 1]);
        }
        // 记录每个柱子右边柱子最大高度
        maxRight[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--) {
            maxRight[i] = max(height[i], maxRight[i + 1]);  // height[i] 本身参与比较，保证 maxRight[i] >= height[i]
        }
        // 求和
        int sum = 0;
        for (int i = 0; i < size; i++) {
            int count = min(maxLeft[i], maxRight[i]) - height[i];
            // 上面的判断可以保证 maxLeft[i] maxRight[i] 都大于等于 height[i]
            if (count > 0) sum += count;        // 判断可以去掉     // ***
        }
        return sum;
    }
};



// 21:19--21:30--21:46(写错)--22:00
// 看过 D3 关于单调栈的图
class Solution {
public:
    int trap(vector<int>& height) {
        int size = height.size();
        stack<int> s;
        int result = 0;
        for(int i=0; i<size; i++) {
            while(!s.empty() && height[i] > height[s.top()]) {
                int mid = s.top();
                s.pop();
                if(!s.empty()) {    // 两高夹一矮，有凹槽
                    int h = std::min(height[s.top()], height[i]) - height[mid];
                    result += h * (i - s.top() - 1);
                }
            }
            s.push(i);
        }
        return result;
    }
};