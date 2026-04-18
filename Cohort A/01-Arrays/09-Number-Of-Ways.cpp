/*
========================================================================================
Problem Name : Number of Ways (466 C)
Problem Link : https://codeforces.com/problemset/problem/466/C
========================================================================================

PROBLEM STATEMENT:
You've got array a[1], a[2], ..., a[n], consisting of n integers. Count the number of ways to split all the elements of the array into three contiguous parts so that the sum of elements in each part is the same.

More formally, you need to find the number of such pairs of indices i, j (2 ≤ i ≤ j ≤ n - 1), that sum of a (for k = 1 to i - 1) is equal to sum of a (for k = i to j) is equal to sum of a (for k = j + 1 to n)

Input
The first line contains integer n (1 ≤ n ≤ 5·10^5), showing how many numbers are in the array. The second line contains n integers a[1], a[2], ..., a[n] (|a[i]| ≤  10^9) — the elements of array a.

Output
Print a single integer — the number of ways to split the array into three parts with the same sum.

Example 1:
Input
5
1 2 3 0 3
Output
2

Example 2:
Input
4
0 1 -1 0
Output
1

Example 3:
Input
2
4 1
Output
0

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
If I want to break a chocolate bar into 3 pieces that all weigh exactly the same, and the whole bar weighs 10 grams, can I do it? No, 10 isn't divisible by 3! 
So Step 1: If the total sum of the array is not divisible by 3, the answer is instantly 0.

If the total sum is divisible by 3, say Total = S. Then each part MUST sum to S / 3.
To split it into 3 parts, we need to make two cuts.
- The first cut must happen when our running prefix sum hits S / 3.
- The second cut must happen when our running prefix sum hits 2 * (S / 3).

Every time we find a valid second cut (2 * S / 3), it can be paired with every single valid first cut (S / 3) we have seen so far!

APPROACH 1: Brute Force
Concept: Use two nested loops to place the two cuts. Calculate the sum of Part 1, Part 2, and Part 3. If they are all equal, increment the count.
Time Complexity: O(N^2) or O(N^3) without prefix sums.
Space Complexity: O(1).

APPROACH 2: Optimal (Single Pass with Running Counts)
Concept: We iterate through the array, maintaining a currentSum. We keep a running tally of how many times we've seen the target (S/3). Whenever we hit 2 * target, we add that tally to our total ways.
Time Complexity: O(N) — We traverse the array exactly twice (once for total sum, once to count ways).
Space Complexity: O(1) — Only a few integer variables are used.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N) — We traverse the array exactly twice (once for total sum, once to count ways).
- Space Complexity: O(1) — Only a few integer variables are used.
========================================================================================
*/

// APPROACH 2:
#include <iostream>
#include <vector>
using namespace std;

long long countWays(int n, vector<int>& a) {
    long long totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += a[i];
    }
    
    // If the total sum is not divisible by 3, it's impossible.
    if (totalSum % 3 != 0) {
        return 0;
    }
    
    long long target = totalSum / 3;
    long long currentSum = 0;
    long long ways = 0;       // Total valid combinations
    long long countT = 0;     // How many times we've seen the sum 'target'
    
    // We loop up to n-2. Why? 
    // Because the 3rd part must contain AT LEAST one element!
    // The second cut cannot be placed after the very last element.
    for (int i = 0; i < n - 1; i++) {
        currentSum += a[i];
        
        // Check for the SECOND cut first!
        if (currentSum == 2 * target) {
            // We can pair this with any 'target' cut we saw earlier
            ways += countT;
        }
        
        // Then check for the FIRST cut
        if (currentSum == target) {
            countT++;
        }
    }
    
    return ways;
}
