// 239. 滑动窗口最大值
// 给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
// 返回滑动窗口中的最大值。
// 进阶：
// 你能在线性时间复杂度内解决此题吗？
// 提示：
// 1 <= nums.length <= 10^5
// -10^4 <= nums[i] <= 10^4
// 1 <= k <= nums.length


# include <iostream>
# include <deque>
# include <vector>
using namespace std;
class Solution {
private:
    class MyQueue {
    public:
        deque<int> que; // 使用dqueue实现单调队列
        // 要弹的数值等于出口元素的数值
        void pop(int value) {
            if (!que.empty() && value == que.front()) {
                que.pop_front();
            }
        }
        void push(int value) {
            // push的数值大于入口元素的数值时将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
            // 这样就保持了队列里的数值是单调从大到小的了。
            while(!que.empty() && value > que.back()) {
                que.pop_back();
            }
            que.push_back(value);
        }
        int front() {
            que.front();
        }
        
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        for(int i=0; i<k; i++) {
            que.push(nums[i]);
        }
        result.push_back(que.front());
        for(int i=k; i<nums.size(); i++) {
            que.pop(nums[i-k]); // 滑动窗口移除最前面元素
            que.push(nums[i]);  // 滑动窗口前加入最后面的元素
            result.push_back(que.front());
        }
        return result;
    }
};