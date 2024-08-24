// https://leetcode.cn/problems/find-the-duplicate-number/?envType=study-plan-v2&envId=top-100-liked
// 287. 寻找重复数
// 已解答
// 中等
// 相关标签
// 相关企业
// 给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和 n），可知至少存在一个重复的整数。

// 假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。

// 你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。

 

// 示例 1：

// 输入：nums = [1,3,4,2,2]
// 输出：2
// 示例 2：

// 输入：nums = [3,1,3,4,2]
// 输出：3
// 示例 3 :

// 输入：nums = [3,3,3,3,3]
// 输出：3
 

 

// 提示：

// 1 <= n <= 105
// nums.length == n + 1
// 1 <= nums[i] <= n
// nums 中 只有一个整数 出现 两次或多次 ，其余整数均只出现 一次
 

// 进阶：

// 如何证明 nums 中至少存在一个重复的数字?
// 你可以设计一个线性级时间复杂度 O(n) 的解决方案吗？



#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {

    }
};

class Solution_M1 {
public:
    int findDuplicate(vector<int>& nums) {
        // 2024年8月6日
        // 22:10--22:16
        int result;
        for(int i=0; i<nums.size(); i++) {
            int cur = std::abs(nums[i]);
            if(nums[cur] > 0) nums[cur] = -nums[cur];
            else {
                result = cur;
                break;
            }
        }
        for(int i=0; i<nums.size(); i++) {
            if(nums[i] < 0) nums[i] = -nums[i];
        }
        return result;
    }
};


// 使用类似环形链表的解法
// 如果数组中有重复的数，以数组 [1,3,4,2,2] 为例,我们将数组下标 n 和数 nums[n] 建立一个映射关系 f(n)，
// 其映射关系 n->f(n) 为：
// 0->1
// 1->3
// 2->4
// 3->2
// 1.数组中有一个重复的整数 <==> 链表中存在环
// 2.找到数组中的重复整数 <==> 找到链表的环入口
class Solution_O1 {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        while(fast < nums.size() && nums[fast] < nums.size()) {
            slow = nums[slow];
            fast = nums[nums[fast]];
            if(slow == fast) {
                fast = 0;
                while(fast != slow) {
                    fast = nums[fast];
                    slow = nums[slow];
                }
                return fast;
            }
        }
        return -1;
    }
};