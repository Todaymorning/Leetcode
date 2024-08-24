// 739. 每日温度
// labuladong 题解
// 中等
// 给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中 answer[i] 是指对于第 i 天，
// 下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用 0 来代替。

// 示例 1:
// 输入: temperatures = [73,74,75,71,69,72,76,73]
// 输出: [1,1,4,2,1,1,0,0]

// 示例 2:
// 输入: temperatures = [30,40,50,60]
// 输出: [1,1,1,0]

// 示例 3:
// 输入: temperatures = [30,60,90]
// 输出: [1,1,0]

// 提示：
// 1 <= temperatures.length <= 10^5
// 30 <= temperatures[i] <= 100

#include<iostream>
#include<vector>
#include<stack>
using std::stack;
using std::vector;


class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        
    }
};


// 17:00--17:02(读题找思路)--17:18(M1, M2)(超出时间限制)
// 暴力解法
class Solution_M1 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        for(int i=0; i<temperatures.size() - 1; i++) {  // 直到倒数第二天
            int j = i+1;    // 从下一天开始
            while(j<temperatures.size() && temperatures[j] <= temperatures[i]) {
                j++;
            }
            if(j == i + 1) {
                if(temperatures[j] > temperatures[i]) result[i] = 1;
                else result[i] = 0;
            }
            else if(j < temperatures.size()) {  // j 每超出索引
                result[i] = j - i;
            }
            // j 超出索引 result[i] = 0;
        }
        return result;
    }
};

// 上面的逻辑有点繁琐，简化如下
class Solution_M2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        for(int i=0; i<temperatures.size(); i++) {  // 直到最后一天
            int j = i;  // 从当天开始
            while(j<temperatures.size() && temperatures[j] <= temperatures[i]) {
                j++;
            }
            if(j < temperatures.size()) {  // j 每超出索引
                result[i] = j - i;
            }
            // j 超出索引 result[i] = 0;
        }
        return result;
    }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 单调栈
// 17:20--10:53(看过 D1 的思路后开写)--10:59--11:08(改符号)
// temperatures = [73, 74, 75, 71, 71, 72, 76, 73]
// i=1, s:0,    s.top()=0, t[1]=74 >  t[0]=73, result[0]=1-0=1, 弹出0，压入1
// i=2, s:1,    s.top()=1, t[2]=75 >  t[1]=74, result[1]=2-1=1，弹出1，压入2
// i=3, s:2,    s.top()=2, t[3]=71 <= t[2]=75, 压入3
// i=4, s:2 3,  s.top()=3, t[4]=71 <= t[3]=71, 压入4
// i=5, s:2 3 4,s.top()=4, t[5]=72 >  t[4]=71, result[4]=5-4=1, 弹出4
// i=5, s:2 3,  s.top()=3, t[5]=72 >  t[3]=71, result[3]=5-3=2, 弹出3
// i=5, s:2,    s.top()=2, t[5]=72 <= t[2]=75, 压入5
// i=6, s:2,5   s.top()=5, t[6]=76 >  t[5]=72, result[5]=6-5=1, 弹出5
// i=6, s:2,    s.top()=2, t[6]=76 >  t[2]=75, result[2]=6-2=4, 弹出2，压入6
// i=7, s:6,    s.top()=6, t[7]=73 <= t[6]=76, 压入7


class Solution_D1 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        stack<int> stk;
        stk.push(0);
        for(int i=1; i<temperatures.size(); i++) {
            if(temperatures[i] > temperatures[stk.top()]) {
                while(!stk.empty() && temperatures[i] > temperatures[stk.top()]) { // 栈内单调递减
                    result[stk.top()] = i - stk.top();
                    stk.pop();
                }
                stk.push(i);
            }
            else {
                stk.push(i);
            }
        }
        return result;
    }
};

// 简化
class Solution_D2 {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> result(temperatures.size(), 0);
        stack<int> stk;
        stk.push(0);
        for(int i=1; i<temperatures.size(); i++) {
            while(!stk.empty() && temperatures[i] > temperatures[stk.top()]) { // 栈内单调递减
                result[stk.top()] = i - stk.top();
                stk.pop();
            }
            stk.push(i);
        }
        return result;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 右边第一个大值的索引，不使用栈，只用数组保存
// 启发自 5_84
class Solution_no_stack1 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> result(size, -1);   // 右边找不到更大的置 -1
        // i 从倒数第二项开始遍历，最后一位肯定为 -1
        for(int i=size-2; i>=0; i--) {  // 倒序遍历
            int t = i+1;
            while(t != -1 && t<size && nums[t] <= nums[i]) t = result[t];
            result[i] = t;
        }
        return result;
    }
};

class Solution_no_stack2 {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> result(size);   // 不需要初始化
        result[size-1] = -1;    // 右边找不到更大的置 -1
        // i 从倒数第二项开始遍历
        for(int i=size-2; i>=0; i--) {  // 倒序遍历
            int t = i+1;    // 从右边一位开始找
            while(t != -1 && t<size && nums[t] <= nums[i]) t = result[t];
            // 解释 while
            // t != -1 是在执行过一次 t=result[t] 才需要用到的，防止向右跳过头了
            // result[t]中存着t处右侧第一个较大值的索引，t=result[t]是为了向右跳转，是为了找下一个更大的值与当前值比较
            // t<size 是为了限制向右跳过头了，这里其实不需要，这么写只是为了逻辑清晰
            // nums[t] <= nums[i]，当右边的值不是大值的时候需要继续向右跳转
            result[i] = t;  // 找到了与当前值相比较大的值 或者没找到 -1
        }
        return result;
    }
};





class Solution_M3 {
public:
    vector<int> dailyTemperatures(vector<int>& nums) {

        ///////////////////////////////////////////////////////////////////////////////
        int size = nums.size();
        vector<int> result(size, -1);
        // i 从倒数第二项开始遍历，最后一位肯定为 -1
        for(int i=size-2; i>=0; i--) {  // 倒序遍历
            int t = i+1;
            while(t != -1 && t<size && nums[t] <= nums[i]) t = result[t];
            result[i] = t;   //  == size ? -1 : t; // 右边第一个大值，如果没有的话，一直会跳转遍历到 size
        }
        ///////////////////////////////////////////////////////////////////////////////
        
        for(int i=0; i<size; i++) {
            if(result[i] != -1) result[i] = result[i] - i;
            else result[i] = 0;
        }

        return result;
    }
};


// 2024年8月1日
// 21:58--22:06
// 知道用单调栈，尝试自己写出来
// 栈内减小
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        vector<int> res(temperatures.size(), 0);
        stack<int> stk;
        for(int i=0; i<temperatures.size(); i++) {
            while(!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                res[stk.top()] = i - stk.top(); // 几天后 i - stk.top()
                stk.pop();
            }
            stk.push(i);
        }
        return res;
    }
};