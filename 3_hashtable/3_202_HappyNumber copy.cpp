// 编写一个算法来判断一个数 n 是不是快乐数。
// 「快乐数」定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，
// 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
// 如果 可以变为  1，那么这个数就是快乐数。
// 如果 n 是快乐数就返回 True ；不是，则返回 False 。

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// 哈希集合
// 复杂度分析较难
// 时间复杂度：O(常数 + log n + log log n + log log log n...)= O(log n).
// 空间复杂度:　O(logn).
int getSum(int n)
{
    int sum = 0;
    while(n)
    {
        sum += (n % 10) * (n % 10);
        n /= 10;
    }
    return sum;
}
bool isHappy_G1(int n)
{
    unordered_set<int> seen;
    // 等于 1 和 出现重复值是跳出循环的条件
    while( (n != 1) && (seen.count(n) == 0) )
    {
        seen.insert(n);
        n = getSum(n);
    }
    return n == 1;
}

// 快慢指针:
// 如果 n是一个快乐数，即没有循环，那么快跑者最终会比慢跑者先到达数字 1。
// 如果 n不是一个快乐数，那么最终快跑者和慢跑者将在同一个数字上相遇。
// 时间复杂度: O(logn)
// 空间复杂度: O(1)
bool isHappy_G2(int n)
{
    int slow = n;
    int fast = getSum(n);   // 防止不进入循环
    // 等于 1 和 出现重复值是跳出循环的条件
    while(fast != 1 && slow != fast)
    {
        slow = getSum(slow);
        fast = getSum(getSum(fast));
    }
    return fast==1;
}
