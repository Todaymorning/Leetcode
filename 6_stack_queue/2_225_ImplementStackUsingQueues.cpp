// 225. 用队列实现栈
// 使用队列实现栈的下列操作：
// push (x) -- 元素 x 入栈
// pop () -- 移除栈顶元素
// top () -- 获取栈顶元素
// empty () -- 返回栈是否为空

// 注意:
// 你只能使用队列的基本操作 -- 也就是 push to back, peek/pop from front, size, 和 is empty 这些操作是合法的。
// 你所使用的语言也许不支持队列。 你可以使用 list 或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。
// 你可以假设所有操作都是有效的（例如，对一个空的栈不会调用 pop 或者 top 操作）。


// 队列模拟栈，一个队列就够了
// 用两个队列实现，另一个队列用来备份用
// 栈实现队列：先进后出变为先进先出，有一个栈用来倒序 in out
// 队列实现栈：先进先出变为先进后出，有一个队列用来倒序

// C++ queue背景知识
// queue 默认是由 dequeue实现，和stack一样也是容器适配器
// 
// queue<int, dqueue<int>>
// push
// pop
// front
// back
// size
// empty

# include<iostream>
# include<queue>
using std::queue;


// 使用两个队列，一个队列当作备份
class MyStack_D1
{
public:
    queue<int> queue1;  // 与外界沟通进出
    queue<int> queue2;  // 辅助队列，用来备份及倒序
    MyStack_D1(){}
    void push(int x)
    {
        queue1.push(x);
    }

    int pop()   // 注意标准的queue.pop()没有返回值
    {
        int size = queue1.size();   // 还有多少元素
        size--;
        while(size--)   // 将queue1导入queue2，但留下最后一个元素pop
        {
            queue2.push(queue1.front());
            queue1.pop();
        }
        int result = queue1.front();
        queue1.pop();
        queue1 = queue2; // 恢复queue1
        while(!queue2.empty())  // 清空queue2
        {
            queue2.pop();
        }
        return result;
    }

    int top()
    {
        return queue1.back();
    }

    bool empty()
    {
        return queue1.empty();
    }
};


// 用一个队列
// 一个队列在模拟栈弹出元素的时候只要将队列头部的元素（除了最后一个元素外）
// 重新添加到队列尾部，此时再去弹出元素就是栈的顺序了。
class MyStack_D2
{
public:
    queue<int> q;
    MyStack_D2() {}

    void push(int x)
    {
        q.push(x);
    }

    int pop()
    {
        int size = q.size();
        size--;     // queue尾进头出，可以自己调个头：队首自觉去到队尾
        while(size--)
        {
            q.push(q.front());
            q.pop();
        }
        int result = q.front();
        q.pop();
        return result;
    }

    int top()
    {
        return q.back();
    }

    bool empty()
    {
        return q.empty();
    }
};

int main()
{
    return 0;
}