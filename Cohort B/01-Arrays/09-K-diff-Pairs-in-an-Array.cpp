/*
========================================================================================
Problem Name : K-diff Pairs in an Array (532)
Problem Link : https://leetcode.com/problems/k-diff-pairs-in-an-array/description/
========================================================================================

PROBLEM STATEMENT:
Given an array of integers nums and an integer k, return the number of unique k-diff pairs in the array.
A k-diff pair is an integer pair (nums[i], nums[j]), where the following are true:

0 <= i, j < nums.length
i != j
|nums[i] - nums[j]| == k
Notice that |val| denotes the absolute value of val.


Example 1:
Input: nums = [3,1,4,1,5], k = 2
Output: 2
Explanation: There are two 2-diff pairs in the array, (1, 3) and (3, 5).
Although we have two 1s in the input, we should only return the number of unique pairs.

Example 2:
Input: nums = [1,2,3,4,5], k = 1
Output: 4
Explanation: There are four 1-diff pairs in the array, (1, 2), (2, 3), (3, 4) and (4, 5).

Example 3:
Input: nums = [1,3,1,5,4], k = 0
Output: 1
Explanation: There is one 0-diff pair in the array, (1, 1).
 

Constraints:

1 <= nums.length <= 10^4
-10^7 <= nums[i] <= 10^7
0 <= k <= 10^7

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Approach 1: Brute Force with a Hash Set (Time Limit Exceeded)
Check every possible pair using nested loops.
To handle the "unique pairs" constraint, we can store the smaller number of the valid pair in a Hash Set to ensure we don't count it twice.
- Time Complexity: O(n^2)
- Space Complexity: O(n) (for the set to store unique pairs)

Approach 2: Sorting + Two Pointers (O(1) Space)
Sort the array first. Because it's sorted, we can use two pointers (left and right) moving in the same direction.
We look for a difference of exactly k. If the difference is too small, we expand the window (right++).
If it's too big, we shrink it (left++).
- Time Complexity: O(n * log n) (due to sorting)
- Space Complexity: O(1) (ignoring the memory used by the sorting algorithm)

Approach 3: Frequency Map / Hash Map (Optimal Time)
Instead of sorting, we can count the frequency of each number using a Hash Map.
We then iterate through the unique numbers (the keys in our map).

If k > 0: We just check if number + k exists in the map.
If k == 0: We check if the frequency of the number is greater than 1.
- Time Complexity: O(n)
- Space Complexity: O(n)

The k = 0 Trap: This is the most critical learning moment of the problem. 
"If k = 2, and my array is [1, 5], I look for 1 + 2 = 3. But what if k = 0 and my array is [1, 5]? I look for 1 + 0 = 1.
But wait, 1 is already in the array... so does [1, 5] have a pair?"
This perfectly illustrates why a simple Hash Set (which just tracks "have I seen this number?") fails. 
To find a difference of 0, we need two distinct indices with the same value. That is exactly why we upgrade from a Hash Set to a Hash Map to track frequency.

Why not num - k?: In Approach 3, you might ask why we only check for num + k and not num - k. 
If we have (1, 3) and k = 2. When we are at 1, we find 3. Later, when we are at 3, if we looked backwards for 1, we would double-count the pair! 
By strictly looking "forward" (num + k), we naturally ensure every pair is counted exactly once.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(n)
========================================================================================
*/

// APPROACH 1:
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

class Solution {
public:
    int findPairs(std::vector<int>& nums, int k) {
        std::unordered_set<int> uniquePairs;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (std::abs(nums[i] - nums[j]) == k) {
                    // Always insert the smaller element to uniquely identify the pair
                    uniquePairs.insert(std::min(nums[i], nums[j]));
                }
            }
        }
        
        return uniquePairs.size();
    }
};

// APPROACH 2:
#include <vector>
#include <algorithm>

class Solution {
public:
    int findPairs(std::vector<int>& nums, int k) {
        std::sort(nums.begin(), nums.end());
        int left = 0, right = 1;
        int count = 0;
        
        while (left < nums.size() && right < nums.size()) {
            // Ensure pointers don't overlap, or if the diff is too small
            if (left == right || nums[right] - nums[left] < k) {
                right++;
            } 
            // If the diff is too big
            else if (nums[right] - nums[left] > k) {
                left++;
            } 
            // We found a match!
            else {
                count++;
                left++;
                // Skip duplicates for the left pointer to ensure unique pairs
                while (left < nums.size() && nums[left] == nums[left - 1]) {
                    left++;
                }
            }
        }
        
        return count;
    }
};

// APPROACH 3:
#include <vector>
#include <unordered_map>

class Solution {
public:
    int findPairs(std::vector<int>& nums, int k) {
        std::unordered_map<int, int> freqMap;
        for (int num : nums) {
            freqMap[num]++;
        }
        
        int count = 0;
        // Iterate through the unique keys in the map
        for (auto& pair : freqMap) {
            int num = pair.first;
            int frequency = pair.second;
            
            if (k > 0 && freqMap.count(num + k)) {
                count++;
            } else if (k == 0 && frequency > 1) {
                count++;
            }
        }
        
        return count;
    }
};
