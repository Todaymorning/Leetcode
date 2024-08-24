// https://leetcode.cn/problems/search-a-2d-matrix-ii/description/?envType=study-plan-v2&envId=top-100-liked
// 240. 搜索二维矩阵 II
// 已解答
// 中等
// 相关标签
// 相关企业
// 编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

// 每行的元素从左到右升序排列。
// 每列的元素从上到下升序排列。
 

// 示例 1：


// 输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
// 输出：true
// 示例 2：


// 输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
// 输出：false
 

// 提示：

// m == matrix.length
// n == matrix[i].length
// 1 <= n, m <= 300
// -109 <= matrix[i][j] <= 109
// 每行的所有元素从左到右升序排列
// 每列的所有元素从上到下升序排列
// -109 <= target <= 109


#include<iostream>
#include<vector>
using namespace std;



class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        
    }
};



// 按行二分查找
class Solution_G1 {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for(const auto & vec : matrix) {
            auto it = std::lower_bound(vec.begin(), vec.end(), target);
            if(it != vec.end() && *it == target) {
                return true;
            }
        }
        return false;
    }
};

// 自己实现二分查找
class Solution_G1_M1 {
    // 找到升序数组中大于等于 target 的最小索引
    // 找到返回索引，找不到返回 - 1
    int lowerBound(vector<int> vec, int target) {
        int middle = -1;
        // [left, right)
        int left = 0, right = vec.size();
        while(left < right) {
            middle = left + ((right - left) >> 1);
            if(vec[middle] < target) {
                left = middle + 1;
            }
            else {  // ***
                right = middle;
            }
        }
        return left >= vec.size() ? -1 : left;
    }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for(const auto & vec : matrix) {
            int idx = lowerBound(vec, target);
            if(idx != -1 && vec[idx] == target) return true;
        }
        return false;
    }
};


// z 字形查找
// 从右上角开始查找，除了左上角，其余三个角均满足一边增加边减小，可以按 z 字形查找
// 如果 matrix[x][y] > target，由于y向下数组增加，排除y列，让 y-1
// 如果 matrix[x][y] < target，由于x向左数字减小，排除x行，让 x+1
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(), n = matrix[0].size();
        int x = 0, y = n - 1;
        while(x < m && y>=0) {
            if(matrix[x][y] > target) {
                y--;
            }
            else if(matrix[x][y] < target) {
                x++;
            }
            else {
                return true;
            }
        }
        return false;
    }
};