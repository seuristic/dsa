#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxSubArray(vector<int>& nums) {
    int current = 0, best = INT_MIN;
    for (int x : nums) {
      current = max(x, current + x);
      best = max(best, current);
    }
    return best;
  }
};

void test(vector<int> nums, int expected) {
  assert(Solution().maxSubArray(nums) == expected);
}

int main() {
  test({-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);
  test({1}, 1);
  test({5, 4, -1, 7, 8}, 23);
  test({-3, -1, -2}, -1);
  test({-5}, -5);
  test({0, 0, 0}, 0);
  test({2, -1, 2}, 3);
  test({1, -10, 5}, 5);
  test({-10000, 10000, 10000}, 20000);
  cout << "All tests passed\n";
}
