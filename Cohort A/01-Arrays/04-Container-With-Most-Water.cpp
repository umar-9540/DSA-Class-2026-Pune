/*
========================================================================================
Problem Name : Container With Most Water (11)
Problem Link : https://leetcode.com/problems/container-with-most-water/description/
========================================================================================

PROBLEM STATEMENT:
You are given an integer array height of length n. There are n vertical lines drawn such that the two endpoints of the ith line are (i, 0) and (i, height[i]).
Find two lines that together with the x-axis form a container, such that the container contains the most water.
Return the maximum amount of water a container can store.

Notice that you may not slant the container.

Example 1:
Input: height = [1,8,6,2,5,4,8,3,7]
Output: 49
Explanation: The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

Example 2:
Input: height = [1,1]
Output: 1

Constraints:

n == height.length
2 <= n <= 10^5
0 <= height[i] <= 10^4

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Draw two uneven vertical lines on the board. If I pour water in here, which line determines how high the water can go before spilling?
The answer is always the shorter line.
The formula for the water is simple: Area = width * min(height_left, height_right).

To maximize this, we should intuitively start with the widest possible container (left pointer at the start, right pointer at the end).
Now, how do we find a better one?
If we move the taller line inward, the width decreases, and the height is still restricted by the shorter line—our area can only shrink! 
The only logical way to potentially get a bigger area is to abandon the shorter line and hope the next line is much taller.

Approach 1: Brute Force
Concept: Check every possible pair of lines and calculate the area. Keep track of the maximum.

Time Complexity: O(N²).
Space Complexity: O(1).

Approach 2: Optimal (Two Pointers)
Concept: Place a pointer at the beginning (left) and one at the end (right). Calculate the area. 
Then, move the pointer that points to the shorter line inward. Repeat until the pointers meet.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N) - Each line is evaluated at most once.
- Space Complexity: O(1)
========================================================================================
*/

class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int maxArea = 0;
        // TC => O(n)
        // SC => O(1)
        while (left < right) {
            int width = right - left;
            int minHeight = min(height[left], height[right]);

            int currArea = width * minHeight;
            maxArea = max(maxArea, currArea);

            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        return maxArea;
    }
};
