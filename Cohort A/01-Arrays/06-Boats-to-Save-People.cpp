/*
========================================================================================
Problem Name : Boats to Save People (881)
Problem Link : https://leetcode.com/problems/boats-to-save-people/description/
========================================================================================

PROBLEM STATEMENT:
You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit.
Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.

Return the minimum number of boats to carry every given person.

Example 1:
Input: people = [1,2], limit = 3
Output: 1
Explanation: 1 boat (1, 2)

Example 2:
Input: people = [3,2,2,1], limit = 3
Output: 3
Explanation: 3 boats (1, 2), (2) and (3)

Example 3:
Input: people = [3,5,3,4], limit = 5
Output: 4
Explanation: 4 boats (3), (3), (4), (5)
 
Constraints:

1 <= people.length <= 5 * 10^4
1 <= people[i] <= limit <= 3 * 10^4

----------------------------------------------------------------------------------------
INTUITION AND APPROACH: (Sorting + Two Pointers)
You have a boat that can fit at most 2 people, up to a certain weight limit. 
Your heaviest passenger steps up to the boat. Who should you try to pair them with?
Logically, you want to maximize efficiency, so you try to squeeze the lightest person in with the heaviest person.
If the heaviest person + the lightest person <= limit, great! They both ride.
If the heaviest person + the lightest person > limit, the heaviest person is simply too heavy to share a boat with anyone. They must ride alone.
To do this efficiently, we must sort the array first!

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N log N) - Dominated entirely by the sorting step. The two-pointer traversal takes O(N).
- Space Complexity: O(1)
========================================================================================
*/

class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        int left = 0;
        int right = people.size() - 1;
        int boats = 0;
        // TC => O(n * logn)
        // SC => O(1)
        while (left <= right) {
            if (people[right] + people[left] <= limit) {
                left++;
                right--;
            } else {
                right--;
                // boats++;
            }
            boats++;
        }
        return boats;
    }
};
