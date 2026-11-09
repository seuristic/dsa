#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int getSum(int a, int b) {
    while (b != 0) {
      unsigned carry = (unsigned)(a & b) << 1;
      a = a ^ b;
      b = (int)carry;
    }

    return a;
  }
};

void test(int a, int b, int expected) {
  assert(Solution().getSum(a, b) == expected);
}

int main() {
  test(1, 2, 3);
  test(2, 3, 5);
  test(0, 0, 0);
  test(5, 3, 8);
  test(-1, 1, 0);
  test(-2, -3, -5);
  test(5, -3, 2);
  test(-5, 3, -2);
  test(0, -7, -7);
  test(1000, 1000, 2000);
  test(-1000, -1000, -2000);
  test(1000, -1000, 0);
  cout << "All tests passed\n";
}
