// 51. N 皇后
// labuladong 题解思路
// 困难

// 按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
// n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
// 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
// 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

 

// 示例 1：
// 输入：n = 4
// 输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
// 解释：如上图所示，4 皇后问题存在两个不同的解法。

// 示例 2：
// 输入：n = 1
// 输出：[["Q"]]
 
// 提示：
// 1 <= n <= 9

#include<iostream>
#include<vector>
#include<string>
using std::vector;
using std::string;
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {

    }
};


// 20:21--20:40--斜线判断错误
// 按行进行回溯，每次回溯进入下一行
// 题目理解错误
// 时间复杂度: O (n!)
// 空间复杂度: O (n)
class Solution_D1 {
    vector<vector<string>> result;
    vector<string> track;
    bool isValid(int n, int row, int col) { // 从后往前检查
        // 检查同一列
        for(int i=row-1; i>=0; i--) {
            if(track[i][col] == 'Q') return false;
        }
        // 检查45度（左上方）
        for(int i=row-1, j=col-1; i>=0 && j>=0; i--,j--) {
            if(track[i][j] == 'Q') return false;
        }
        // 检查135度（右上方）
        for(int i = row-1, j=col+1; i>=0 && j<n; i--, j++) {
            if(track[i][j] == 'Q') return false;
        }
        return true;
    }
    void backtracking(int n, int row) {
        if(row == n) {
            result.push_back(track);
            return;
        }
        for(int col=0; col<n; col++) {
            if(!isValid(n, row, col)) continue;
            track[row][col] = 'Q';
            backtracking(n, row + 1);
            track[row][col] = '.';
        }

    }
public:
    vector<vector<string>> solveNQueens(int n) {
        result.clear();
        track = vector<string>(n, string(n, '.'));
        backtracking(n, 0);
        return result;
    }
};