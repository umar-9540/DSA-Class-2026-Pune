/*
========================================================================================
Problem Name : Zigzag Conversion (6)
Problem Link : https://leetcode.com/problems/zigzag-conversion/description/
========================================================================================

PROBLEM STATEMENT:
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this: (you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:
string convert(string s, int numRows);

Example 1:

Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"
 

Constraints:

1 <= s.length <= 1000
s consists of English letters (lower-case and upper-case), ',' and '.'.
1 <= numRows <= 1000

----------------------------------------------------------------------------------------
INTUITION AND APPROACH:
Try to visualize how you would actually write this out on paper.
If you are writing this row by row, what are you actually doing? You are writing a letter on Row 0, then Row 1, then Row 2... until you hit the bottom.
Then you bounce back up: Row 1, Row 0. You are just a bouncing ball!"

We just need a simple list of strings—one string representing each row. We just drop each character into the correct row's string as we "bounce" up and down.

APPROACH 1: The Intuitive Simulation 
Concept: We create an array of strings, vector<string> rows, where rows[i] will hold all the characters that belong to the i-th row.
We read the input string one character at a time. We keep track of our currentRow and a boolean variable called goingDown.
If we are at the top row (currentRow == 0), we must go down.If we are at the bottom row (currentRow == numRows - 1), we must go up.
Once we place all characters in their respective rows, we just glue the strings together!

Time Complexity: O(N) where N is the length of the string. We look at each character exactly once and append it to a string.
Space Complexity: O(N) to store the characters in the rows array.

APPROACH 2: The Math/Index Jump Method
Concept: Instead of simulating the bouncing, we can use math to jump straight to the exact indices of the original string that belong in Row 0, then Row 1, etc.
Take a look at the cycle of the bouncing ball. A full cycle goes from the top, to the bottom, and back up to the row just below the top.
The length of this cycle is exactly cycleLen = 2 * numRows - 2.
For example, if numRows = 4, the cycle length is (2 * 4) - 2 = 6. Characters in Row 0 appear at indices: 0, 6, 12, 18
Characters in the bottom Row appear at indices: 3, 9, 15, 21
Characters in the inner rows have two characters per cycle!

Time Complexity: O(N). We still visit each character exactly once, just in a different order.
Space Complexity: O(1) auxiliary space (since we build the output string directly and don't use intermediate arrays).

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N). We still visit each character exactly once, just in a different order.
- Space Complexity: O(1) auxiliary space (since we build the output string directly and don't use intermediate arrays).
========================================================================================
*/

// APPROACH 1:
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string convertSimulation(string s, int numRows) {
    // EDGE CASE: If there is only 1 row, it's just the original string.
    // If numRows >= s.length(), it just goes straight down, no zigzag needed.
    if (numRows == 1 || numRows >= s.length()) {
        return s;
    }

    // Create an array of strings to represent each row
    vector<string> rows(min(numRows, int(s.length())));
    
    int currentRow = 0;
    bool goingDown = false; // Will flip to true on the very first step

    // Drop each character into the correct row
    for (char c : s) {
        rows[currentRow] += c;
        
        // If we hit the top or bottom, bounce! (Change direction)
        if (currentRow == 0 || currentRow == numRows - 1) {
            goingDown = !goingDown;
        }
        
        // Move up or down based on our current direction
        currentRow += goingDown ? 1 : -1;
    }

    // Glue all the rows together
    string result = "";
    for (string row : rows) {
        result += row;
    }
    
    return result;
}

// APPROACH 2:
#include <iostream>
#include <string>
using namespace std;

string convertMath(string s, int numRows) {
    if (numRows == 1 || numRows >= s.length()) {
        return s;
    }

    string result = "";
    int n = s.length();
    int cycleLen = 2 * numRows - 2;

    // Iterate through each row we want to build
    for (int i = 0; i < numRows; i++) {
        // Jump through the string in cycles
        for (int j = 0; j + i < n; j += cycleLen) {
            // 1. Add the main character for this cycle
            result += s[j + i];
            
            // 2. If we are NOT on the first row or the last row, 
            // there is a second character hiding in the upward diagonal of the zigzag!
            if (i != 0 && i != numRows - 1 && j + cycleLen - i < n) {
                result += s[j + cycleLen - i];
            }
        }
    }
    return result;
}
