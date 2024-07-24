// 332. 重新安排行程
// 困难
// 给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi] 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。
// 所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。
// 例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。
// 假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<unordered_map>
using std::pair;
using std::map;
using std::unordered_map;
using std::sort;
using std::string;
using std::vector;
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {

    }
};

// 16:00--16:55--半天
// 将每张票的六个字母和索引拼成一个字符串后参与排序，然后使用排序后的字符串得到排序后的票
// 遇到的错误：
// 访问空数组、超时
// results只需要一个元素就可以退出、排序后同一树层去重、使用前可能需要判断非空、索引从拼接字符串中分离
class Solution_M1 {
    vector<vector<int>> results;    // 记录票的索引
    vector<int> track;
    vector<bool> used;
    void backtrack(vector<vector<string>>& tickets) {
        if(!track.empty() && tickets[track[0]][0] != "JFK") return; // 第一张票限制
        if(track.size() == tickets.size()) {
            results.push_back(track);
            return;
        }
        for(int i=0; i<tickets.size(); i++) {
            if(!results.empty()) return;    // 已经找到了一个，不用继续找了 ***
            if(used[i] == true) continue;   // 票被用过了
            if(!track.empty() &&tickets[track.back()][1] != tickets[i][0]) continue; // 行程不连续 !track.empty()  ***
            if(i>0 && used[i-1] == false && tickets[i-1] == tickets[i]) continue;    // 同一树层去重               ***
            used[i] = true;
            track.push_back(i);
            backtrack(tickets);
            used[i] = false;
            track.pop_back();
        }
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        results.clear();
        track.clear();
        used = vector<bool>(tickets.size(), false);
        // 排序
        vector<string> tickets_copy;
        for(int i=0; i<tickets.size(); i++) {
            tickets_copy.push_back(tickets[i][0] + tickets[i][1] + string(std::to_string(i)));
        }
        sort(tickets_copy.begin(), tickets_copy.end());
        vector<vector<string>> sorted_tickets;
        for(int i=0; i<tickets.size(); i++) {
            int idx = std::stoi(string(tickets_copy[i].begin() + 6, tickets_copy[i].end()));
            sorted_tickets.push_back(tickets[idx]);
            // sorted_tickets.push_back(tickets[tickets_copy[i].back() - '0']);    // 不是最后一位，数字是从第六位开始 ***
        }
        backtrack(sorted_tickets);

        // 由索引找到对应的字符串，注意是排序后的 sorted_tickets   ***
        vector<string> result;
        if(results.empty()) return result;                   // ***
        result.push_back(sorted_tickets[results[0][0]][0]);
        result.push_back(sorted_tickets[results[0][0]][1]);
        for(int i=1; i<sorted_tickets.size(); i++) {
            result.push_back(sorted_tickets[results[0][i]][1]);
        }
        return result;
    }
};

// int main() {
//     vector<vector<string>> tickets = {{"MUC","LHR"},{"JFK","MUC"},{"SFO","SJC"},{"LHR","SFO"}};
//     Solution_M1 s;
//     auto result = s.findItinerary(tickets);
//     return 0;
// }






// 16:22--16:58
// 看过 D1 的思路后写的
// 从同一个机场出发的机票可以看作一个集合，这样就可以大大减少回溯中下一层的选择
// 回溯函数有个返回值，找到一个路径后就可以直接返回，不用继续回溯了
// 本题既要找到一个对数据进行排序的容器，而且还要容易增删元素，迭代器还不能失效。
// 所以我选择了 unordered_map<string, map<string, int>> targets 来做机场之间的映射。---------使用这样的数据结构，不用同一树层去重了
class Solution_D1_M1 {
    // 保存结果
    vector<string> result;
    // unordered_map<出发机场, map<到达机场, 航班次数>>
    // 所有出发机场的顺序不用排序，同一机场出发时的目的机场排序
    unordered_map<string, map<string,int>> candidate;       // ---***---
    bool backtracking(const int num, const string& from) {
        if(result.size() == num + 1) return true;
        for(pair<const string, int>& to : candidate[from]) {    // map 已经自动排序，只要是第一个找到的路径，肯定是字典最小的
            if(to.second <= 0) continue;    // 该行程票用完了
            to.second--;                    // 用掉一张票
            result.push_back(to.first);
            if(backtracking(num, to.first)) return true;
            to.second++;
            result.pop_back();
        }
        return false;
    }
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        result.clear();
        candidate.clear();
        // 记录映射关系
        for(const vector<string>& t : tickets) {
            candidate[t[0]][t[1]]++;    // candidate[出发][到达] ***
        }
        result.push_back("JFK");
        backtracking(tickets.size(), "JFK");
        return result;
    }
};





// 不使用 unordered_map<string, map<string,int>>
// 使用   unordered_map<string, vector<string>>， 手动对其进行排序-----------使用这样的数据结构需要对同一树层去重
class Solution_L1_copy {
    // 邻接表形式的图，key 是机场名字，value 是从该机场出发能够到达的机场列表
    unordered_map<string, vector<string>> graph;
    // 和 graph 对应，记录每张机票是否被使用过
    // 比如 graph["JFK"][2] = true 说明从机场 JFK 出发的第 3 张机票已经用过了
    unordered_map<string, vector<bool>> used;
    vector<vector<string>> tickets;

    // 回溯算法使用的数据结构
    vector<string> track;
    // 回溯算法记录结果
    vector<string> res;

public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        this->tickets = tickets;
        // 1. 用机场的名字构建邻接表
        for (vector<string>& ticket : tickets) {
            string from = ticket[0];
            string to = ticket[1];
            if (!graph.count(from)) {
                graph[from] = vector<string>();
            }
            graph[from].push_back(to);
        }
        // 2. 对邻接表的每一行进行排序，保证字典序最小
        for (auto& p : graph) {
            sort(p.second.begin(), p.second.end());
        }
        // 3. 初始化 used 结构，初始值都为 false
        for (auto& p : graph) {
            used[p.first] = vector<bool>(p.second.size(), false);
        }
        // 4. 从起点 "JFK" 开始启动 DFS 算法递归遍历
        track.push_back("JFK");
        backtrack("JFK");
        return res;
    }

private:
    void backtrack(string airport) {
        if (!res.empty()) {
            // 已经找到答案了，不用再计算了
            return;
        }
        if (track.size() == tickets.size() + 1) {
            // track 里面包含了所有的机票，即得到了一个合法的结果
            // 注意 tickets.size() 要加一，因为 track 里面额外包含了起点 "JFK"
            res = vector<string>(track.begin(), track.end());
            return;
        }
        if (!graph.count(airport)) {
            // 没有从 s 出发的边
            return;
        }

        // 遍历当前机场所有能够到达的机场
        vector<string>& nextAirports = graph[airport];
        for (int i = 0; i < nextAirports.size(); i++) {
            string& nextAirport = nextAirports[i];
            if (used[airport][i]) {
                // 如果这张机票被使用过，跳过
                continue;
            }
            // 做选择
            used[airport][i] = true;
            track.push_back(nextAirport);
            // 递归
            backtrack(nextAirport);
            // 撤销选择
            used[airport][i] = false;
            track.pop_back();
        }
    }
};


