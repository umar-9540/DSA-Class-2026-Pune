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
The Guard Clause: Always check if (m * n != r * c) first. It's a fundamental sanity check.

Approach 1: Naive (Using an intermediate 1D Array)
Flatten the original matrix into a 1D array, then fill the new 2D matrix row by row. It's conceptually simple but wastes space.

Approach 2: Direct Mapping with Division and Modulo
We can pretend the original 2D matrix is 1D. We iterate from 0 to (m*n) - 1.
The magic is converting this 1D index i into 2D coordinates for the new matrix.
The Magic Formula (/ and %): row = index / columns, col = index % columns

----------------------------------------------------------------------------------------
COMPLEXITY:
APPROACH 1:
- Time Complexity: O(m * n)
- Space Complexity: O(m * n) for the intermediate array.

APPROACH 2:
- Time Complexity: O(m * n)
- Space Complexity: O(1) [excluding the return matrix]
========================================================================================
*/

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
        
        int m = mat.size();
        int n = mat[0].size();

        if (m * n != r * c) {
            return mat;
        }
        // APPROACH 1
        // vector<int> flatArray(m * n, 0);
        // int k = 0;
        // for (int i = 0; i < m; i++) {
        //     for (int j = 0; j < n; j++) {
        //         flatArray[k] = mat[i][j];
        //         k++;
        //     }
        // }

        // // TC => O(m * n)
        // // SC => O(m * n)
        // k = 0;
        // vector<vector<int>> result(r, vector<int>(c, 0));
        // for (int i = 0; i < r; i++) {
        //     for (int j = 0; j < c; j++) {
        //         result[i][j] = flatArray[k];
        //         k++;
        //     }
        // }
        // return result;


        // APPROACH 2
        vector<vector<int>> result(r, vector<int>(c, 0));
        for (int i = 0; i < m * n; i++) {
            int originalRow = i / n;
            int originalCol = i % n;

            int newRow = i / c;
            int newCol = i % c;

            result[newRow][newCol] = mat[originalRow][originalCol];
        }
        // TC => O(m * n)
        // SC => O(1)
        return result;
    }
};
