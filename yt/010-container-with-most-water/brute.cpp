#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxArea(vector<int>& height) {
    int n = height.size();
    int best = 0;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int area = min(height[i], height[j]) * (j - i);
        best = max(best, area);
      }
    }

    return best;
  }
};

void test(vector<int> height, int expected) {
  assert(Solution().maxArea(height) == expected);
}

int main() {
  test({1, 8, 6, 2, 5, 4, 8, 3, 7}, 49);
  test({1, 1}, 1);
  test({0, 0}, 0);
  test({0, 5}, 0);
  test({4, 3, 2, 1, 4}, 16);
  test({1, 2, 1}, 2);
  test({2, 3, 4, 5, 18, 17, 6}, 17);
  test({10000, 1, 10000}, 20000);
  cout << "All tests passed\n";
}
