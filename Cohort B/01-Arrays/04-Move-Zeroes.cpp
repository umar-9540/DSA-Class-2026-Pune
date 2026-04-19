/*
========================================================================================
Problem Name : Move Zeroes (283)
Problem Link : https://leetcode.com/problems/move-zeroes/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
Note that you must do this in-place without making a copy of the array.


Example 1:
Input: nums = [0,1,0,3,12]
Output: [1,3,12,0,0]

Example 2:
Input: nums = [0]
Output: [0]
 

Constraints:
1 <= nums.length <= 10^4
-2^31 <= nums[i] <= 2^31 - 1
 

Follow up: Could you minimize the total number of operations done?

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Using two pointer to swap two numbers.
We want to move all zeroes to right places. In that case, basically, we have two choice:
- move all zeros to right places OR
- move all non zero numbers to left places

First of all, we have left pointer and right pointer.
We use the second idea(= move all non zero numbers to left places) above.
Why?
That's because now we have the two pointers at index 0, so seem like we can handle algorithm easily if we move non zero numbers to left position.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time complexity: O(n)
- Space complexity: O(1)
========================================================================================
*/

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
         int j = 0;

        for(int i = 0; i < nums.size(); i++)
        {
            if(nums[i] != 0)
            {
                swap(nums[i], nums[j]);
                j++;
            }
        }
    }
};
