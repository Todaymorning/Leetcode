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

// 单调队列
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

    }
};

// 不推荐，看下一个答案
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




// 2024年7月28日
// 忘记咋写

// 如何在 O(1) 时间计算最大值，只需要一个特殊的数据结构「单调队列」，
// push 方法依然在队尾添加元素，但是要把前面比自己小的元素都删掉，
// 直到遇到更大的元素才停止删除。

// 注意：cpp 代码由 chatGPT🤖 根据我的 java 代码翻译，旨在帮助不同背景的读者理解算法逻辑。
// 本代码已经通过力扣的测试用例，应该可直接成功提交。

class Solution {
    // 单调队列的实现
    class MonotonicQueue {
        deque<int> q;
    public:
        void push(int n) {
            // 将小于 n 的元素全部删除
            while (!q.empty() && q.back() < n) {
                q.pop_back();
            }
            // 然后将 n 加入尾部
            q.push_back(n);
        }
        // 这个可以不用要，push 和 pop 必须要有，且都有参数
        int max() {
            return q.front();
        }

        void pop(int n) {
            if (n == q.front()) {
                q.pop_front();
            }
        }
    };

public:
    // 解题函数的实现
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MonotonicQueue window;
        vector<int> res;

        for (int i = 0; i < nums.size(); i++) {
            if (i < k - 1) {
                // 先填满窗口的前 k - 1
                window.push(nums[i]);
            } else {       // 每次进来的时候窗口只有 k-1 个元素，需要先加入窗口 
                // 窗口向前滑动，加入新数字
                window.push(nums[i]);
                // 记录当前窗口的最大值
                res.push_back(window.max());
                // 移出旧数字
                window.pop(nums[i - k + 1]);    // i - k + 1
            }
        }
        // 需要转成 int[] 数组再返回
        return res;
    }
};
// 详细解析参见：
// https://labuladong.online/algo/slug.html?slug=sliding-window-maximum
