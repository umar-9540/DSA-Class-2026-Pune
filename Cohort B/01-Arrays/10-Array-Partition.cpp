/*
========================================================================================
Problem Name : Array Partition (561)
Problem Link : https://leetcode.com/problems/array-partition/description/
========================================================================================

PROBLEM STATEMENT:
Given an integer array nums of 2n integers, group these integers into n pairs (a1, b1), (a2, b2), ..., (an, bn) such that the sum of min(ai, bi) for all i is maximized. Return the maximized sum.
 

Example 1:
Input: nums = [1,4,3,2]
Output: 4
Explanation: All possible pairings (ignoring the ordering of elements) are:
1. (1, 4), (2, 3) -> min(1, 4) + min(2, 3) = 1 + 2 = 3
2. (1, 3), (2, 4) -> min(1, 3) + min(2, 4) = 1 + 2 = 3
3. (1, 2), (3, 4) -> min(1, 2) + min(3, 4) = 1 + 3 = 4
So the maximum possible sum is 4.

Example 2:
Input: nums = [6,2,6,5,1,2]
Output: 9
Explanation: The optimal pairing is (2, 1), (2, 5), (6, 6). min(2, 1) + min(2, 5) + min(6, 6) = 1 + 2 + 6 = 9.
 

Constraints:
1 <= n <= 10^4
nums.length == 2 * n
-10^4 <= nums[i] <= 10^4

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Approach 1: Sorting (The Intuitive Greedy Choice)
To maximize the sum of minimums, we cannot let large numbers be paired with very small numbers (because the large number's value is completely wasted).
Therefore, we must pair numbers that are closest to each other. Sorting perfectly achieves this.
- Time Complexity: O(n * log n)
- Space Complexity: O(1) or O(n) depending on the underlying sorting algorithm used by std::sort.

Approach 2: Counting Sort (O(n) Optimization)
See the constraints: -10^4 <= nums[i] <= 10^4. The range of possible numbers is very small (20,001).
Whenever constraints are this small, we can use an array to count frequencies and skip the O(n log n) comparison sort!
- Time Complexity: O(n + K), where K is the range of values (20001). This simplifies to O(n).
- Space Complexity: O(K) for the frequency array.

The "Wasted Value" Concept: 
See the array [1, 100, 2, 99]. Try to pair (1, 100) and (2, 99). The minimums are 1 + 2 = 3.
The 100 and 99 were completely wasted. This visual proves why pairing adjacent sorted elements is the only way to "save" the high values.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n + K), where K is the range of values (20001). This simplifies to O(n).
- Space Complexity: O(K) for the frequency array.
========================================================================================
*/

// APPROACH 1:
#include <vector>
#include <algorithm>

class Solution {
public:
    int arrayPairSum(std::vector<int>& nums) {
        // Sort the array in ascending order
        std::sort(nums.begin(), nums.end());
        int sum = 0;
        
        // Since the array is sorted, pairing adjacent elements is optimal.
        // We only need to sum the first element of every pair (index 0, 2, 4...)
        for (int i = 0; i < nums.size(); i += 2) {
            sum += nums[i];
        }
        
        return sum;
    }
};

// APPROACH 2:
#include <vector>

class Solution {
public:
    int arrayPairSum(std::vector<int>& nums) {
        // The range is -10000 to 10000, so we need an array of size 20001
        // We use an offset of 10000 to handle negative numbers as array indices.
        std::vector<int> freq(20001, 0);
        for (int num : nums) {
            freq[num + 10000]++;
        }
        
        int sum = 0;
        bool pickNext = true; // Flag to tell us when to pick a number
        
        for (int i = 0; i <= 20000; i++) {
            while (freq[i] > 0) {
                if (pickNext) {
                    sum += (i - 10000); // Remove offset when adding to sum
                }
                pickNext = !pickNext; // Flip the flag
                freq[i]--;
            }
        }
        
        return sum;
    }
};
