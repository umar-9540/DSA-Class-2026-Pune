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
Approach 1: Sorting
Sort the array descending and iterate, counting unique elements.
- Time Complexity: O(n * log n)
- Space Complexity: O(1) or O(n) depending on the sorting algorithm.

Approach 2: Three Pointers / Variables
Keep track of the top three distinct maximums directly. Use long long to avoid issues with INT_MIN existing in the array.
- Time Complexity: O(n)
- Space Complexity: O(1)

The INT_MIN Trap: The constraint is -2^31 <= nums[i]. If INT_MIN is in the array, using INT_MIN as an "empty" flag will fail. Upgrading to long long elegantly solves this.

The "Shift" Logic: When a new first max is found, second becomes third, and first becomes second.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(1)
========================================================================================
*/

// APPROACH 1:
#include <vector>
#include <algorithm>

class Solution {
public:
    int thirdMax(std::vector<int>& nums) {
        std::sort(nums.rbegin(), nums.rend());
        int distinctCount = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != nums[i - 1]) {
                distinctCount++;
            }
            if (distinctCount == 3) {
                return nums[i];
            }
        }
        return nums[0];
    }
};

// APPROACH 2:
#include <vector>
#include <climits>

class Solution {
public:
    int thirdMax(std::vector<int>& nums) {
        long long first = LLONG_MIN;
        long long second = LLONG_MIN;
        long long third = LLONG_MIN;
        
        for (int num : nums) {
            if (num == first || num == second || num == third) continue;
            
            if (num > first) {
                third = second;
                second = first;
                first = num;
            } else if (num > second) {
                third = second;
                second = num;
            } else if (num > third) {
                third = num;
            }
        }
        
        return third == LLONG_MIN ? first : third;
    }
};
