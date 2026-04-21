/*
========================================================================================
Problem Name : Third Maximum Number (414)
Problem Link : https://leetcode.com/problems/third-maximum-number/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums, return the third distinct maximum number in this array. If the third maximum does not exist, return the maximum number.
 

Example 1:
Input: nums = [3,2,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2.
The third distinct maximum is 1.

Example 2:
Input: nums = [1,2]
Output: 2
Explanation:
The first distinct maximum is 2.
The second distinct maximum is 1.
The third distinct maximum does not exist, so the maximum (2) is returned instead.

Example 3:
Input: nums = [2,2,3,1]
Output: 1
Explanation:
The first distinct maximum is 3.
The second distinct maximum is 2 (both 2's are counted together since they have the same value).
The third distinct maximum is 1.
 

Constraints:

1 <= nums.length <= 10^4
-2^31 <= nums[i] <= 2^31 - 1
 
Follow up: Can you find an O(n) solution?

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
[Explain the core logic in plain English. This is where you explain the "Why".]
- Why use this pattern? (e.g., "Since the search space is monotonic, we can use Binary Search.")
- Step 1: Sort the array to ensure stalls are in order.
- Step 2: Set our low pointer to 1 (minimum possible distance) and high pointer to (max - min).
- Step 3: Use a helper function `isPossible()` to check if we can place all cows with at least `mid` distance.

----------------------------------------------------------------------------------------
DRY RUN (With Sample Test Case):
Input: stalls = [1, 2, 4, 8, 9], k = 3
- Attempt 1: mid = 4. Can we place 3 cows? 
  Cow 1 at 1. Cow 2 at 1+4=5 (Closest is 8). Cow 3 at 8+4=12 (Out of bounds). False.
- Attempt 2: mid = 3. Can we place 3 cows?
  Cow 1 at 1. Cow 2 at 1+3=4 (Stall 4). Cow 3 at 4+3=7 (Closest is 8). True!

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N log(Max Distance)) - [Reason: We iterate through N elements in our isPossible function for every log(Max Distance) binary search step.]
- Space Complexity: O(1) - [Reason: No extra space is used, only pointers.]
========================================================================================
*/

