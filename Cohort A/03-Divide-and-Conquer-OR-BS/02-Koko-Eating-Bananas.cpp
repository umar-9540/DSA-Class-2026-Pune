/*
========================================================================================
Problem Name : Koko Eating Bananas (875)
Problem Link : https://leetcode.com/problems/koko-eating-bananas/
========================================================================================

PROBLEM STATEMENT:
Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4
Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30
Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N * log(Max of Array)) - [Reason: We iterate through N elements in our isPossible function for every log(Max of Array) binary search step.]
- Space Complexity: O(1) - [Reason: No extra space is used, only pointers.]
========================================================================================
*/

class Solution {
public:
    long long calculateHours(vector<int>& piles, int k) {
        long long totalHours = 0;
        for (int p : piles) {
            totalHours += (p + k - 1) / k;
        }
        return totalHours;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int low = 1;
        int high = -1;
        for (int p : piles) {
            high = max(high, p);
        }

        int ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (calculateHours(piles, mid) <= h) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
