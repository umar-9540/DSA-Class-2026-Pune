/*
========================================================================================
Problem Name : Missing Number (268)
Problem Link : https://leetcode.com/problems/missing-number/description/
========================================================================================

PROBLEM STATEMENT:
Given an array nums containing n distinct numbers in the range [0, n], return the only number in the range that is missing from the array.

 
Example 1:
Input: nums = [3,0,1]
Output: 2
Explanation:
n = 3 since there are 3 numbers, so all numbers are in the range [0,3]. 
2 is the missing number in the range since it does not appear in nums.

Example 2:
Input: nums = [0,1]
Output: 2
Explanation:
n = 2 since there are 2 numbers, so all numbers are in the range [0,2].
2 is the missing number in the range since it does not appear in nums.

Example 3:
Input: nums = [9,6,4,2,3,5,7,0,1]
Output: 8
Explanation:
n = 9 since there are 9 numbers, so all numbers are in the range [0,9].
8 is the missing number in the range since it does not appear in nums.

Constraints:

n == nums.length
1 <= n <= 10^4
0 <= nums[i] <= n
All the numbers of nums are unique.
 

Follow up: Could you implement a solution using only O(1) extra space complexity and O(n) runtime complexity?

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
APPROACH 1: Using Vector
Will iterate over the nums and will put elements in the v vector(size of n+1).
At last will iterate in v and will return index of the element which is still -1.
- Time complexity: O(n)
- Space complexity: O(n)

APPROACH 2: XOR Operation
XOR operation we should be known:
- If we XOR something with 0, it will return the same number. For example => 5 ^ 0 = 5
- If we XOR two same numbers, the output will be 0. For example => 5 ^ 5 = 0
We will xor each number present in the nums to itself.
Then will xor it with every number present in the range [0,n].
- Time complexity: O(n)
- Space complexity: O(1)

APPROACH 3(Sum of all elememnts)
First calculate sum of all elements in the range[0,n].
Then calculate sum of nums.
If we subtrate both we will get the missing number.
- Time complexity: O(n)
- Space complexity: O(1)

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(n)
- Space Complexity: O(1)
========================================================================================
*/

// APPROACH 1:
class Solution {
public:
    int missingNumber(vector<int>& nums) {   
        int n = nums.size();
        vector<int> v(n + 1, -1);

        for (int i = 0; i < n; i++) {
            v[nums[i]] = nums[i];
        }

        for (int i = 0; i < v.size(); i++) {
            if (v[i] == -1) {
                return i;
            }
        }
        return -1;
    }
};

// APPROACH 2: XOR Operation
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int xorValue = 0;

        for (int i = 1; i <= n; i++) {
            xorValue ^= i;
        }

        for (int i = 0; i < n; i++) {
            xorValue ^= nums[i];
        }

        return xorValue;
    }
};

// APPROACH 3: Sum of all Numbers
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int expectedSum = (n * (n + 1)) / 2;

        int actualSum = 0;
        for (int num : nums){
            actualSum += num;
        }

        return expectedSum - actualSum;

        return 0;
    }
};
