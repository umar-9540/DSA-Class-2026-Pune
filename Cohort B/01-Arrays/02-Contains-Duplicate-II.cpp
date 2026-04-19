/*
========================================================================================
Problem Name : Contains Duplicate II (219)
Problem Link : https://leetcode.com/problems/contains-duplicate-ii/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums and an integer k, return true if there are two distinct indices i and j in the array such that nums[i] == nums[j] and abs(i - j) <= k.
 

Example 1:
Input: nums = [1,2,3,1], k = 3
Output: true

Example 2:
Input: nums = [1,0,1,1], k = 1
Output: true

Example 3:
Input: nums = [1,2,3,1,2,3], k = 2
Output: false
 

Constraints:

1 <= nums.length <= 10^5
-10^9 <= nums[i] <= 10^9
0 <= k <= 10^5

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
APPROACH 1: Brute Force (Time Limit Exceeded)
Compare every element with every other element within a distance of k.
- Time Complexity: O(n * min(n, k))
- Space Complexity: O(1)

APPROACH 2: Hash Map (Storing Indices)
Store the most recently seen index of each number. If we see a number again, check the distance.
- Time Complexity: O(n)
- Space Complexity: O(n)

APPROACH 3: Sliding Window with Hash Set (Most Intuitive Optimal)
Maintain a "window" of size k using a Hash Set. If the window grows larger than k, remove the oldest element.
- Time Complexity: O(n)
- Space Complexity: O(min(n, k))

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(min(n, k))
========================================================================================
*/

// APPROACH 1:
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j <= i + k && j < n; j++) {
                if (nums[i] == nums[j]) {
                    return true;
                }
            }
        }
        return false;
    }
};

// APPROACH 2:
#include <vector>
#include <unordered_map>

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> numMap;
        for (int i = 0; i < nums.size(); i++) {
            if (numMap.count(nums[i]) && i - numMap[nums[i]] <= k) {
                return true;
            }
            numMap[nums[i]] = i; 
        }
        return false;
    }
};

// APPROACH 3:
#include <vector>
#include <unordered_set>

class Solution {
public:
    bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
        std::unordered_set<int> window;
        for (int i = 0; i < nums.size(); i++) {
            if (window.count(nums[i])) {
                return true;
            }
            window.insert(nums[i]);
            if (window.size() > k) {
                window.erase(nums[i - k]);
            }
        }
        return false;
    }
};
