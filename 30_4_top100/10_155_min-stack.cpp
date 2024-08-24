// https://leetcode.cn/problems/min-stack/submissions/557035267/
// 155. 最小栈
// 已解答
// 中等
// 相关标签
// 相关企业
// 提示
// 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

// 实现 MinStack 类:

// MinStack() 初始化堆栈对象。
// void push(int val) 将元素val推入堆栈。
// void pop() 删除堆栈顶部的元素。
// int top() 获取堆栈顶部的元素。
// int getMin() 获取堆栈中的最小元素。
 

// 示例 1:

// 输入：
// ["MinStack","push","push","push","getMin","pop","top","getMin"]
// [[],[-2],[0],[-3],[],[],[],[]]

// 输出：
// [null,null,null,null,-3,null,0,-2]

// 解释：
// MinStack minStack = new MinStack();
// minStack.push(-2);
// minStack.push(0);
// minStack.push(-3);
// minStack.getMin();   --> 返回 -3.
// minStack.pop();
// minStack.top();      --> 返回 0.
// minStack.getMin();   --> 返回 -2.
 

// 提示：

// -231 <= val <= 231 - 1
// pop、top 和 getMin 操作总是在 非空栈 上调用
// push, pop, top, and getMin最多被调用 3 * 104 次


#include<iostream>
#include<stack>
using namespace std;


class MinStack {
public:
    MinStack() {

    }
    
    void push(int val) {

    }
    
    void pop() {

    }
    
    int top() {

    }
    
    int getMin() {

    }
};




// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

// 原始思路
class MinStack_L1 {
    // 记录栈中的所有元素
    stack<int> stk;
    // 阶段性记录栈中的最小元素
    stack<int> minStk;

public:
    void push(int val) {
        stk.push(val);
        // 维护 minStk 栈顶为全栈最小元素
        if (minStk.empty() || val <= minStk.top()) {
            // 新插入的这个元素就是全栈最小的
            minStk.push(val);
        } else {
            // 插入的这个元素比较大
            minStk.push(minStk.top());
        }
    }
    
    void pop() {
        stk.pop();
        minStk.pop();
    }
    
    int top() {
        return stk.top();
    }
    
    int getMin() {
        // minStk 栈顶为全栈最小元素
        return minStk.top();
    }
};

// 优化版
class MinStack_L2 {
    // 记录栈中的所有元素
    stack<int> stk;
    // 阶段性记录栈中的最小元素
    stack<int> minStk;

public:
    void push(int val) {
        stk.push(val);
        // 维护 minStk 栈顶为全栈最小元素
        if (minStk.empty() || val <= minStk.top()) {
            // 新插入的这个元素就是全栈最小的
            minStk.push(val);
        }
    }

    void pop() {
        // 注意 Java 的语言特性，比较 Integer 相等要用 equals 方法
        if (stk.top() == minStk.top()) {
            // 弹出的元素是全栈最小的
            minStk.pop();
        }
        stk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        // minStk 栈顶为全栈最小元素
        return minStk.top();
    }
};