#include <iostream>
#include <vector>
#include <string>

using namespace std;

#if 1

// 1480. 一维数组的动态和
#if 1
vector<int> runningSum(vector<int>& nums)
{
    int count = nums.size();
    for(int i=1; i<count; ++i)
        nums[i] += nums[i-1];
    return nums;
}
#endif

// 383.  赎金信
#if 1
bool canConstruct(string ransomNote, string magazine)
{
    if (ransomNote.size() > magazine.size())
        return false;
    vector<int> count(26, 0);
    // int count[26] = {0}
    for (auto & c : magazine)
        count[c - 'a']++;           // 两个 char 的差值可作为数组的索引
    for (auto & c : ransomNote)
    {
        count[c - 'a']--;
        if (count[c - 'a'] < 0)
            return false;
    }
    return true;
}
#endif

// 412.  Fizz Buzz
// 给你一个整数 n ，找出从 1 到 n 各个整数的 Fizz Buzz 表示，
// 并用字符串数组 answer（下标从 1 开始）返回结果，其中：
// answer[i] == "FizzBuzz" 如果 i 同时是 3 和 5 的倍数。
// answer[i] == "Fizz" 如果 i 是 3 的倍数。
// answer[i] == "Buzz" 如果 i 是 5 的倍数。
// answer[i] == i （以字符串形式）如果上述条件全不满足。
#if 1
vector<string> fizzBuzz(int n)
{
    vector<string> results(n);
    for(int i=1; i<=n; i++)
    {

        if(i%15 == 0)
            results[i-1] = "FizzBuzz";
        else if(i%3 == 0)
            results[i-1] = "Fizz";
        else if(i%5 == 0)
            results[i-1] = "Buzz";
        else
            results[i-1] = to_string(i);    // 将 int转换为 string
    }
    return results;
}

vector<string> fizzBuzz2(int n)
{
    vector<string> answer;
    for (int i = 1; i <= n; i++)
    {
        string curr;
        if (i % 3 == 0) {
            curr += "Fizz";     // += 有前提
        }
        if (i % 5 == 0) {
            curr += "Buzz";
        }
        if (curr.size() == 0) {
            curr += to_string(i);
        }            
        answer.emplace_back(curr);
    }
    return answer;
}
#endif

// 876. 链表的中间结点
// 题目：
// 给定一个头结点为 head 的非空单链表，返回链表的中间结点。
// 如果有两个中间结点，则返回第二个中间结点。
// Definition for singly-linked list.
// struct ListNode {
//     int val;
//     ListNode *next;
//     ListNode() : val(0), next(nullptr) {}
//     ListNode(int x) : val(x), next(nullptr) {}
//     ListNode(int x, ListNode *next) : val(x), next(next) {}
// };
// 
// 解题思路：
// 方法一：用空间换时间
// 首先遍历一遍单链表，记录链表的长度 len，计算中间节点的位置。 
// 即开辟一个数组，记录所有节点，最后返回 arr[len/2] 的节点即可
// 
// 方法二：用时间换空间 —— 再次遍历链表，遍历到 len/2 次时返回当前节点记为中间节点。
// 利用快慢指针，快指针每次走两步，慢指针每次走一步，所以快指针走的距离为慢指针的两倍，
// 故当快指针遍历到链表末尾时，慢指针指向记为中间节点
#if 1
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr)  {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next)    {}
};

// 空间换时间：数组一次遍历
ListNode* middleNode(ListNode* head)
{
    vector<ListNode*> addrlist = {head};   // 存储所有的节点地址
    while (addrlist.back()->next != nullptr)    // vector.back(): 访问vector最后一个元素
        addrlist.push_back(addrlist.back()->next);
    return addrlist[addrlist.size() / 2];
    // 如果有4个，返回 addrlist[2]是第三个元素
    // 如果有3个，返回 addrlist[1]是第二个元素
    // 返回左边的中间值：
    // return addrlist[(addrlist.size() - 1) / 2]
}

// 时间换空间
// 单指针两次遍历
ListNode * middleNode2(ListNode * head)
{
    int count = 0;
    ListNode * current = head;
    while(current != nullptr)   // 一次遍历计数
    {
        count++;
        current = current->next;
    }
    int n = 0;
    current = head;
    while(n < count/2)          // 二次遍历找中间
    {
        n++;
        current = current->next;
    }
    // 返回左边的中间值：
    // while(n < (count-1)/2)
    return current;
}
// 双指针一次遍历，快慢指针
ListNode * middleNode3(ListNode * head)
{
    ListNode * slow = head;
    ListNode * fast = head;
    while(fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    // 返回左边的中间值：
    // while(fast->next != nullptr && fast->next->next != nullptr)
    return slow;
}
#endif

// 1342. 将数字变成 0 的操作次数
// 题目：
// 给你一个非负整数 num ，请你返回将它变成 0 所需要的步数。 
// 如果当前数字是偶数，你需要把它除以 2 ；否则，减去 1 。
// 思路：
// 当 num>0 时，总操作次数等于总减 1 的操作数与总除以 2 的操作数之和。
// 总减 1 的操作数等于 num 二进制位 1 的个数，
// 总除以 2 的操作数等于 num 二进制数长度减 1，即最高位右移到最低位的距离。
#if 1
// 简单计算
int numberOfSteps(int num)
{
    int steps = 0;
    while(num)
    {
        ++steps;
        if(num%2 == 0)
            num/=2;
        else
            num-=1;
    }
    return steps;
}

// 模拟
int numberOfSteps2(int num)
{
    int steps = 0;
    while(num)
    {
        steps+=(num>1 ? 1 : 0) + (num & 0x01);
        num>>=1;
        // (num>1 ? 1 : 0) 偶数除二的次数减一
        // (num & 0x01) 奇数减一的次数
    }
    return steps;
}

// 直接计算
class Solution {
// 二分法加速求解前导零数目：
// 首先判断num前半部分是否全为零，如果是，则将clz加上前半部分的长度，然后将后半部分作为处理
// 对象，否则将前半部分作为处理对象。重复以上操作直到处理的对象长度为1，直接判断是否有零，有
// 则将clz加 1。
    int length(unsigned int num) {
        unsigned int clz = 0;
        if ((num >> 16) == 0) {
            clz += 16;
            num <<= 16;
        }
        if ((num >> 24) == 0) {
            clz += 8;
            num <<= 8;
        }
        if ((num >> 28) == 0) {
            clz += 4;
            num <<= 4;
        }
        if ((num >> 30) == 0) {
            clz += 2;
            num <<= 2;
        }
        if ((num >> 31) == 0) {
            clz += 1;
        }
        return 32 - clz;
    }

// 分治法来加速求解二进制数位 1 的个数: https://zhuanlan.zhihu.com/p/147862695
// 对二进制数num,它的位1的个数等于所有位的值相加的结果,比如101101012)=1+0+1+1+
// 0+1+0+1.我们可以将8个位的求和分解成4个相邻的位的求和,然后将4个中间结果分解成2个
// 相邻的求和,即10110101(2)=(1+0)+(1+1)+(0+1)+(0+1)=((1+0)+(1+1))+((0+1)+
// (0+1))=5.32位数的求解过程同理.
    int count(int num) {
        num = (num & 0x55555555) + ((num >> 1) & 0x55555555);   // 5 = 0101
        num = (num & 0x33333333) + ((num >> 2) & 0x33333333);   // 3 = 0011
        num = (num & 0x0F0F0F0F) + ((num >> 4) & 0x0F0F0F0F);   // 0F = 00001111
        num = (num & 0x00FF00FF) + ((num >> 8) & 0x00FF00FF);
        num = (num & 0x0000FFFF) + ((num >> 16) & 0x0000FFFF);
        return num;
    }

    int numberOfSteps(int num) {
        return num == 0 ? 0 : length(num) - 1 + count(num);
    }
};
#endif

// 1672. 最富有客户的资产总量
// 给你一个 m x n 的整数网格 accounts
// 其中 accounts[i][j] 是第 i​​​​​​​​​​​​ 位客户在第 j 家银行托管的资产数量。返回最富有客户所拥有的 资产总量 。
// 客户的资产总量就是他们在各家银行托管的资产数量之和。最富有客户就是资产总量最大的客户。
#if 1
// 手工遍历
int maximumWealth(vector<vector<int>>& accounts)
{
    int max = 0;
    int num = accounts.size();
    for(int i=0; i<num; i++)
    {
        int sum = INT_MIN;  // int 的最小值，因为有人会有负债
        int length = accounts[i].size();
        for(int j=0; j<length; j++)
        {
            sum += accounts[i][j];
        }
        if(sum > max)
            max = sum;
    }
    return max;
}

// 调用函数
#include <algorithm>    // max(), min()
#include <numeric>      // accumulate()
// accumulate(A.begin(), A.end(), 0)    // 从 begin() 累加到 end(), 累加初始值为 0
// accumulate(A.begin(), A.begin()+n, 0);
int maximumWealth2(vector<vector<int>>& accounts) {
    int maxWealth = INT_MIN;
    for (auto &account : accounts) {
        maxWealth = max(maxWealth, accumulate(account.begin(), account.end(), 0));
    }
    return maxWealth;
}
#endif



#endif