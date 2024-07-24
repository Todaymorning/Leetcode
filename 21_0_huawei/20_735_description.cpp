// https://leetcode.cn/problems/asteroid-collision/description
// 735. 小行星碰撞
// 中等
// 相关标签
// 相关企业
// 提示
// 给定一个整数数组 asteroids，表示在同一行的小行星。
// 对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。
// 每一颗小行星以相同的速度移动。找出碰撞后剩下的所有小行星。
// 碰撞规则：两个小行星相互碰撞，较小的小行星会爆炸。如果两颗小行星大小相同，则两颗小行星都会爆炸。两颗移动方向相同的小行星，永远不会发生碰撞。

// 示例 1：
// 输入：asteroids = [5,10,-5]
// 输出：[5,10]
// 解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。

// 示例 2：
// 输入：asteroids = [8,-8]
// 输出：[]
// 解释：8 和 -8 碰撞后，两者都发生爆炸。

// 示例 3：
// 输入：asteroids = [10,2,-5]
// 输出：[10]
// 解释：2 和 -5 发生碰撞后剩下 -5 。10 和 -5 发生碰撞后剩下 10 。

// 提示：
// 2 <= asteroids.length <= 10^4
// -1000 <= asteroids[i] <= 1000
// asteroids[i] != 0



#include<iostream>
#include<vector>
#include<stack>
using std::stack;
using std::vector;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {

    }
};


// 2024年5月17日
// 20:30--20:33(不会)--20:36(看了关键词 栈模拟)--21:12--21:21(错误，没有考虑往两边飞的)
# if 0
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        // 栈内都是同向的
        stack<int> stk;
        stk.push(asteroids[0]);
        for(int i=1; i<asteroids.size(); i++) {
            // 栈内为空，放入
            if(stk.empty()) {
                stk.emplace(asteroids[i]);
            }
            else {
                // 符号相同，放入
                if(stk.top() > 0 && asteroids[i] > 0) stk.emplace(asteroids[i]);
                else if(stk.top() < 0 && asteroids[i] < 0) stk.emplace(asteroids[i]);
                else {
                    // 符号相反，开始碰撞
                    char flag = 's';    // small
                    int temp = std::abs(asteroids[i]);
                    while(!stk.empty()) {
                        int top = std::abs(stk.top());
                        if(top < temp) stk.pop();
                        else if(top == temp) {
                            stk.pop();
                            flag = 'e'; // equal
                            break;
                        }
                        else {
                            flag = 'b'; // big
                            break;
                        }
                    }
                    if(flag == 's') stk.emplace(asteroids[i]);
                }
            }
        }
        vector<int> result;
        while(!stk.empty()) {
            result.emplace_back(stk.top());
            stk.pop();
        }
        return result;
    }
};
#endif


// 2024年5月17日
// 21:22--正确
// + 向右  - 向左
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int n = asteroids.size();
        vector<int> stk;
        stk.emplace_back(asteroids[0]);
        for(int i=1; i<n; i++) {
            if(stk.empty()) {
                stk.emplace_back(asteroids[i]);
            }
            else {
                // 碰撞 -->  <--
                if(stk.back() > 0 && asteroids[i] < 0) {
                    int flag = 0;
                    while(!stk.empty() && stk.back() > 0) {
                        if(std::abs(stk.back()) > std::abs(asteroids[i])) {
                            flag = 1;
                            break;  // 栈内较大，i被碰碎
                        }
                        else if(std::abs(stk.back()) == std::abs(asteroids[i])) {
                            flag = 1;
                            stk.pop_back(); // 相等，都被碰碎
                            break;
                        }
                        else {
                            // i 较大，栈顶被碰碎
                            stk.pop_back();
                        }
                    }
                    // i 还没被碰碎，放入栈顶
                    if(flag == 0) stk.emplace_back(asteroids[i]);
                }
                // 不用碰撞
                else {
                    stk.emplace_back(asteroids[i]);
                }
            }
        }
    }
};





// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/asteroid-collision/solutions/1663442/xing-xing-peng-zhuang-by-leetcode-soluti-u3k0/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
class Solution_G1_copy {
public:
    vector<int> asteroidCollision (vector<int>& asteroids) {
        vector<int> st;
        for (auto aster : asteroids) {
            bool alive = true;
            while (alive && aster < 0 && !st.empty () && st.back () > 0) {
                alive = st.back () < -aster; //aster 是否存在
                if (st.back () <= -aster) {  // 栈顶行星爆炸
                    st.pop_back ();
                }
            }
            if (alive) {
                st.push_back (aster);
            }
        }
        return st;
    }
};