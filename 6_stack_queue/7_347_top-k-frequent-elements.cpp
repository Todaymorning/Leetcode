// 347. 前 K 个高频元素
// 给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

// 示例 1:
// 输入: nums = [1,1,1,2,2,3], k = 2
// 输出: [1,2]

// 示例 2:
// 输入: nums = [1], k = 1
// 输出: [1]

// 提示：
// 1 <= nums.length <= 105
// 你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
// 你的算法的时间复杂度必须优于 O(nlog n), n 是数组的大小。
// 题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的。
// 你可以按任意顺序返回答案


// 背景知识：
// 优先级队列 priority_queue (#include <queue>),披着队列外衣的堆
// priority_queue 是容器适配器
// 缺省的情况下用大顶堆，也可以指定用小顶堆
// 堆是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。 如果父亲结点是大于等于左右孩子就是大顶堆，小于等于左右孩子就是小顶堆。
// 完全二叉树、满二叉树、堆


// 思路：
// 1.
// 用 unordered_map统计元素的频率
// 使用底层是小顶堆的优先级队列 priority_queue 维护前 k个高频元素
// 输出
// 时间复杂度: O(nlogk)
// 空间复杂度: O(n)

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using std::vector;
using std::unordered_map;
using std::priority_queue;
using std::pair;


// 优先级队列
class Solution_D1 {
    // 自定义比较函数类
    class mycompare {
    public:
        bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
            return a.second > b.second; // 构造小顶堆，这里使用 >
        }
    };
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 统计频率
        unordered_map<int, int> map;
        for(auto num:nums) {
            map[num]++;
        }
        
        // 构造小顶堆
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> pri_que;
        // 第一个参数 pair<int, int> 是该堆存储元素的类型。
        // 第二个参数 vector<pair<int, int>> 是底层容器的类型。
        // 第三个参数 mycompare 是用于比较元素的自定义比较函数对象。该对象必须实现一个 operator() 函数，并且按照指定的顺序比较两个元素。
        // static bool cmp (pair<int, int>& m, pair<int, int>& n) {
        //     return m.second > n.second;}
        // priority_queue<pair<int, int>, vector<pair<int, int>>, decltype (&cmp)> pri_que(cmp);
        
        // 用固定大小为 k的小顶堆，扫描所有频率的数值
        // unordered_map<int, int>::iterator
        for (auto it = map.begin(); it!=map.end(); it++) {
            pri_que.push(*it);
            if(int(pri_que.size()) > k) {
                pri_que.pop();  // 弹出最小频率，保证小顶堆中剩下的都是比较大的频率
            }
        }

        // 返回前 k个高频元素
        vector<int> result(k, 0);
        for(int i=k; i>0; i--) {    // 因为每次top都是最小频率，所以需要反序
            result[i-1] = pri_que.top().first;
            pri_que.pop();
        }
        return result;
    }
};