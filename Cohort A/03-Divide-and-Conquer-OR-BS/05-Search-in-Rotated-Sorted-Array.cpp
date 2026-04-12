/*
========================================================================================
Problem Name : Search in Rotated Sorted Array (33)
Problem Link : https://leetcode.com/problems/search-in-rotated-sorted-array/description/
========================================================================================

PROBLEM STATEMENT:
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is possibly left rotated at an unknown index k (1 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed).
For example, [0,1,2,4,5,6,7] might be left rotated by 3 indices and become [4,5,6,7,0,1,2].

Given the array nums after the possible rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

You must write an algorithm with O(log n) runtime complexity.

Example 1:
Input: nums = [4,5,6,7,0,1,2], target = 0
Output: 4

Example 2:
Input: nums = [4,5,6,7,0,1,2], target = 3
Output: -1

Example 3:
Input: nums = [1], target = 0
Output: -1
 

Constraints:

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
All values of nums are unique.
nums is an ascending array that is possibly rotated.
-10^4 <= target <= 10^4

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
If you cut a sorted, rotated array in half, at least one half will always be completely sorted.
Our goal is simply to identify which half is sorted, check if our target is inside that sorted half, and if so, search there. If not, discard it.
We look at low, mid, and high. We determine the sorted half by comparing nums[low] and nums[mid].

Why <= on nums[low] <= nums[mid]: The equal sign handles the case where the search space shrinks down to a single element.

----------------------------------------------------------------------------------------
DRY RUN (With Sample Test Case):
Visualizing the Halves: Dry-run [4, 5, 6, 7, 0, 1, 2] targeting 0.
mid is 7. Left half [4, 5, 6, 7] is sorted. 0 is not between 4 and 7.
Therefore, search the right half!

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(log N)
- Space Complexity: O(1)
========================================================================================
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size() - 1;
        // TC => O(logn)
        // SC => O(1)
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (nums[mid] == target) {
                return mid;
            }

            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }
        return -1;
    }
};
