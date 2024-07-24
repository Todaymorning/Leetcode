// 406. 根据身高重建队列
// 中等
// 假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。
// 每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。
// 请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，
// 其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。

// 示例 1：
// 输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
// 输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
// 解释：
// 编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
// 编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
// 编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
// 编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
// 编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
// 编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
// 因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。

// 示例 2：
// 输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
// 输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]

// 提示：
// 1 <= people.length <= 2000
// 0 <= hi <= 10^6
// 0 <= ki < people.length
// 题目数据确保队列可以被重建


#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
using std::list;    // C++链表
using std::sort;
using std::vector;
class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {

    }
};

// 15:46--15:51(看题)--16:00(找思路)--16:29(错误，vs调试)--16:39(应该是升序而不是降序)
// 先按照身高从低到高排序，再从低到高放人
// 人的身高大于 0
// 输入
// people =
// [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
// 输出
// [[5,0],[6,1],[5,2],[0,0],[4,4],[0,0]]
// 预期结果
// [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
class Solution_M1 {
    static bool cmp(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];   // 降序序排列   ***
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 降序排列
        sort(people.begin(), people.end(), cmp);
        // 初始化
        vector<vector<int>> result(people.size(), vector<int>(2, 0));
        vector<bool> used(people.size(), false);
        // 放人，先放身高低的，再放身高高的
        for(int i=0; i<people.size(); i++) {
            // int num = 1;
            // while(i+1 < people.size() && people[i+1][0] == people[i][0]) num++, i++;
            // vector<vector<int>> temp(people.begin() + i - num, people.begin() + i)
            int temp = people[i][1];
            for(int j=0; j<people.size(); j++) {
                if(used[j] == false || result[j][0] >= people[i][0]) temp--;
                if(temp < 0) {
                    result[j] = people[i];
                    used[j] = true;
                    break;
                }
            }
        }
        return result;
    }
};



// 16:40--16:48
// 看了 D1 的思路和部分代码
// 使用 vector 的 insert 身高从大到小插入，人数从小到达插入
// 16:48--16:59
// 时间复杂度：O (nlog n + n^2)
// 空间复杂度：O (n)
// 但使用 vector 是非常费时的，C++ 中 vector（可以理解是一个动态数组，底层是普通数组实现的）如果插入元素大于预先普通数组大小，
// vector 底部会有一个扩容的操作，即申请两倍于原先普通数组的大小，然后把数据拷贝到另一个更大的数组上。
// 所以使用 vector（动态数组）来 insert，是费时的，插入再拷贝的话，单纯一个插入的操作就是 O (n^2) 了，甚至可能拷贝好几次，就不止 O (n^2) 了。
class Solution_D1_M2 {
    static bool cmp(vector<int>& a, vector<int>& b) {
        if(a[0] == b[0]) return a[1] < b[1];    // 同一身高，按人数从小到大（人数升序）
        else return a[0] > b[0];                // 不同身高，按身高从大到小（身高倒序）
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 排序
        sort(people.begin(), people.end(), cmp);
        vector<vector<int>> result; 
        for(int i=0; i<people.size(); i++) {
            result.insert(result.begin() + people[i][1], people[i]);
        }
        return result;
    }
};



// 17:00--17:03(看D2思路)--17:13
// 使用vector插入较为耗时，因此将其改为链表实现，其余不变
// 链表插入的使用方式 ***
class Solution_D2_M3 {
    static bool cmp(vector<int>& a, vector<int>& b) {
        if(a[0] == b[0]) return a[1] < b[1];
        else return a[0] > b[0];
    }
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // 排序
        sort(people.begin(), people.end(), cmp);
        // 插入
        list<vector<int>> que;
        for(int i=0; i<people.size(); i++) {
            // auto it = que.begin();
            int posion = people[i][1];
            // ***
            std::list<std::vector<int>>::iterator it = que.begin();
            while(posion--) it++;

            que.insert(it, people[i]);
        }
        vector<vector<int>> result(que.begin(), que.end());
        return result;
    }
};