#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> countBits(int n) {
    vector<int> ans(n + 1, 0);

    for (int i = 0; i <= n; i++) {
      int x = i;

      while (x > 0) {
        ans[i] += x & 1;
        x >>= 1;
      }
    }

    return ans;
  }
};

void test(int n, vector<int> expected) {
  assert(Solution().countBits(n) == expected);
}

int main() {
  test(2, {0, 1, 1});
  test(5, {0, 1, 1, 2, 1, 2});
  test(0, {0});
  test(1, {0, 1});
  test(8, {0, 1, 1, 2, 1, 2, 2, 3, 1});
  test(16, {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1});

  vector<int> big = Solution().countBits(100000);
  assert(big.size() == 100001);
  assert(big[65535] == 16);
  assert(big[65536] == 1);
  assert(big[99999] == 10);
  assert(big[100000] == 6);
  cout << "All tests passed\n";
}
