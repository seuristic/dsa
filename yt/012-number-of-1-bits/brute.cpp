#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int hammingWeight(int n) {
    int count = 0;

    while (n > 0) {
      count += n & 1;
      n >>= 1;
    }

    return count;
  }
};

void test(int n, int expected) {
  assert(Solution().hammingWeight(n) == expected);
}

int main() {
  test(11, 3);
  test(128, 1);
  test(2147483645, 30);
  test(1, 1);
  test(2, 1);
  test(7, 3);
  test(1073741824, 1);
  test(1431655765, 16);
  test(2147483647, 31);
  cout << "All tests passed\n";
}
