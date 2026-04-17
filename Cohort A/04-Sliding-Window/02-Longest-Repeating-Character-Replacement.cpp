/*
========================================================================================
Problem Name : Longest Repeating Character Replacement (424)
Problem Link : https://leetcode.com/problems/longest-repeating-character-replacement/description/
========================================================================================

PROBLEM STATEMENT:
You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character.
You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.
 

Constraints:

1 <= s.length <= 10^5
s consists of only uppercase English letters.
0 <= k <= s.length

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Imagine a window of characters, like [A, B, A, B, B]. If we want to make this entire window the same letter, which letter should we pick to minimize our work?
Answer: The letter that already appears the most! (In this case, B, which appears 3 times).
If the length of our window is 5, and the most frequent character B appears 3 times, how many characters do we have to replace?
Formula: Total Length - Most Frequent Character Count = Replacements Needed (5 - 3 = 2).
If this number is <= k, the window is valid! If it is > k, the window is invalid, and we must shrink it from the left.

APPROACH 1: Brute Force
Concept: We generate every single possible substring. For each substring, we count the frequencies of all characters, find the maximum frequency, and check our formula: Length - MaxFreq <= k.
Time Complexity: O(N^2) to check all substrings, plus O(26) to find the max frequency each time. This will cause a Time Limit Exceeded (TLE) error.
Space Complexity: O(1) (an array of 26 characters).

Approach 2: Optimal (Sliding Window)
Concept: We use a left and right pointer to create a window. As right expands, we update our frequency map and keep track of the maxFreq we've seen.
If the window becomes invalid (Length - maxFreq > k), we move the left pointer inward to shrink it.
Time Complexity: O(N) - Both pointers only move forward.
Space Complexity: O(1) - An array of size 26 is considered constant space.

"Wait! When we shrink the window from the left, we decrement the count of the character leaving the window. But we NEVER recalculate maxFreq to see if it went down! Is that a bug?"
This is the most brilliant part of this algorithm. We are looking for the MAXIMUM length. Once we find a valid window of size 4, we don't care about valid windows of size 3.
For the window to ever grow to size 5, we NEED a maxFreq that is larger than our historical best.
Therefore, an outdated, artificially high maxFreq doesn't hurt us—it just prevents the window from expanding until a genuinely better maxFreq comes along to overwrite it!

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N) - Both pointers only move forward.
- Space Complexity: O(1) - An array of size 26 is considered constant space.
========================================================================================
*/

// APPROACH 2:
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int characterReplacement(string s, int k) {
    vector<int> count(26, 0); // Frequency map for uppercase English letters
    int left = 0;
    int maxFreq = 0;
    int maxLength = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // 1. Add the new character to our window
        count[s[right] - 'A']++;
        
        // 2. Update the highest frequency of a single character seen in this window
        maxFreq = max(maxFreq, count[s[right] - 'A']);
        
        // 3. Check if the window is INVALID:
        // Window Length - maxFreq > k
        int windowLength = right - left + 1;
        if (windowLength - maxFreq > k) {
            // The window is invalid, we must shrink it from the left
            count[s[left] - 'A']--;
            left++; 
        }
        
        // 4. Update the maximum length found so far
        // Note: We only calculate this after ensuring the window is valid
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}
