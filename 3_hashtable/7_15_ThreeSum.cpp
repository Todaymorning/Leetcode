// 第 15 题。三数之和
// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
// 使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
// 注意： 答案中不可以包含重复的三元组。
// 给定数组 nums = [-1, 0, 1, 2, -1, -4]，
// 满足要求的三元组集合为： [ [-1, 0, 1], [-1, -1, 2] ]

// Three Sum
// sort + hash
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

vector<vector<int>> threeSum_D1(vector<int> &nums)
{
	vector<vector<int>> result; // 结果
	sort(nums.begin(), nums.end());  // 快速排序
	// 找到 	a+b+c=0, a<=b<=c, a=nums[i], b=nums[j], c=0-a-b
	for(int i=0; i<nums.size(); i++)
	{
		if(nums[i]>0) // 最小值应该 >=0
			break;
		if(i>0 && nums[i] == nums[i-1]) // a 去重,第一个数不同，其他数才有可能不同
			continue;
		unordered_set<int> set;
		for(int j = i+1; j<nums.size(); j++)
		{
			if(j>i+2 && nums[j] == nums[j-1] && nums[j-1] == nums[j-2])
				continue;	// b 去重
			int c = 0-nums[i]-nums[j];
			if(set.find(c)!=set.end())
			{
				result.push_back({nums[i], nums[j], c});
				set.erase(c);	// c 去重
			}
			else {
				set.insert(nums[j]);
			}
		}
	}
	return result;
}


//sort + 双指针
vector<vector<int>> threeSum_D2(vector<int> & nums)
{
	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	for(int i=0; i<nums.size(); i++)
	{
		// a+b+c = 0, a<=b<=c 	令:
		// nums[i] = a; nums[left] = b; nums[right] = c;
		if(nums[i]>0)	// 排序后的数组三个数的最小值应该小于零
			break;
		if(i>0 && nums[i] == nums[i-1]) // a去重，如果第一个数相同，后面两个数一定相同，都是在后面的数组中找
			continue;
		int left = i+1;
		int right = nums.size()-1;
		while(right > left)
		{
			int sum = nums[i] + nums[left] + nums[right]; // a+b+c
			if(sum > 0) right--;
			else if(sum < 0) left++;
			else {
				result.push_back(vector<int>{nums[i], nums[left], nums[right]});
				// 在找到元组之后对 b c 去重
				while(right > left && nums[right] == nums[right-1]) right--;
				while(right > left && nums[left] == nums[left+1]) left++;
				// 找到答案时，双指针同时收缩
				right--;
				left++;
			}
		}
	}
	return result;
}




// n 数之和
/* 注意：调用这个函数之前一定要先给 nums 排序 */
// n 填写想求的是几数之和，start 从哪个索引开始计算（一般填 0），target 填想凑出的目标和

vector<vector<int>> nSumTarget(vector<int>& nums, int n, int start, long target) {
    int size = nums.size();
    vector<vector<int>> res;
    // 至少是 2Sum，且数组大小不应该小于 n
    if (n < 2 || size < n) return res;
    // 2Sum 是 base case
    if (n == 2) {
        // 双指针那一套操作
        int lo = start, hi = size - 1;
        while (lo < hi) {
            int sum = nums[lo] + nums[hi];
            int left = nums[lo], right = nums[hi];
            if (sum < target) {
                while (lo < hi && nums[lo] == left) lo++;
            } else if (sum > target) {
                while (lo < hi && nums[hi] == right) hi--;
            } else {
                res.push_back({left, right});
                while (lo < hi && nums[lo] == left) lo++;
                while (lo < hi && nums[hi] == right) hi--;
            }
        }
    } else {
        // n > 2 时，递归计算 (n-1)Sum 的结果
        for (int i = start; i < size; i++) {
            vector<vector<int>> sub = nSumTarget(nums, n - 1, i + 1, target - nums[i]);
            for (vector<int>& arr : sub) {
                // (n-1)Sum 加上 nums[i] 就是 nSum
                arr.push_back(nums[i]);
                res.push_back(arr);
            }
            while (i < size - 1 && nums[i] == nums[i + 1]) i++;
        }
    }
    return res;
}