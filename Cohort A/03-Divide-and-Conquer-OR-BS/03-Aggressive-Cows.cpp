/*
========================================================================================
Problem Name : Aggressive Cows
Problem Link : https://www.geeksforgeeks.org/problems/aggressive-cows/1
========================================================================================

PROBLEM STATEMENT:
You are given an array with unique elements of stalls[], which denote the positions of stalls.
You are also given an integer k which denotes the number of aggressive cows.
The task is to assign stalls to k cows such that the minimum distance between any two of them is the maximum possible.

Example 1:
Input: stalls[] = [1, 2, 4, 8, 9], k = 3
Output: 3
Explanation: The first cow can be placed at stalls[0], 
the second cow can be placed at stalls[2] and 
the third cow can be placed at stalls[3]. 
The minimum distance between cows in this case is 3, which is the largest among all possible ways.

Example 2:
Input: stalls[] = [10, 1, 2, 7, 5], k = 3
Output: 4
Explanation: The first cow can be placed at stalls[0],
the second cow can be placed at stalls[1] and
the third cow can be placed at stalls[4].
The minimum distance between cows in this case is 4, which is the largest among all possible ways.

Example 3:
Input: stalls[] = [2, 12, 11, 3, 26, 7], k = 5
Output: 1
Explanation: There are 6 stalls and only 5 cows, we try to place the cows such that the minimum distance between any two cows is as large as possible.
The minimum distance between cows in this case is 1, which is the largest among all possible ways.

Constraints:
2 ≤ stalls.size() ≤ 10^6
0 ≤ stalls[i] ≤ 10^8
2 ≤ k ≤ stalls.size()

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N * log N) + O(N * log(max_stall - min_stall))
- Space Complexity: O(1) - [Reason: No extra space is used, only pointers.]
========================================================================================
*/

class Solution {
  public:
  
  bool canPlaceCows(vector<int> &stalls, int dist, int k) {
      int cowsPlaced = 1;
      int lastPos = stalls[0];
      
      for (int i = 1; i < stalls.size(); i++) {
          if (stalls[i] - lastPos >= dist) {
              cowsPlaced++;
              lastPos = stalls[i];
          }
          
          if (cowsPlaced >= k) return true;
      }
      return false;
  }
  
    int aggressiveCows(vector<int> &stalls, int k) {
      
        sort(stalls.begin(), stalls.end());
        int n = stalls.size();
        int low = 1;
        int high = stalls[n - 1] - stalls[0];
        int ans = 0;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (canPlaceCows(stalls, mid, k)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};
