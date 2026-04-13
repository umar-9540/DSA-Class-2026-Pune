/*
========================================================================================
Problem Name : Maximum Distance in Arrays (624)
Problem Link : https://leetcode.com/problems/maximum-distance-in-arrays/description/
========================================================================================

PROBLEM STATEMENT:
You are given m arrays, where each array is sorted in ascending order.

You can pick up two integers from two different arrays (each array picks one) and calculate the distance.
We define the distance between two integers a and b to be their absolute difference |a - b|.

Return the maximum distance.

Example 1:
Input: arrays = [[1,2,3],[4,5],[1,2,3]]
Output: 4
Explanation: One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.

Example 2:
Input: arrays = [[1],[1]]
Output: 0
 

Constraints:

m == arrays.length
2 <= m <= 10^5
1 <= arrays[i].length <= 500
-10^4 <= arrays[i][j] <= 10^4
arrays[i] is sorted in ascending order.
There will be at most 10^5 integers in all the arrays.


----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
If you want to find the maximum possible difference between two numbers, what kind of numbers are you looking for? The absolute biggest number and the absolute smallest number!
The arrays are already sorted. This means we don't have to search the arrays at all. The smallest number in any array is always at index 0, and the largest is always at the last index.
The only trap? The problem explicitly states the two numbers must come from different arrays.

Approach 1: Brute Force (Comparing all pairs of arrays)
Concept: We can pair every array with every other array. 
For each pair, we calculate the difference between Array A's minimum and Array B's maximum, and vice versa.
Time Complexity: O(M²) where M is the number of arrays.
Space Complexity: O(1).

Approach 2: Optimal (One-Pass Greedy)
Concept: Instead of comparing every array with every other array, we can just keep track of the global_min and global_max we have seen so far as we iterate through the arrays.
When we are looking at the current array, we calculate the distance using its boundaries against our global_min and global_max.
Because the globals only contain data from previous arrays, we are 100% guaranteed that the numbers come from different arrays! After calculating, we update our globals.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(M) - We loop through the list of arrays exactly once.
- Space Complexity: O(1)
========================================================================================
*/

class Solution {
public:
    int maxDistance(vector<vector<int>>& arrays) {
        int globalMin = arrays[0].front();
        int globalMax = arrays[0].back();
        int maxDist = 0;

        for (int i = 1; i < arrays.size(); i++) {
            int currMin = arrays[i].front(); 
            int currMax = arrays[i].back();

            maxDist = max(maxDist, abs(currMax - globalMin));
            maxDist = max(maxDist, abs(globalMax - currMin));

            // int dist1 = abs(currMax - globalMin);
            // int dist2 = abs(globalMax - currMin);
            // maxDist = max(maxDist, max(dist1, dist2));

            globalMin = min(globalMin, currMin);
            globalMax = max(globalMax, currMax);
        }
        return maxDist;
    }
};
