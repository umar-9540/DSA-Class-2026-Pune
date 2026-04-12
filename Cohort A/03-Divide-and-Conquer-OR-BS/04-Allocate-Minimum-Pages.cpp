/*
========================================================================================
Problem Name : Allocate Minimum Pages
Problem Link : https://www.geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1
========================================================================================

PROBLEM STATEMENT:
Given an array arr[] of integers, where each element arr[i] represents the number of pages in the i-th book.
You also have an integer k representing the number of students. The task is to allocate books to each student such that:

Each student receives atleast one book.
Each student is assigned a contiguous sequence of books.
No book is assigned to more than one student.
All books must be allocated.

The objective is to minimize the maximum number of pages assigned to any student.
In other words, out of all possible allocations, find the arrangement where the student who receives the most pages still has the smallest possible maximum.

Note: If it is not possible to allocate books to all students, return -1.

Example 1:
Input: arr[] = [12, 34, 67, 90], k = 2
Output: 113
Explanation: Allocation can be done in following ways:
=> [12] and [34, 67, 90] Maximum Pages = 191
=> [12, 34] and [67, 90] Maximum Pages = 157
=> [12, 34, 67] and [90] Maximum Pages = 113.
The third combination has the minimum pages assigned to a student which is 113.

Example 2:
Input: arr[] = [15, 17, 20], k = 5
Output: -1
Explanation: Since there are more students than total books, it's impossible to allocate a book to each student.

Constraints:
1 ≤ arr.size() ≤ 10^6
1 ≤ arr[i], k ≤ 10^3

----------------------------------------------------------------------------------------
INTUITION:
We are asked to "minimize the maximum."

What is the absolute minimum possible answer? The book with the maximum pages (since we can't split a book).

What is the absolute maximum possible answer? The sum of all pages (if one poor student gets all the books).
This creates our search space!

----------------------------------------------------------------------------------------
COMPLEXITY:
- Time Complexity: O(N * log(sum - max)) - [Reason: We iterate through N elements in our isPossible function for every log(sum - max) binary search step.]
- Space Complexity: O(1) - [Reason: No extra space is used, only pointers.]
========================================================================================
*/

class Solution {
  public:
  int calcStudents (vector<int> &arr, int pages) {
      int pagesCount = 0;
      int students = 1;
      
      for (int i = 0; i < arr.size(); i++) {
          if (pagesCount + arr[i] <= pages) {
              pagesCount += arr[i];
          } else {
              students++;
              pagesCount = arr[i];
          }
      }
      return students;
  }
  
    int findPages(vector<int> &arr, int k) {
        // code here
        if (k > arr.size()) return -1;
        
        int low = *max_element(arr.begin(), arr.end());
        int high = 0;
        for (int num : arr) {
            high += num;
        }
        
        // TC => O(n * log(sum - max))
        // SC => O(1)
        int ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            
            if (calcStudents(arr, mid) <= k) {
                ans = mid;
                high = mid - 1;
            } else {
                low = mid + 1;
            }
        }
        return ans;
    }
};
