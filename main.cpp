/**
SUBMITTED BY: Aakash Kumar

PROBLEM STATEMENT:

A top secret message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
You are an FBI agent. You have to determine the total number of ways that message can be decoded.
Note: An empty digit sequence is considered to have one decoding. It may be assumed that the input contains valid digits from 0 to 9 and If there are leading 0’s, extra trailing 0’s and two or more consecutive 0’s then it is an invalid string.

Example :
Given encoded message "123",  it could be decoded as "ABC" (1 2 3) or "LC" (12 3) or "AW"(1 23).
So total ways are 3.

Input:
First line contains the test cases T.  1<=T<=1000
Each test case have two lines
First is length of string N.  1<=N<=40
Second line is string S of digits from '0' to '9' of N length.
*/

#include <bits/stdc++.h>

using namespace std;

/**
  * Function computes total number of ways that message can be decoded.
  * Time Complexity: O(n), Space Complexity: O(n)
  * Returns:
    1. -1, if decoded string is invalid.
    2. or, total number of ways that message can be decoded

  * Solution Approach:
    We can break problem into subproblems. Suppose we know number of ways to decode message of length i.
    Then we can compute number of ways to decode message of length i+1 as:
    1. If last digit is non-zero
      i. We can decode the (i+1)th digit directly, i.e ways[i+1] += ways[i]. (ways[i+1] is initially 0)
      ii. We can group the (i+1)th digit with ith digit to decode (only if decoded number if in range [10, 26]), i.e
          ways[i+1] += ways[i-2];

    2. If digit is zero, we can only decode combining with ith digit.
      i. If comibination is not in range [10, 26] then provided string is invalid  .
      ii. If combination is valid, then ways[i+1] = ways[i].
*/
int compute_ways(string S, int N) {

  vector <int> ways(N, 0);

  // leading zeros are not allowed
  if (S[0] == '0') return -1;

  // Initializing one digit sequence value
  ways[0] = 1;

  for (int i = 1; i < N ; i++) {

    // Computing number by combining ith and (i+1)th digit.
    int num = ((S[i-1] - '0') * 10) + (S[i] - '0');

    if (S[i] == '0') {

      if (num <= 26 && num >= 10) {
        // Condition 2(ii)
        ways[i] = i > 1 ? ways[i-1] : 1;

      } else {
        // Condition 2(i)
        // breaking loop, setting final value to -1
        ways[N-1] = -1;

        break;
      }

    } else {
      // condition 1(i)
      ways[i] = ways[i-1];

      if (num >= 10 && num <= 26) {
        // condition 1(ii), handling base case when i == 1
        ways[i] += (i == 1 ? 1 : ways[i-2]);
      }

    }
  }

  return ways[N-1];
}

/**
  * Improved version of above function
  * Time Complexity: O(n), Space Complexity: O(1)

  * Solution Approach: Same as mentioned above
    We can see on above method that only ways[i-1] and way[i-2] are required to compute ways[i]. Using 2 variables to store them.
*/
int improved_compute_ways(string S, int N) {

  int cur, last, second_last;

  // leading zeros are not allowed
  if (S[0] == '0') return -1;

  // Initializing one digit sequence value
  last = 1;

  for (int i = 1; i < N ; i++) {

    // Computing number by combining ith and (i+1)th digit.
    int num = ((S[i-1] - '0') * 10) + (S[i] - '0');

    if (S[i] == '0') {

      if (num >= 10 && num <= 26) {
        // Condition 2(ii)
        cur = i > 1 ? last : 1;

      } else {
        // Condition 2(i)
        // breaking loop, setting final value to -1
        cur = -1;

        break;
      }

    } else {
      // condition 1(i)
      cur = last;

      if (num >= 10 && num <= 26) {
        // condition 1(ii), handling base case when i == 1
        cur += (i == 1 ? 1 : second_last);
      }

    }

    second_last = last;
    last = cur;
  }

  return cur;
}

int main()
{
    int t, N;
    string S;

    cin >> t;

    while (t--) {
      cin >> N;
      cin >> S;

      cout << "compute_ways returns: " << compute_ways(S, N) << endl;
      cout << "improved_compute_ways returns" <<improved_compute_ways(S, N) << endl;
    }

    return 0;
}
