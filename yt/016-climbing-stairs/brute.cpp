#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int climbStairs(int n) {
    if (n <= 2) {
      return n;
    }

    return climbStairs(n - 1) + climbStairs(n - 2);
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
