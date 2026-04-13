/*
========================================================================================
Problem Name : Find All Duplicates in an Array (442)
Problem Link : https://leetcode.com/problems/find-all-duplicates-in-an-array/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.

You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output

Example 1:
Input: nums = [4,3,2,7,8,2,3,1]
Output: [2,3]

Example 2:
Input: nums = [1,1,2]
Output: [1]

Example 3:
Input: nums = [1]
Output: []
 

Constraints:

n == nums.length
1 <= n <= 10^5
1 <= nums[i] <= n
Each element in nums appears once or twice.

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Approach 1: Brute Force / Hash Map
Brute Force: Sort and check adjacent elements. O(N * log N) time. Fails constraint.
Better: Use a Hash Set or an external frequency array. O(N) time, but O(N) space. Fails the O(1) space constraint.

Approach 2: Optimal (In-Place Negation)
Concept: We use the array itself to track what we've seen. When we read a number x, we go to index |x| - 1 and multiply the number sitting there by -1.
If we go to an index and the number sitting there is already negative, it means we must have visited this index before—which means the number x is a duplicate!

----------------------------------------------------------------------------------------
DRY RUN (With Sample Test Case):
Input: stalls = [1, 2, 4, 8, 9], k = 3
- Attempt 1: mid = 4. Can we place 3 cows? 
  Cow 1 at 1. Cow 2 at 1+4=5 (Closest is 8). Cow 3 at 8+4=12 (Out of bounds). False.
- Attempt 2: mid = 3. Can we place 3 cows?
  Cow 1 at 1. Cow 2 at 1+3=4 (Stall 4). Cow 3 at 4+3=7 (Closest is 8). True!

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N) - We iterate through the array exactly once.
- Space Complexity: O(1) - We only modify the input array in place (ignoring the output array).
========================================================================================
*/

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ans;
        // TC => O(n)
        // SC => O(1)
        for (int i = 0; i < nums.size(); i++) {
            int val = abs(nums[i]);
            int targetIndex = val - 1;

            if (nums[targetIndex] < 0) {
                ans.push_back(val);
            }

            nums[targetIndex] = -nums[targetIndex];
        }
        return ans;
    }
};
