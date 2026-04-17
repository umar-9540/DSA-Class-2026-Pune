/*
========================================================================================
Problem Name : Palindromic Substrings (647)
Problem Link : https://leetcode.com/problems/palindromic-substrings/description/
========================================================================================

PROBLEM STATEMENT:
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.

Example 1:
Input: s = "abc"
Output: 3
Explanation: Three palindromic strings: "a", "b", "c".

Example 2:
Input: s = "aaa"
Output: 6
Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".
 

Constraints:

1 <= s.length <= 1000
s consists of lowercase English letters.

----------------------------------------------------------------------------------------
INTUITION:
How do you normally check if a word like 'racecar' is a palindrome?
Read it from the outside in (left and right pointers moving towards the middle). That works great for ONE string.
But if we need to find ALL palindromes hidden inside a massive string, checking from the outside-in means we have to find every possible substring first. That is incredibly slow.
Reverse the thinking. Instead of looking outside-in, what if we stand in the middle of a letter and look inside-out?
If we pick a center character and expand outward, as long as the left and right characters match, the palindrome grows!
The Only Trap: Centers aren't just single letters. "aba" has a center at 'b' (a single letter). "abba" has a center between the two 'b's.
So, for a string of length N, we must check N single-letter centers and N-1 double-letter centers.

APPROACH 1: Brute Force
Concept: Generate every possible substring using two nested loops. Then, use a third loop to check if that substring is a palindrome.
Time Complexity: O(N^3) => O(N^2) to generate substrings, and O(N) to check each one. This is way too slow.
Space Complexity: O(1).

APPROACH 2: Optimal (Expand Around Center)
Concept: We iterate through every index in the string. For each index, we run our expansion logic twice: once treating the index as a single-character center, and once treating it as the left half of a two-character center.
Time Complexity: O(N^2) => We check 2*N - 1 centers. For each center, expanding takes at most O(N) steps.
Space Complexity: O(1). No extra data structures are used.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N^2) => We check 2*N - 1 centers. For each center, expanding takes at most O(N) steps.
- Space Complexity: O(1). No extra data structures are used.
========================================================================================
*/

// APPROACH 1:
#include <string>
using namespace std;

bool isPalindrome(string& s, int left, int right) {
    while (left < right) {
        if (s[left] != s[right]) return false;
        left++;
        right--;
    }
    return true;
}

int countSubstringsBrute(string s) {
    int count = 0;
    int n = s.length();
    
    // Generate all substrings s[i...j]
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPalindrome(s, i, j)) {
                count++;
            }
        }
    }
    return count;
}

// APPROACH 2:
#include <string>
using namespace std;

// Helper function that expands outwards and returns the count of palindromes found
int expandAroundCenter(string& s, int left, int right) {
    int count = 0;
    // Keep expanding as long as we are in bounds and the characters match
    while (left >= 0 && right < s.length() && s[left] == s[right]) {
        count++;    // Found a valid palindrome!
        left--;     // Expand left
        right++;    // Expand right
    }
    return count;
}

int countSubstringsOptimal(string s) {
    int totalPalindromes = 0;
    
    for (int i = 0; i < s.length(); i++) {
        // 1. Odd length palindromes (single character center)
        totalPalindromes += expandAroundCenter(s, i, i);
        
        // 2. Even length palindromes (center is between i and i+1)
        totalPalindromes += expandAroundCenter(s, i, i + 1);
    }
    
    return totalPalindromes;
}
