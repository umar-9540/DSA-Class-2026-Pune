/*
========================================================================================
Problem Name : Minimum Window Substring (76)
Problem Link : https://leetcode.com/problems/minimum-window-substring/description/
========================================================================================

PROBLEM STATEMENT:
Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window.
If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
 

Constraints:

m == s.length
n == t.length
1 <= m, n <= 10^5
s and t consist of uppercase and lowercase English letters.
 
Follow up: Could you find an algorithm that runs in O(m + n) time?

----------------------------------------------------------------------------------------
INTUITION:
"Imagine eating a giant sandwich to find a hidden coin. You take huge bites (expanding the right pointer) until you finally get the coin in your mouth.
But wait, you want the SMALLEST piece of bread that contains the coin! So, you start spitting out the edges of the bread (shrinking the left pointer) until right before the coin falls out."

Expand right until the window contains all characters of string t (Valid Window).
Shrink left to minimize the window size, while updating our "best minimum" answer.
Stop shrinking as soon as a required character is lost (Invalid Window).
Repeat until the end of the string.

APPROACH 1: Brute Force
Generate every possible substring of s. For each one, count its characters and compare them against the character counts of t.
Time Complexity: O(N^3)

Approach 2: Optimal (Sliding Window with a 'Required' Counter)
Concept: Instead of comparing two HashMaps every single time we move a pointer (which takes $O(256)$ time per step), we use a single integer required.
If t is "ABC", required = 3. When our window consumes a needed 'A', required drops to 2. When required == 0, we know our window is valid without doing any heavy map comparisons!
Time Complexity: O(M + N) where M is length of s and N is length of t.
Space Complexity: O(1) - An array of size 128 for ASCII characters.

Why map[rightChar]-- goes into the negatives: 
If t only needs one 'A', but our window has swallowed three 'A's, the map value for 'A' will be -2. This is actually a good thing!
It acts as a buffer. When we shrink from the left and throw away an 'A', the map value goes from -2 to -1.
Because it's still <= 0, the algorithm knows we haven't damaged the required string yet.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(M + N) where M is length of s and N is length of t.
- Space Complexity: O(1) - An array of size 128 for ASCII characters.
========================================================================================
*/

// APPROACH 2:
#include <iostream>
#include <string>
#include <vector>
using namespace std;

string minWindow(string s, string t) {
    // Edge case
    if (s.length() == 0 || t.length() == 0 || s.length() < t.length()) {
        return "";
    }
    
    // Array to keep track of the characters we need
    // Size 128 handles all standard ASCII characters (upper and lowercase)
    vector<int> map(128, 0);
    
    // Populate the map with characters from 't'
    for (char c : t) {
        map[c]++;
    }
    
    int left = 0, right = 0;
    int required = t.length(); // Total number of useful characters we need to find
    
    // Variables to store the final answer
    int minLen = 1e9; // Infinity
    int startIndex = 0;
    
    while (right < s.length()) {
        char rightChar = s[right];
        
        // If this character is useful (we need it), decrement 'required'
        if (map[rightChar] > 0) {
            required--;
        }
        
        // Regardless of whether we needed it, decrement its count in the map.
        // (Negative numbers mean we have MORE of this character than we need)
        map[rightChar]--;
        
        // When required == 0, our window contains all characters from 't'
        while (required == 0) {
            
            // 1. Record the current window if it's the smallest we've seen
            int currentWindowSize = right - left + 1;
            if (currentWindowSize < minLen) {
                minLen = currentWindowSize;
                startIndex = left;
            }
            
            // 2. Try to shrink the window from the left
            char leftChar = s[left];
            
            // Remove the left character from our window by incrementing its map count
            map[leftChar]++;
            
            // If the count becomes > 0, it means we just threw away a character we NEEDED
            if (map[leftChar] > 0) {
                required++; // The window is now invalid, so we break out of the inner loop
            }
            
            left++; // Actually move the left pointer
        }
        
        right++; // Expand the right pointer to find the next valid window
    }
    
    // If minLen was never updated, no valid window was found
    return minLen == 1e9 ? "" : s.substr(startIndex, minLen);
}
