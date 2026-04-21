/*
========================================================================================
Problem Name : Find All Numbers Disappeared in an Array (448)
Problem Link : https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/description/
========================================================================================

PROBLEM STATEMENT:
Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
 

Example 1:
Input: nums = [4,3,2,7,8,2,3,1]
Output: [5,6]

Example 2:
Input: nums = [1,1]
Output: [2]
 
Constraints:
n == nums.length
1 <= n <= 10^5
1 <= nums[i] <= n
 

Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Approach 1: Hash Set (Extra Space)
Put all numbers in a set, then check which numbers from 1 to N are missing.
- Time Complexity: O(n)
- Space Complexity: O(n)

Approach 2: In-Place State Change (Optimal)
Since numbers are strictly between 1 and N, we can use the values as indices.
We iterate through the array, and when we see value x, we mark the element at index x-1 as negative. Missing numbers will be the indices that remain positive.
- Time Complexity: O(n)
- Space Complexity: O(1) (excluding the return array)

The Core Trick: 1 <= nums[i] <= n
"Whenever you see this constraint, your brain should immediately scream: I can use the values as indices!"

Why absolute value? (abs()): 
Walk through an example. If index 2 is made negative by a previous step, but we later need to read the value at index 2 to find its corresponding index, reading a negative value will cause an out-of-bounds error.
The absolute value restores the original data.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(1) (excluding the return array)
========================================================================================
*/

// APPROACH 1:
#include <vector>
#include <unordered_set>

class Solution {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::unordered_set<int> numSet(nums.begin(), nums.end());
        std::vector<int> result;
        for (int i = 1; i <= nums.size(); i++) {
            if (!numSet.count(i)) {
                result.push_back(i);
            }
        }
        return result;
    }
};

// APPROACH 2:
#include <vector>
#include <cmath>

class Solution {
public:
    std::vector<int> findDisappearedNumbers(std::vector<int>& nums) {
        std::vector<int> result;
        for (int i = 0; i < nums.size(); i++) {
            int index = std::abs(nums[i]) - 1;
            if (nums[index] > 0) {
                nums[index] = -nums[index];
            }
        }
        
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) {
                result.push_back(i + 1);
            }
        }
        return result;
    }
};
