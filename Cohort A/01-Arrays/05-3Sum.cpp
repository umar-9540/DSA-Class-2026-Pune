/*
========================================================================================
Problem Name : 3Sum (15)
Problem Link : https://leetcode.com/problems/3sum/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:
Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation: 
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.

Example 2:
Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:
Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
 

Constraints:

3 <= nums.length <= 3000
-10^5 <= nums[i] <= 10^5

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
If you need to find three numbers that sum to 0, A + B + C = 0, what happens if you just pick A and lock it in place?
The equation becomes B + C = -A. Suddenly, this is just the classic Two Sum problem! 
We reduced a 3D problem into a 1D loop + a 2D problem.

Approach 1: Brute Force (Three Nested Loops)
Concept: Check every possible triplet. Sort each triplet and put it in a Set to remove duplicates.
Time Complexity: O(N^3 * log(text{unique triplets})).
Space Complexity: O(text{Number of unique triplets}).

Approach 2: Optimal (Sorting + Two Pointers)
Concept: We sort the array first. Sorting does two amazing things: it allows us to use the Two Pointer technique to find B + C = -A in O(N) time,
AND it groups duplicate numbers together so we can easily skip them.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N * log N) for sorting + O(N^2) for the nested loops = O(N^2).
- Space Complexity: O(1).
========================================================================================
*/

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        set<vector<int>> st;

        sort(nums.begin(), nums.end());
        int n = nums.size();
        // TC => O(n * logn)
        // SC => O(1)
        for (int i = 0; i < n; i++) {
            int left = i + 1, right = n - 1;

            while (left < right) {
                int sum = nums[i] + nums[left] + nums[right];

                if (sum < 0) left++;

                else if (sum > 0) right--;

                else {
                    vector<int> temp = {nums[i], nums[left], nums[right]};
                    st.insert(temp);
                    left++;
                    right--;
                }
            }
        }
        vector<vector<int>> ans(st.begin(), st.end());
        return ans;
    }
};
