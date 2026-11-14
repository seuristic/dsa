#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int reverseBits(int n) {
    unsigned x = n;

    x = (x >> 16) | (x << 16);
    x = ((x >> 8) & 0x00ff00ff) | ((x & 0x00ff00ff) << 8);
    x = ((x >> 4) & 0x0f0f0f0f) | ((x & 0x0f0f0f0f) << 4);
    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);

    return (int)x;
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
