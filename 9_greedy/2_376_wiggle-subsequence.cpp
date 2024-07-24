// 376. 摆动序列
// 中等
// 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列 。第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。
// 例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3) 是正负交替出现的。
// 相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
// 子序列 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。
// 给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。

// 示例 1：
// 输入：nums = [1,7,4,9,2,5]
// 输出：6
// 解释：整个序列均为摆动序列，各元素之间的差值为 (6, -3, 5, -7, 3) 。

// 示例 2：
// 输入：nums = [1,17,5,10,13,15,10,5,16,8]
// 输出：7
// 解释：这个序列包含几个长度为 7 摆动序列。
// 其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3, 6, -8) 。

// 示例 3：
// 输入：nums = [1,2,3,4,5,6,7,8,9]
// 输出：2
 

// 提示：
// 1 <= nums.length <= 1000
// 0 <= nums[i] <= 1000
 
// 进阶：你能否用 O(n) 时间复杂度完成此题？


#include<iostream>
#include<vector>
using std::vector;
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {

    }
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 贪心解法
// 局部最优：删除单调坡度上的节点（不包括单调坡度两端的节点），那么这个坡度就可以有两个局部峰值。
// 整体最优：整个序列有最多的局部峰值，从而达到最长摆动序列。

// 11:04--11:15--11:26(有错误)
// 没有考虑到单调的中间有平台：0,1,2,2,2,2,4，这里面本来只能算成两个，但用之前的算法会算出三个（有两个转折点）
#if 0
class Solution_M1 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int size = nums.size();
        if(size < 2) return size;
        if(size == 2 && nums[0] != nums[1]) return size;
        int result = 1;
        // 下面的代码相当于遇到一个转折点就加一，但忽略了单调的坡上有平台的情况
        for(int i=1, j; i<size; ) {
            while(i<size && nums[i-1] == nums[i]) i++;
            j = i;
            while(i<size && nums[i-1] > nums[i]) i++;
            if(i != j) result += 1;
            j = i;
            while(i<size && nums[i-1] < nums[i]) i++;
            if(i != j) result += 1;
        }
        return result;
    }
};
#endif
// ------11:51
// 看了 D1 的总结后发现错误的地方，尝试自己更改
class Solution_M1 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int size = nums.size();
        if(size < 2) return size;
        if(size == 2 && nums[0] != nums[1]) return size;
        int result = 1;
        for(int i=1, j; i<size; ) {         // 注意这里没有了i++        ***
            while(i<size && nums[i-1] == nums[i]) i++;  // 过滤头部相等，应该只有数组的开头有用，后面不会用到
            j = i;
            while(i<size && (nums[i-1] > nums[i] || nums[i-1] == nums[i])) i++; // 单调下降中的平台及末尾的平台；下一个结束或是一个上升
            if(i != j) result += 1;
            // while(i<size && nums[i-1] == nums[i]) i++;  // 过滤头部相等
            j = i;
            while(i<size && (nums[i-1] < nums[i] || nums[i-1] == nums[i])) i++; // 单调上升中的平台及末尾的平台；下一个结束或时一个下降
            if(i != j) result += 1;
        }
        return result;
    }
};



// 12:06--15:23
// 记录峰值
// 情况一：上下坡中有平坡
// (preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)
// 情况二：数组首尾两端
// result 初始为 1（默认最右面有一个峰值），此时 curDiff > 0 && preDiff <= 0，那么 result++（计算了左面的峰值），
// 最后得到的 result 就是 2（峰值个数为 2 即摆动序列长度为 2）
// 情况三：单调坡中有平坡
// 如果在一个单调坡度上有平坡，例如 [1,2,2,2,3,4]，不处理的话就会多计算
// 时间复杂度：O (n)
// 空间复杂度：O (1)
class Solution_D1_M1 {
public:
    int wiggleMaxLength(vector<int>& nums) {
        if (nums.size() < 2) return nums.size();
        int result = 1;     // 记录峰值个数，默认最右边有个峰值
        int max = nums.size()-1;
        int prediff = 0;    // 前一对差值
        int curdiff = 0;    // 当前一对差值
        for(int i=0; i<max; i++) {
            curdiff = nums[i+1] - nums[i];
            if((prediff >= 0 && curdiff < 0) || (prediff <= 0 && curdiff > 0)) {
                result ++;
                prediff = curdiff;  // 只在摆动变换的时候变化prediff，即 curdiff == 0 的时候是平台，不更新 prediff
            }
            // prediff = curdiff;
        }
        return result;
    }
};



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 动态规划
// 待写

