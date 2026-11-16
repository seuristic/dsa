#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int climbStairs(int n) {
    vector<int> memo(n + 1, 0);
    return ways(n, memo);
  }

private:
  int ways(int n, vector<int>& memo) {
    if (n <= 2) {
      return n;
    }

    if (memo[n] != 0) {
      return memo[n];
    }

    memo[n] = ways(n - 1, memo) + ways(n - 2, memo);
    return memo[n];
  }
};

void test(int n, int expected) {
  assert(Solution().climbStairs(n) == expected);
}

int main() {
  test(2, 2);
  test(3, 3);
  test(1, 1);
  test(4, 5);
  test(5, 8);
  test(10, 89);
  test(20, 10946);
  test(30, 1346269);
  cout << "All tests passed\n";
}
