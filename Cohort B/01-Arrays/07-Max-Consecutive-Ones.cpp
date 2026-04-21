/*
========================================================================================
Problem Name : Max Consecutive Ones (485)
Problem Link : https://leetcode.com/problems/max-consecutive-ones/description/
========================================================================================

PROBLEM STATEMENT:
Given a binary array nums, return the maximum number of consecutive 1's in the array.


Example 1:
Input: nums = [1,1,0,1,1,1]
Output: 3
Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.

Example 2:
Input: nums = [1,0,1,1,0,1]
Output: 2

Constraints:
1 <= nums.length <= 10^5
nums[i] is either 0 or 1.

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Single Pass Linear Scan:
Keep a running count of 1s. Reset the count to 0 when you hit a 0. Continuously update the maximum count.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(1)
========================================================================================
*/

// APPROACH 2:
#include <vector>
#include <algorithm>

class Solution {
public:
    int findMaxConsecutiveOnes(std::vector<int>& nums) {
        int maxCount = 0;
        int currentCount = 0;
        
        for (int num : nums) {
            if (num == 1) {
                currentCount++;
                maxCount = std::max(maxCount, currentCount);
            } else {
                currentCount = 0;
            }
        }
        
        return maxCount;
    }
};
