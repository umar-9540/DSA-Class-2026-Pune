/*
========================================================================================
Problem Name : Maximum Sum Circular Subarray (918)
Problem Link : https://leetcode.com/problems/maximum-sum-circular-subarray/description/
========================================================================================

PROBLEM STATEMENT:
Given a circular integer array nums of length n, return the maximum possible sum of a non-empty subarray of nums.

A circular array means the end of the array connects to the beginning of the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i - 1 + n) % n].

A subarray may only include each element of the fixed buffer nums at most once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.


Example 1:
Input: nums = [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3.

Example 2:
Input: nums = [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.

Example 3:
Input: nums = [-3,-2,-3]
Output: -2
Explanation: Subarray [-2] has maximum sum -2.
 

Constraints:

n == nums.length
1 <= n <= 3 * 10^4
-3 * 10^4 <= nums[i] <= 3 * 10^4

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Think about the standard Kadane’s Algorithm, which easily finds the maximum subarray if it sits beautifully in the middle of the array.
But what if the biggest sum wraps around the edges?

If the best subarray wraps around the edges (like taking the two 5s from array [5, -3, 5]), what is left sitting in the middle?
The answer: A contiguous chunk of numbers we DID NOT select.

If we want the edge pieces we selected to be as LARGE as possible, the unselected middle piece must be as SMALL as possible!
Therefore, we have two possibilities for the answer:

The Normal Case: The max subarray is just in the middle (found using normal Kadane's).
The Circular Case: The max subarray wraps around. The formula for this is simply: Total Sum of Array - Minimum Subarray Sum.

Our final answer is just the maximum of these two possibilities!

Approach 1: Brute Force (The Modulo Trick)
Concept: If we don't know any fancy algorithms, how do we systematically check every single circular subarray?
We treat every element as a starting point, and we loop forward N times. To prevent our index from going out of bounds, we use the modulo operator % N.
If the array size is 5, and we are at index 4, (4 + 1) % 5 = 0, which beautifully loops us back to the start!
Time Complexity: O(N^2) — We check subarrays of length 1 through N for every single starting position.
Space Complexity: O(1) — No extra arrays are used.

Approach 2: Optimal (Double Kadane's Algorithm)
Concept: We can do everything we need in one single O(N) pass. We will keep track of a running total_sum.
At the same time, we will run Kadane's algorithm to find the max_sum (for the normal case) AND a flipped version of Kadane's to find the min_sum (for the circular case).
Time Complexity: O(N) — We traverse the array exactly once.
Space Complexity: O(1) — We only use a few integer tracking variables.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N) — We traverse the array exactly once.
- Space Complexity: O(1) — We only use a few integer tracking variables.
========================================================================================
*/

// APPROACH 1
#include <vector>
#include <algorithm>
using namespace std;

int maxSubarraySumCircularBrute(vector<int>& nums) {
    int n = nums.size();
    int maxSum = nums[0];
    
    // 'i' is the starting index of our subarray
    for (int i = 0; i < n; i++) {
        int currentSum = 0;
        
        // 'len' is how many elements we include (up to n elements)
        for (int len = 0; len < n; len++) {
            // Use modulo to wrap around the array safely
            currentSum += nums[(i + len) % n];
            maxSum = max(maxSum, currentSum);
        }
    }
    
    return maxSum;
}

// APPROACH 2
#include <vector>
#include <algorithm>
using namespace std;

int maxSubarraySumCircular(vector<int>& nums) {
    int total_sum = 0;
    
    // Variables for standard Kadane's (Max Subarray)
    int curr_max = 0;
    int max_sum = nums[0];
    
    // Variables for flipped Kadane's (Min Subarray)
    int curr_min = 0;
    int min_sum = nums[0];
    
    for (int num : nums) {
        total_sum += num;
        
        // 1. Kadane's for Maximum Subarray
        curr_max = max(curr_max + num, num);  // Do I add 'num' to my existing max sequence, or start a new sequence at 'num'?
        max_sum = max(max_sum, curr_max);
        
        // 2. Kadane's for Minimum Subarray
        curr_min = min(curr_min + num, num);  // Do I add 'num' to my existing min sequence, or start a new sequence at 'num'?
        min_sum = min(min_sum, curr_min);
    }
    
    // EDGE CASE: What if ALL numbers are negative?
    // If all numbers are negative, max_sum will be the smallest negative number.
    // However, total_sum will equal min_sum, meaning (total_sum - min_sum) = 0.
    // The problem requires a NON-EMPTY subarray, so returning 0 is invalid here.
    if (max_sum < 0) {
        return max_sum; 
    }
    
    return max(max_sum, total_sum - min_sum);
}
