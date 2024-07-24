// 498. 对角线遍历
// 中等
// 相关标签
// 相关企业
// 给你一个大小为 m x n 的矩阵 mat ，请以对角线遍历的顺序，用一个数组返回这个矩阵中的所有元素。

// 示例 1：
// 输入：mat = [[1,2,3],[4,5,6],[7,8,9]]
// 输出：[1,2,4,7,5,3,6,8,9]

// 示例 2：
// 输入：mat = [[1,2],[3,4]]
// 输出：[1,2,3,4]

// 提示：
// m == mat.length
// n == mat[i].length
// 1 <= m, n <= 10^4
// 1 <= m * n <= 10^4
// -10^5 <= mat[i][j] <= 10^5

#include<iostream>
#include<vector>
using std::vector;


class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {

    }
};



// 20:54--21:23
class Solution {
    int dir[4][2] = {-1, 1, 1, -1};
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int x = 0, y=0;
        vector<int> result;
        int flag = 0;
        for(int i=0; i<m+n-1; i++) {
            // 左上 右下
            while(x>=0 && x<m && y>=0 && y<n) {
                result.push_back(mat[x][y]);
                x += dir[flag][0];
                y += dir[flag][1];
            }
            // 恢复
            x -= dir[flag][0];
            y -= dir[flag][1];
            // 拐弯
            if(!flag && y<n-1) y+=1;
            else if(!flag && y==n-1) x+=1;
            else if(x < m-1) x+=1;
            else y+= 1;
            // 换向
            flag = flag == 0 ? 1 : 0;
        }
        return result;
    }
};




class Solution_G1 {
public:
    vector<int> findDiagonalOrder (vector<vector<int>>& mat) {
        int m = mat.size ();
        int n = mat [0].size ();
        vector<int> res;
        for (int i = 0; i < m + n - 1; i++) {
            if (i % 2) {
                int x = i < n ? 0 : i - n + 1;
                int y = i < n ? i : n - 1;
                while (x < m && y >= 0) {
                    res.emplace_back (mat [x][y]);
                    x++;
                    y--;
                }
            } else {
                int x = i < m ? i : m - 1;
                int y = i < m ? 0 : i - m + 1;
                while (x >= 0 && y < n) {
                    res.emplace_back (mat [x][y]);
                    x--;
                    y++;
                }
            }
        }
        return res;
    }
};
// 作者：力扣官方题解
// 链接：https://leetcode.cn/problems/diagonal-traverse/solutions/1597961/dui-jiao-xian-bian-li-by-leetcode-soluti-plz7/
// 来源：力扣（LeetCode）
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

