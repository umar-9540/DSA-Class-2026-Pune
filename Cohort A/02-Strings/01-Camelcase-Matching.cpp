/*
========================================================================================
Problem Name : Camelcase Matching (1023)
Problem Link : https://leetcode.com/problems/camelcase-matching/description/
========================================================================================

PROBLEM STATEMENT:
Given an array of strings queries and a string pattern, return a boolean array answer where answer[i] is true if queries[i] matches pattern, and false otherwise.

A query word queries[i] matches pattern if you can insert lowercase English letters into the pattern so that it equals the query.
You may insert a character at any position in pattern or you may choose not to insert any characters at all.
 

Example 1:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FB"
Output: [true,false,true,true,false]
Explanation: "FooBar" can be generated like this "F" + "oo" + "B" + "ar".
"FootBall" can be generated like this "F" + "oot" + "B" + "all".
"FrameBuffer" can be generated like this "F" + "rame" + "B" + "uffer".

Example 2:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBa"
Output: [true,false,true,false,false]
Explanation: "FooBar" can be generated like this "Fo" + "o" + "Ba" + "r".
"FootBall" can be generated like this "Fo" + "ot" + "Ba" + "ll".

Example 3:
Input: queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"], pattern = "FoBaT"
Output: [false,true,false,false,false]
Explanation: "FooBarTest" can be generated like this "Fo" + "o" + "Ba" + "r" + "T" + "est".
 

Constraints:

1 <= pattern.length, queries.length <= 100
1 <= queries[i].length <= 100
queries[i] and pattern consist of English letters.

----------------------------------------------------------------------------------------
INTUITION:
Can we insert uppercase letters? No, only lowercase.
This means the uppercase letters act like a strict skeleton.
The rule is simple: The pattern must be a subsequence of the query. AND, any extra character in the query that is NOT part of the pattern MUST be lowercase.
If we find an extra uppercase letter in the query, it's an immediate false.

APPROACH: Optimal (Two Pointers)
Concept: We iterate through each query. We use one pointer to walk through the query string, and another pointer to walk through the pattern string.

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(Q × L), where Q is the number of queries and L is the max length of a query string. We check each character exactly once.
- Space Complexity: O(1) auxiliary space (excluding the output boolean array).
========================================================================================
*/

#include <vector>
#include <string>
#include <cctype>
using namespace std;

class Solution {
    bool isMatch(const string& query, const string& pattern) {
        int pIndex = 0; // Pointer for the pattern
        
        for (int i = 0; i < query.length(); i++) {
            // If characters match, advance the pattern pointer
            if (pIndex < pattern.length() && query[i] == pattern[pIndex]) {
                pIndex++;
            } 
            // If they don't match, the extra character in query MUST be lowercase
            else if (isupper(query[i])) {
                return false; // Found an unexpected uppercase letter!
            }
            // If it's a lowercase letter and doesn't match, we just ignore it.
        }
        
        // After reading the whole query, did we find the complete pattern?
        return pIndex == pattern.length();
    }

public:
    vector<bool> camelMatch(vector<string>& queries, string pattern) {
        vector<bool> result;
        for (const string& query : queries) {
            result.push_back(isMatch(query, pattern));
        }
        return result;
    }
};
