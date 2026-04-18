/*
========================================================================================
Problem Name : Patching Array (330)
Problem Link : https://leetcode.com/problems/patching-array/description/
========================================================================================

PROBLEM STATEMENT:
Given a sorted integer array nums and an integer n, add/patch elements to the array such that any number in the range [1, n] inclusive can be formed by the sum of some elements in the array.

Return the minimum number of patches required.


Example 1:

Input: nums = [1,3], n = 6
Output: 1
Explanation:
Combinations of nums are [1], [3], [1,3], which form possible sums of: 1, 3, 4.
Now if we add/patch 2 to nums, the combinations are: [1], [2], [3], [1,3], [2,3], [1,2,3].
Possible sums are 1, 2, 3, 4, 5, 6, which now covers the range [1, 6].
So we only need 1 patch.

Example 2:

Input: nums = [1,5,10], n = 20
Output: 2
Explanation: The two patches can be [2, 4].

Example 3:

Input: nums = [1,2,2], n = 5
Output: 0
 

Constraints:

1 <= nums.length <= 1000
1 <= nums[i] <= 10^4
nums is sorted in ascending order.
1 <= n <= 2^31 - 1

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Let's maintain a variable called "miss". "miss" represents the smallest sum we CANNOT currently form.
Initially, we haven't added anything, so the smallest positive sum we can't form is miss = 1.
This implies that we can currently form all numbers in the continuous range [1, miss - 1].
Now, look at the next number in our given array, let's call it X. We have two scenarios:

Scenario A: The number X is helpful (X <= miss). If X is less than or equal to miss, we can add X to all the sums we could already form.
Example: If our range of sums is [1, 5] (so miss is 6), and our next array number is 4.We can now form:Our old sums: [1, 5] => Our old sums + 4: [1+4, 5+4] => [5, 9] 
Combined, we can now form everything seamlessly from [1, 9].
Formula: Our new miss simply becomes miss + X. No patch needed!

Scenario B: The number X is unhelpful, or the array is empty (X > miss)
If X is strictly greater than miss, there is a gap!
Example: If our range is [1, 5] (so miss is 6), and the next number is 10. We cannot form 6, 7, 8, or 9.
We must patch a number to the array to fix this gap.
The Greedy Choice: What is the best number to patch? To maximize our future reach, we should patch the largest number possible that still closes the gap.
That number is exactly miss.If we patch miss (which is 6), we extend our range from [1, miss - 1] to [1, miss + miss - 1].
So our new miss doubles: miss = miss + miss. We record 1 patch, and we DO NOT advance the array index, because we still haven't processed the number 10.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(Size of array + log N). Because miss doubles every time we patch, it reaches the target N logarithmically.
- Space Complexity: O(1).
========================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

int minPatches(vector<int>& nums, int n) {
    long long miss = 1; // Smallest sum we cannot form. Use long long to avoid overflow!
    int patches = 0;
    int i = 0;          // Index for nums array
    
    while (miss <= n) {
        // Scenario A: Current number extends our range seamlessly
        if (i < nums.size() && nums[i] <= miss) {
            miss += nums[i];
            i++; // Move to the next number in the array
        } 
        // Scenario B: Gap detected! We must patch.
        else {
            miss += miss; // Greedily patch the number 'miss' itself
            patches++;    // Record the patch
            // Note: We DO NOT increment 'i' because we still haven't used nums[i]
        }
    }
    
    return patches;
}
