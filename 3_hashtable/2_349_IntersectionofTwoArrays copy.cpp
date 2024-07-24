// 349. 两个数组的交集
// 题意：给定两个数组，编写一个函数来计算它们的交集。

#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

// std::set 和 std::multiset 底层实现都是红黑树，
// std::unordered_set 的底层实现是哈希表， 
// 使用 unordered_set 读写效率是最高的，并不需要对数据进行排序，而且还不要让数据重复，
// 所以选择 unordered_set。
// #1 两个都存到 unordered_set 中比较得结果
// #2 一个存到 unordered_set 中另一个比较
// #3 限定数组元素大小时可用数组做 hash表
vector<int> intersection_D1(vector<int> & nums1, vector<int> & nums2)
{
    // unordered_set 与 vector 相互赋值的方法
    // hash表，num1 去重，如果限定 nums1，nums2小于等于1000，则可用数组做 hash表
    unordered_set<int> nums_set(nums1.begin(), nums2.end());
    unordered_set<int> result_set;  // 存放并集
    for(int & i : nums2)
    {
        if(nums_set.count(i))
            result_set.insert(i);
    }
    return vector<int>(result_set.begin(), result_set.end());
}

vector<int> intersection_D1_2(vector<int> & nums1, vector<int> & nums2)
{
    unordered_set<int> result_set;
    int hash[1000] = {0};
    for(int i : nums1)
        hash[i] = 1;
    for(int i : nums2)
    {
        if(hash[i])
            result_set.insert(i);
    }
    return vector<int>(result_set.begin(), result_set.end());
}

// 排序后用双指针
// . 时间复杂度: O(mlogm+nlogn),其中m和n分别是两个数组的长度.
//   对两个数组排序的时间复杂度分别是O(mlogm)和O(n logn),
//   双指针寻找交集元素的时间复杂度是O(m+n),因此总时间复杂度是 O(m log m + n log n).
// · 空间复杂度: O(logm+logn),其中m和n分别是两个数组的长度.
// 空间复杂度主要取决于排序使用的额外空间.
vector<int> intersection_G1(vector<int> & nums1, vector<int> & nums2)
{
    // 排序
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    int length1 = nums1.size();
    int length2 = nums2.size();
    int index1  = 0;
    int index2  = 0;
    int num1, num2;
    // 双指针查找
    vector<int> result;
    while(index1 < length1 && index2 < length2)
    {
        num1 = nums1[index1];
        num2 = nums2[index2];
        if(num1 == num2)
        {
            if(!result.size() || num1 != result.back()) // 保证唯一性
                result.push_back(num1);                 // 有序数组才有用
            index1++;
            index2++;
        }
        else if(num1 < num2)
            index1++;
        else
            index2++;
    }
    return result;
}


vector<int> intersection_G1_2(vector<int> & nums1, vector<int> & nums2)
{
    // 排序
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    int length1 = nums1.size();
    int length2 = nums2.size();
    int index1  = 0;
    int index2  = 0;
    int num1, num2;
    // 双指针查找
    vector<int> result;
    while(index1 < length1 && index2 < length2)
    {
        num1 = nums1[index1];
        num2 = nums2[index2];
        if(num1 == num2)
        {
            result.push_back(num1);
            while(index1 < length1 && (num1==nums1[index1])) index1++;    // 找下一个不同的值
            while(index2 < length2 && (num2==nums2[index2])) index2++;
        }
        else if(num1 < num2)
            while(index1 < length1 && (num1==nums1[index1])) index1++;
        else
            while(index2 < length2 && (num2==nums2[index2])) index2++;
    }
    return result;
}