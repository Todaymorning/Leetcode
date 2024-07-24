// 双指针相关题目

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> fourSum_D1(vector<int> & nums, int target)
{
	vector<vector<int>> result;
	sort(nums.begin(), nums.end());
	//找 a+b+c+d=target; a=nums[k],b=nums[i],c=nums[left],d=nums[right]
	for(int k=0; k<nums.size(); k++)
	{
		if(nums[k] > target && nums[k]>=0) break;	// 一级减支，nums[k]>=0,说明nums[k]后面的数大于0
		if(k>0 && nums[k] == nums[k-1]) continue;	// a 去重
		for(int i=k+1; i<nums.size(); i++)
		{
			if(nums[k]+nums[i]>target && nums[k]+nums[i]>=0) break;	// 二级减支，说明nums[i]后面的数大于0
			if(i>k+1 && nums[i]==nums[i-1]) continue;
			int left = i+1;
			int right = nums.size()-1;
			long sum = 0;
			while(left < right)
			{
				sum = (long) nums[k]+nums[i]+nums[left]+nums[right];	// sum 位数需要足够，防止溢出
				if(sum > target) right--;
				else if(sum < target) left++;
				else {
					result.push_back({nums[k],nums[i],nums[left],nums[right]});
					while(right>left && nums[left] == nums[left+1]) left++;
					while(right>left && nums[right] == nums[right-1]) right--;
					left++;	// ***
					right--;
				}
			}
		}
	}
	return result;
}