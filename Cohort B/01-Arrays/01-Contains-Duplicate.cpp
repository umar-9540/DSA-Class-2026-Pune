/*
========================================================================================
Problem Name : Contains Duplicate (217)
Problem Link : https://leetcode.com/problems/contains-duplicate/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.


Example 1:
Input: nums = [1,2,3,1]
Output: true
Explanation:
The element 1 occurs at the indices 0 and 3.

Example 2:
Input: nums = [1,2,3,4]
Output: false
Explanation:
All elements are distinct.

Example 3:
Input: nums = [1,1,1,3,3,4,3,2,4,2]
Output: true


Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
APPROACH 1: Sorting
Simply, if we sort all numbers, we can solve this question easily, because all duplicate numbers will be adjacent numbers.
Then we iterate through the input array from index 1 and check previous index every time.
- Time complexity: O(N * logN) due to sort()
- Space complexity: O(1)

APPROACH 2: Set
We use set. Every time we find a new number, we will check set.
And if we have the same number in set, we should return True.
- Time complexity: O(n)
- Space complexity: O(n) In the worst case, numbers are all unique.

APPROACH 3: Check length
If the length of the input array created by executing set is shorter than the original input array, it indicates that we have duplicate numbers.
- Time complexity: O(n)
- Space complexity: O(n)

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(n) In the worst case, numbers are all unique.
========================================================================================
*/

// APPROACH 1:
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1]) {
                return true;
            }
        }
        
        return false;        
    }
};

// APPROACH 2:
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> numSet;

        for (int n : nums) {
            if (numSet.find(n) != numSet.end()) {
                return true;
            }
            numSet.insert(n);
        }
        
        return false;        
    }
};

// APPROACH 3:
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        return numSet.size() < nums.size();        
    }
};
