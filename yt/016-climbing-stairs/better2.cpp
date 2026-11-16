#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int climbStairs(int n) {
    if (n <= 2) {
      return n;
    }

    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
      dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
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
