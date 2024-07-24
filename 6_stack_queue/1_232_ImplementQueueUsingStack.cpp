// 232. 用栈实现队列
// 使用栈实现队列的下列操作：
// push (x) -- 将一个元素放入队列的尾部。
// pop () -- 从队列首部移除元素。
// peek () -- 返回队列首部的元素。
// empty () -- 返回队列是否为空


// C++ stack 预备知识
// 容器适配器，
// empty(): 返回布尔值，表示栈是否为空。true，false。
// size(): 返回整数，表示栈中元素的数量。
// top(): 返回栈顶元素的引用。注意，如果栈为空，调用 top() 方法将导致未定义行为。因此，在调用 top() 方法之前，最好先使用 empty() 方法检查栈是否为空。
// push(const T& value): 无返回值。将给定的值 value 压入栈顶。
// pop(): 无返回值。弹出（删除）栈顶元素。注意，如果栈为空，调用 pop() 方法将导致未定义行为。因此，在调用 pop() 方法之前，最好先使用 empty() 方法检查栈是否为空。

#include <iostream>
#include <stack>
class MyQueue_D1
{
public:
    std::stack<int> stackIn;
    std::stack<int> stackOut;

    MyQueue_D1()
    {

    }

    void push(int x)
    {
        stackIn.push(x);
    }

    int pop()   // 使用前需判断是否为空
    {
        // 只有当stackOut为空的时候才从stackIn中导入数据
        if(stackOut.empty())
        {
            while(!stackIn.empty())
            {
                stackOut.push(stackIn.top());
                stackIn.pop();  // pop返回值为空
            }
        }
        int result = stackOut.top();
        stackOut.pop();
        return result;
    }

    int peek()
    {
        // 直接使用已有函数
        int result = this->pop();
        stackOut.push(result);
        return result;
    }

    bool empty()
    {
        return stackIn.empty() && stackOut.empty();
    }

};

int main()
{
    std::stack<int> st;
    st.push(10086);
    std::cout << st.size() << std::endl;    // 1
    std::cout << st.top() << std::endl;     //10086
    st.pop();   // 正常
    std::cout << st.size() << std::endl;    // 0
    // 当堆栈为空的时候使用 top()直接报错。
    // std::cout << st.top() << std::endl;     // 直接报错
    st.pop();   // 未定义行为，应该先判断是否为空
    std::cout << st.size() << std::endl;    // 18446744073709551615
    st.pop();   // 未定义行为，应该先判断是否为空
    std::cout << st.size() << std::endl;    // 18446744073709551614
    return 0;
}
