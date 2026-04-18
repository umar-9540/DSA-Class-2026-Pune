/*
========================================================================================
Problem Name : Day at the Beach (599 C)
Problem Link : https://codeforces.com/problemset/problem/599/C
========================================================================================

PROBLEM STATEMENT:
One day Squidward, Spongebob and Patrick decided to go to the beach. Unfortunately, the weather was bad, so the friends were unable to ride waves. However, they decided to spent their time building sand castles.

At the end of the day there were n castles built by friends. Castles are numbered from 1 to n, and the height of the i-th castle is equal to hi. When friends were about to leave, Squidward noticed, that castles are not ordered by their height, and this looks ugly. Now friends are going to reorder the castles in a way to obtain that condition hi ≤ hi + 1 holds for all i from 1 to n - 1.

Squidward suggested the following process of sorting castles:

Castles are split into blocks — groups of consecutive castles. Therefore the block from i to j will include castles i, i + 1, ..., j. A block may consist of a single castle.
The partitioning is chosen in such a way that every castle is a part of exactly one block.
Each block is sorted independently from other blocks, that is the sequence hi, hi + 1, ..., hj becomes sorted.
The partitioning should satisfy the condition that after each block is sorted, the sequence hi becomes sorted too. This may always be achieved by saying that the whole sequence is a single block.
Even Patrick understands that increasing the number of blocks in partitioning will ease the sorting process. Now friends ask you to count the maximum possible number of blocks in a partitioning that satisfies all the above requirements.

Input
The first line of the input contains a single integer n (1 ≤ n ≤ 100 000) — the number of castles Spongebob, Patrick and Squidward made from sand during the day.

The next line contains n integers hi (1 ≤ hi ≤ 10^9). The i-th of these integers corresponds to the height of the i-th castle.

Output
Print the maximum possible number of blocks in a valid partitioning.

Example 1:
Input
3
1 2 3
Output
3

Example 2:
Input
4
2 1 3 2
Output
2

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Visualize the array being cut into blocks. If we sort each block individually, the whole array must end up sorted.
"What must be true about the numbers in the left block compared to the numbers in the right block, so that no numbers ever need to cross the boundary during sorting?"
The golden rule: You can draw a valid dividing line between index i and i+1 IF AND ONLY IF the maximum element to the left of the line is <= the minimum element to the right of the line.

APPROACH 1: Brute Force
Concept: Try placing a dividing line at every possible index from 0 to N-2. 
For each line, find the maximum element on the left side and the minimum element on the right side.
If leftMax <= rightMin, we have found a valid block boundary!
- Time Complexity: O(N^2) — For each element, we scan the rest of the array.
- Space Complexity: O(1).

Approach 2: Optimal (Prefix Max and Suffix Min arrays)
Concept: In the brute force approach, we recalculated the right-side minimum every single time.
Instead, we can precompute all the suffix minimums in a single pass from right to left! 
Then, we just do one normal left-to-right pass, keeping track of the running leftMax, and checking our golden rule instantly.
- Time Complexity: O(N) — One pass to build the suffix array, one pass to count blocks.
- Space Complexity: O(N) — To store the rightMin array.

----------------------------------------------------------------------------------------
DRY RUN (With Sample Test Case):
Input: [2, 1, 3, 4, 4]
- rightMin array: [1, 1, 3, 4, 4]
- Step 0 (val 2): leftMax is 2. Is 2 <= 1? No.
- Step 1 (val 1): leftMax is 2. Is 2 <= 3? Yes. Cut!
- Step 2 (val 3): leftMax is 3. Is 3 <= 4? Yes. Cut!
- Step 3 (val 4): leftMax is 4. Is 4 <= 4? Yes. Cut! (This proves <= is correct, not just <)
- Result: 4 blocks [2, 1] [3] [4] [4].

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N) — One pass to build the suffix array, one pass to count blocks.
- Space Complexity: O(N) — To store the rightMin array.
========================================================================================
*/

// -------------------------- APPROACH 1: --------------------------
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxBlocksBrute(int n, vector<int>& h) {
    int blocks = 1; // The whole array is at least 1 block
    
    // Try placing a divider after every index 'i'
    for (int i = 0; i < n - 1; i++) {
        int leftMax = h[0];
        // Find max on the left side (0 to i)
        for (int j = 1; j <= i; j++) {
            leftMax = max(leftMax, h[j]);
        }
        
        int rightMin = h[i + 1];
        // Find min on the right side (i+1 to n-1)
        for (int j = i + 2; j < n; j++) {
            rightMin = min(rightMin, h[j]);
        }
        
        // If the condition holds, we can split here!
        if (leftMax <= rightMin) {
            blocks++;
        }
    }
    return blocks;
}

// -------------------------- APPROACH 2: --------------------------
#include <vector>
#include <algorithm>
using namespace std;

int maxBlocksOptimal(int n, vector<int>& h) {
    if (n == 0) return 0;
    
    // Step 1: Precompute the minimums from right to left
    vector<int> rightMin(n);
    rightMin[n - 1] = h[n - 1]; 
    for (int i = n - 2; i >= 0; i--) {
        rightMin[i] = min(rightMin[i + 1], h[i]);
    }
    
    int blocks = 1; 
    int leftMax = h[0];
    
    // Step 2: Iterate and find valid cuts
    for (int i = 0; i < n - 1; i++) {
        leftMax = max(leftMax, h[i]);
        
        // The Golden Rule Check
        if (leftMax <= rightMin[i + 1]) {
            blocks++;
        }
    }
    
    return blocks;
}
