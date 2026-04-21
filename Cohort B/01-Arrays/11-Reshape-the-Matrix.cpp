/*
========================================================================================
Problem Name : Reshape the Matrix (566)
Problem Link : https://leetcode.com/problems/reshape-the-matrix/description/
========================================================================================

PROBLEM STATEMENT:
In MATLAB, there is a handy function called reshape which can reshape an m x n matrix into a new one with a different size r x c keeping its original data.

You are given an m x n matrix mat and two integers r and c representing the number of rows and the number of columns of the wanted reshaped matrix.

The reshaped matrix should be filled with all the elements of the original matrix in the same row-traversing order as they were.

If the reshape operation with given parameters is possible and legal, output the new reshaped matrix; Otherwise, output the original matrix.


Example 1:
Input: mat = [[1,2],[3,4]], r = 1, c = 4
Output: [[1,2,3,4]]

Example 2:
Input: mat = [[1,2],[3,4]], r = 2, c = 4
Output: [[1,2],[3,4]]
 

Constraints:
m == mat.length
n == mat[i].length
1 <= m, n <= 100
-1000 <= mat[i][j] <= 1000
1 <= r, c <= 300

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Approach 1: Naive (Using an intermediate 1D Array)
Flatten the original matrix into a 1D array, then fill the new 2D matrix row by row. It's conceptually simple but wastes space.
- Time Complexity: O(m * n)
- Space Complexity: O(m * n) for the intermediate array.

Approach 2: Direct Mapping with Division and Modulo (Optimal)
We can pretend the original 2D matrix is 1D. We iterate from 0 to (m*n) - 1. 
The magic is converting this 1D index i into 2D coordinates for the new matrix.
- Time Complexity: O(m * n)
- Space Complexity: O(1) (excluding the return matrix)

The Magic Formula (/ and %): This is the most important takeaway. 
row = index / columns, col = index % columns. 
Try to trace this manually with a 2x3 matrix. See how the division increments the row only when we've passed enough elements, and the modulo wraps the column around.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N log(Max Distance)) - [Reason: We iterate through N elements in our isPossible function for every log(Max Distance) binary search step.]
- Space Complexity: O(1) - [Reason: No extra space is used, only pointers.]
========================================================================================
*/

// APPROACH 1:
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>>& mat, int r, int c) {
        int m = mat.size();
        int n = mat[0].size();
        
        if (m * n != r * c) return mat;
        
        std::vector<int> flat;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                flat.push_back(mat[i][j]);
            }
        }
        
        std::vector<std::vector<int>> result(r, std::vector<int>(c));
        int k = 0;
        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                result[i][j] = flat[k++];
            }
        }
        return result;
    }
};

// APPROACH 2: 
#include <vector>

class Solution {
public:
    std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>>& mat, int r, int c) {
        int m = mat.size();
        int n = mat[0].size();
        
        // Base case: If the total elements don't match, return original
        if (m * n != r * c) return mat;
        
        std::vector<std::vector<int>> result(r, std::vector<int>(c));
        
        for (int i = 0; i < m * n; i++) {
            // Map 1D index back to 2D indices for both original and new matrices
            int origRow = i / n;
            int origCol = i % n;
            
            int newRow = i / c;
            int newCol = i % c;
            
            result[newRow][newCol] = mat[origRow][origCol];
        }
        
        return result;
    }
};
