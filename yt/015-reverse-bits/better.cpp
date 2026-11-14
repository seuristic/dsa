#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int reverseBits(int n) {
    unsigned x = n, result = 0;

    for (int i = 0; i < 32; i++) {
      result = (result << 1) | (x & 1);
      x >>= 1;
    }

    return (int)result;
  }
};

void test(int n, int expected) {
  assert(Solution().reverseBits(n) == expected);
}

int main() {
  test(43261596, 964176192);
  test(2147483644, 1073741822);
  test(0, 0);
  test(2, 1073741824);
  test(6, 1610612736);
  test(1431655764, 715827882);
  test(2147483646, 2147483646);
  cout << "All tests passed\n";
}
