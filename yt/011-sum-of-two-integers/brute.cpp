#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int getSum(int a, int b) {
    unsigned result = 0, carry = 0;

    for (int i = 0; i < 32; i++) {
      unsigned bitA = ((unsigned)a >> i) & 1;
      unsigned bitB = ((unsigned)b >> i) & 1;

      result |= (bitA ^ bitB ^ carry) << i;
      carry = (bitA & bitB) | (bitA & carry) | (bitB & carry);
    }

    return (int)result;
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
