// #1. 两数之和
// 给定一个整数数组 nums 和一个目标值 target，
// 请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
// 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

///映射	     底层实现   是否有序	数值是否可以重复  能否更改数值	查询效率   增删效率
//map	      红黑树    key有序	    key不可重复	    key不可修改	  O(log n)	O(log n)
//multimap	  红黑树    key有序	    key可重复	    key不可修改	  O(log n)	O(log n)
//unordered_map 哈希表  key无序	    key不可重复	    key不可修改	  O(1)	    O(1)

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 暴力枚举
// 枚举数组中的每一个数x，寻找数组中是否存在 target-x
// 当我们使用遍历整个数组的方式寻找 target-x 时,需要注意到每一个位于 x 之前的元素
// 都已经和 x 匹配过,因此不需要再进行匹配.而每一个元素不能被使用两次,所以我们只需
// 要在 x 后面的元素中寻找 target-x.
// . 时间复杂度: O(N^2),其中N是数组中的元素数量.最坏情况下数组中任意两个数都要被匹配一次.
// . 空间复杂度: 0(1).
vector<int> twoSum_G2(vector<int> & nums, int target)
{
    int n = nums.size();
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(nums[i] + nums[j] == target)
                return {i, j};
        }
    }
    return {};
}

// 哈希表
// 使用哈希表,可以将寻找 target-x 的时间复杂度降低到从O(N)降低到 O(1).
// 这样我们创建一个哈希表,对于每一个 x,我们首先查询哈希表中是否存在 target-x,
// 然后将 x 插入到哈希表中,即可保证不会让 x 和自己匹配.
// unordered_map::find() 查找的是 key，返回迭代器，没找到时返回 .end()

vector<int> twoSum_G2(vector<int> & nums, int target)
{
    unordered_map<int, int> hashtable;  // key 存元素值， value 存元素下标
    for(int i=0; i<nums.size(); i++)
    {
        auto iter = hashtable.find(target - nums[i]);   // 在哈希表中找另一半，比在数组中找要快
        if(iter != hashtable.end())
            return {iter->second, i};
        hashtable[nums[i]] = i;         // 没找到时插入 key = nums[i], value = i
        // hashtable.insert(pair<int, int>(nums[i], i));    // 和上面等价
    }
    return {};
}