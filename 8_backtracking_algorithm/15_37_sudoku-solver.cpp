// 37. 解数独
// 困难
// 编写一个程序，通过填充空格来解决数独问题。
// 数独的解法需 遵循如下规则：
// 数字 1-9 在每一行只能出现一次。
// 数字 1-9 在每一列只能出现一次。
// 数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
// 数独部分空格内已填入了数字，空白格用 '.' 表示。

// 提示：
// board.length == 9
// board[i].length == 9
// board[i][j] 是一位数字或者 '.'
// 题目数据 保证 输入数独仅有一个解

#include<iostream>
#include<vector>
using std::vector;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {

    }
};




// 10:32--10:40(没思路)
// 11:26
// 双层递归
// 超出时间限制，没找出为什么错了
#if 0
class Solution_M1 {
    // 判断是否合法
    bool isValid(int row, int col, char c, vector<vector<char>>& board) {
        // 判断行
        for(int i=0; i<board[0].size(); i++) {
            if(board[row][i] == c) return false;
        }
        // 判断列
        for(int i=0; i<board.size(); i++) {
            if(board[i][col] == c) return false;
        }
        // 判断 3*3
        int row_begin = row/3 * 3;
        int row_end = row_begin+3;
        int col_begin = col/3 * 3;
        int col_end = col_begin+3;
        for(int i=row_begin; i<row_end; i++) {
            for(int j=col_begin; j<col_end; j++) {
                if(board[i][j] == c) return false;
            }
        }
        return true;
    }
    bool backtracking(vector<vector<char>>& board, int _row, int _col) {
        if(_row == board.size()) return true;
        for(int row=_row; row<board.size(); row++) {
            for(int col=_col; col<board[0].size(); col++) {    // 在第二层循环中做递归
                if(board[row][col] != '.') continue;
                for(char i='1'; i<='9'; i++) {
                    if(!isValid(row, col, i, board)) continue;
                    board[row][col] = i;
                    if(col == board[0].size() - 1) {
                        if(backtracking(board, row+1, 0)) return true;
                    }
                    else {
                        if(backtracking(board, row, col+1)) return true;
                    }
                    board[row][col] = '.';
                }
            }
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board, 0, 0);
    }
};
#endif

class Solution_D1_M1 {
    // 判断是否合法
    bool isValid(int row, int col, char c, vector<vector<char>>& board) {
        // 判断行
        for(int i=0; i<board[0].size(); i++) {
            if(board[row][i] == c) return false;
        }
        // 判断列
        for(int i=0; i<board.size(); i++) {
            if(board[i][col] == c) return false;
        }
        // 判断 3*3
        int row_begin = row/3 * 3;
        int row_end = row_begin+3;
        int col_begin = col/3 * 3;
        int col_end = col_begin+3;
        for(int i=row_begin; i<row_end; i++) {
            for(int j=col_begin; j<col_end; j++) {
                if(board[i][j] == c) return false;
            }
        }
        return true;
    }
    bool backtracking(vector<vector<char>>& board) {
        for(int row=0; row<board.size(); row++) {       // 遍历行
            for(int col=0; col<board[0].size(); col++) {    // 遍历列，在第二层循环中做递归
                if(board[row][col] != '.') continue;
                for(char i='1'; i<='9'; i++) {
                    if(!isValid(row, col, i, board)) continue;  // 这个位置放i是否合适
                    board[row][col] = i;
                    if(backtracking(board)) return true;    // 如果找到合适一组立刻返回
                    board[row][col] = '.';
                }
                return false;  // 9个数都试完了，都不行，那么就返回false    ***
            }
        }
        return true;       // 遍历完没有返回false，说明找到了合适棋盘位置了
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtracking(board);
    }
};



// 16:28--16:47
class Solution_L1_M2 {
    bool isValid(vector<vector<char>>& board, int row, int col, char ch) {
        int rowBegin = row/3 * 3;
        int colBegin = col/3 * 3;
        for(int i=0; i<9; i++) {
            // 判断行
            if(board[i][col] == ch) return false;
            // 判断列
            if(board[row][i] == ch) return false;
            // 判断 3*3
            if(board[rowBegin + i/3][colBegin + i%3] == ch) return false;   // ***
        }
        return true;
    }
    bool backtrack(vector<vector<char>>& board, int row, int col) {
        int rows = board.size();
        int cols = board[0].size();
        if(row == rows) return true;    // 每一行都穷举完了
        if(col == cols) return backtrack(board, row+1, 0);    // 一行满了，穷举下一行   ***
        if(board[row][col] != '.') return backtrack(board, row, col+1); // 该位置已经有数字了
        for(char ch='1'; ch<='9'; ch++) {
            if(!isValid(board, row, col, ch)) continue;
            board[row][col] = ch;
            if(backtrack(board, row, col+1)) return true;   // 如果找到一个可行解，立即结束
            board[row][col] = '.';
        }
        return false;   // 穷举完 1~9，依然没有找到可行解
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0, 0);
    }
};


class Solution_L1_copy {
public:
    void solveSudoku(vector<vector<char>>& board) {
        backtrack(board, 0, 0);
    }

    bool backtrack(vector<vector<char>>& board, int i, int j) {
        int m = 9, n = 9;
        if (j == n) {
            // 穷举到最后一列的话就换到下一行重新开始。
            return backtrack(board, i + 1, 0);
        }
        if (i == m) {
            // 找到一个可行解，触发 base case
            return true;
        }

        if (board[i][j] != '.') {
            // 如果有预设数字，不用我们穷举
            return backtrack(board, i, j + 1);
        }

        for (char ch = '1'; ch <= '9'; ch++) {
            // 如果遇到不合法的数字，就跳过
            if (!isValid(board, i, j, ch))
                continue;

            board[i][j] = ch;
            // 如果找到一个可行解，立即结束
            if (backtrack(board, i, j + 1)) {
                return true;
            }
            board[i][j] = '.';
        }
        // 穷举完 1~9，依然没有找到可行解，此路不通
        return false;
    }

    bool isValid(vector<vector<char>>& board, int r, int c, char n) {
        for (int i = 0; i < 9; i++) {
            // 判断行是否存在重复
            if (board[r][i] == n) return false;
            // 判断列是否存在重复
            if (board[i][c] == n) return false;
            // 判断 3 x 3 方框是否存在重复
            if (board[(r/3)*3 + i/3][(c/3)*3 + i%3] == n)
                return false;
        }
        return true;
    }
};