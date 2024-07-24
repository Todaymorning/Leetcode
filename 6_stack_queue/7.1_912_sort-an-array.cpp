// 912. 排序数组
// 给你一个整数数组 nums，请你将该数组升序排列。

// 八大排序中，桶排序，冒泡，选择，插入，快速（包括，未随机化的二向、三向切分快排，以及随机化的二向切分）超时；希尔排序，归并排序，堆排序，随机化的三向切分快排，通过。


#include <iostream>
#include <vector>   // std::vector
#include <ctime>    // time
using std::vector;
using std::swap;



////////////////////////////////////////////////////////////////////////////////////////////////////////////// 快速排序
// 不稳定排序，排序后相同元素的相对位置可能发生改变
// 时间复杂度：O(nlogn)~O(logn)
// 空间复杂度 O(logn)~O(n)

// l<k<i时，nums[k]<= pivot
// i+1<k<j-1 时，nums[k]> pivot
// k==r 时，nums[k]= pivot。
class Solution {
public:
    void randomized_quicksort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int mid_idx = rand() % (r - l + 1) + l; // 随机选择一个数作为主元
            swap(nums[mid_idx], nums[r]);           // 将该数放到区间最后
            int mid = nums[r];
            int i = l-1;
            for(int j=l; j<r; j++) {                // i j 之间满足一定条件
                if(nums[j] <= mid) {
                    i++;
                    swap(nums[i], nums[j]);
                }
            }
            swap(nums[r], nums[i+1]);               // 将主元放到中间
            int pos = i+1;
            randomized_quicksort(nums, l, pos - 1);
            randomized_quicksort(nums, pos + 1, r);
        }
    }
    vector<int> sortArray(vector<int>& nums) {
        srand((unsigned)time(NULL));
        randomized_quicksort(nums, 0, int(nums.size()) - 1);
        return nums;
    }
};


class Solution_G1 {
    int partition(vector<int>& nums, int l, int r) {
        int pivot = nums[r];    // 最右边的值已经是随机选的中值了
        int i = l - 1;
        // 指针 i及 i左侧对应的数都是小于等于pivot(中值)的数，i j之间都是大于pivot的数
        for (int j = l; j <= r - 1; ++j) {  // 从左边开始遇到一个小于等于pivot的数就i++，并将i与j对应的数交换
            if (nums[j] <= pivot) {
                i = i + 1;
                swap(nums[i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[r]);
        return i + 1;
    }
    int randomized_partition(vector<int>& nums, int l, int r) {
        int i = rand() % (r - l + 1) + l; // 随机选一个作为我们的主元
        swap(nums[r], nums[i]);
        return partition(nums, l, r);
    }
    void randomized_quicksort(vector<int>& nums, int l, int r) {
        if (l < r) {
            int pos = randomized_partition(nums, l, r);
            randomized_quicksort(nums, l, pos - 1);
            randomized_quicksort(nums, pos + 1, r);
        }
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        srand((unsigned)time(NULL));
        randomized_quicksort(nums, 0, (int)nums.size() - 1);
        return nums;
    }
};




class Solution_ZH {
    void quick_sort_recursive(vector<int>& arr, int start, int end) {
        if (start >= end)
            return;
        int mid = arr[end];
        int left = start, right = end - 1;
        // 结束循环时 left=right，左侧小于mid，右侧大于等于mid，即数组最后的值
        while (left < right) {
            while (arr[left] < mid && left < right)
                left++;
            while (arr[right] >= mid && left < right)
                right--;
            swap(arr[left], arr[right]);
        }
        // left=right时上面的while大循环结束，中间的这个值可能没参与比较，因此需要单独比较
        // 注意循环中先left++，这时可能跳出循环，right可能没有判断大小
        if (arr[left] >= arr[end])
            swap(arr[left], arr[end]);    // 中间的值大于等于mid时，把mid交换到中间，后面分别对两边排序（中间的值不用排序）
        else
            left++; // 中间的值比mid小时，证明中间的值需要继续参与排序，这里将中间的划到左边
        quick_sort_recursive(arr, start, left - 1);
        quick_sort_recursive(arr, left + 1, end);
    }
public:
    vector<int> sortArray(vector<int>& nums) {
        quick_sort_recursive(nums, 0, nums.size() - 1);
        return nums;
    }
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////// 计数排序
class Solution_jishu {
public:
    vector<int> sortArray(vector<int>& nums)
    {
        int max = -50001, min = 50001;  // 最大最小值在题目限制之外，方便真的赋值
        for(int num:nums) {             // 遍历，找到最大最小值
            if (num>max) max = num;
            if (num<min) min = num;
        }
        vector<int> counter(max-min+1);
        for(int num:nums) {             // 统计每个数的个数
            counter[num-min]++;
        }
        int idx=0;
        for(int num=min; num<=max; num++) { // 根据个数放到对应位置
            int cnt = counter[num-min];
            while(cnt-- > 0) {
                nums[idx++] = num;
            }
        }
        return nums;
    }
};








