/*
========================================================================================
Problem Name : Longest Substring Without Repeating Characters (3)
Problem Link : https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
========================================================================================

PROBLEM STATEMENT:
Given a string s, find the length of the longest substring without duplicate characters.

Example 1:
Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3. Note that "bca" and "cab" are also correct answers.

Example 2:
Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.

Example 3:
Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.

Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 10^4
s consists of English letters, digits, symbols and spaces.

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Imagine reading the string left to right. We keep adding letters to our "window" as long as they are unique.
What happens when we hit a duplicate? Say our window is [a, b, c] and the next letter is a.
If we start completely over from the 'b', we are doing redundant work! The only reason our window became invalid is because of the old 'a'.
So Don't destroy the window; just shrink it from the left! We remove letters from the left side until the duplicate 'a' falls out of the window.
Then, we resume growing the window to the right.

APPROACH 1: Brute Force
Concept: Check every possible substring. For each substring, use a Hash Set to see if it contains duplicates.
Time Complexity: O(N^3) to check all substrings from scratch.
Space Complexity: O(min(N, M)), where M is the character set size (e.g., 256 for ASCII).

APPROACH 2: Intuitive Sliding Window (Using a Set)
Concept: We use a left pointer and a right pointer. The right pointer pulls new characters into the window.
If the character is already in our Set, the left pointer kicks characters out until the window is valid again.
Time Complexity: O(N). Each character is visited at most twice (once by right, once by left).
Space Complexity: O(min(N, M)) for the Hash Set.

APPROACH 3: Optimal Sliding Window (The "Pro" Jump Method)
Concept: The while loop in the Set approach is a bit slow. If our window is [a, b, c, d, e] and we encounter another e, the left pointer walks step-by-step: removing a, then b, then c...
Instead of a Set, let's use an array or HashMap to store the exact index where we last saw each character. If we see a duplicate, we instantly "teleport" the left pointer to last_seen_index + 1!
Time Complexity: O(N). Strictly one pass.
Space Complexity: O(1) auxiliary space if we use a fixed array of size 256 for ASCII characters.

The lastSeen[currentChar] >= left condition: 
"Why do we check if the index is >= left?" 
Answer: Because our lastSeen array remembers the history of the entire string. We might have seen an 'a' at index 0, but if our left pointer is currently at index 5, that old 'a' is completely irrelevant. 
It's outside our current window! We only jump if the duplicate is actively bothering our current window.

ASCII Array vs Map: 
Why vector<int> lastSeen(256, -1) is used instead of a standard unordered_map. An array index lookup is significantly faster than computing a hash function, making this the most highly optimized solution possible in C++.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N). Strictly one pass.
- Space Complexity: O(1) auxiliary space if we use a fixed array of size 256 for ASCII characters.
========================================================================================
*/

// APPROACH 2:
#include <string>
#include <unordered_set>
#include <algorithm>
using namespace std;

int lengthOfLongestSubstringSet(string s) {
    unordered_set<char> window;
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < s.length(); right++) {
        // If the character is already in the window, shrink from the left
        while (window.find(s[right]) != window.end()) {
            window.erase(s[left]);
            left++;
        }
        
        // Now it's safe to add the new character
        window.insert(s[right]);
        
        // Update our max length
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}

// APPROACH 3:
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int lengthOfLongestSubstringOptimal(string s) {
    // Array to store the last seen index of each ASCII character
    // Initialize all to -1 (meaning "not seen yet")
    vector<int> lastSeen(256, -1); 
    
    int left = 0;
    int maxLength = 0;
    
    for (int right = 0; right < s.length(); right++) {
        char currentChar = s[right];
        
        // If we have seen this character BEFORE, and its last position is 
        // INSIDE our current window, we must jump the left pointer!
        if (lastSeen[currentChar] >= left) {
            left = lastSeen[currentChar] + 1;
        }
        
        // Update the character's last seen index to the current position
        lastSeen[currentChar] = right;
        
        // Calculate the current window size and update max
        maxLength = max(maxLength, right - left + 1);
    }
    
    return maxLength;
}
