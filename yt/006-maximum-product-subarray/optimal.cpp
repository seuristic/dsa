#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxProduct(vector<int>& nums) {
    long long maxEnd = nums[0], minEnd = nums[0], best = nums[0];
    for (int i = 1; i < (int)nums.size(); i++) {
      long long x = nums[i];
      long long a = maxEnd * x, b = minEnd * x;
      maxEnd = max({x, a, b});
      minEnd = min({x, a, b});
      best = max(best, maxEnd);
    }
    return best;
  }
};

void test(vector<int> nums, int expected) {
  assert(Solution().maxProduct(nums) == expected);
}

int main() {
  test({2, 3, -2, 4}, 6);
  test({-2, 0, -1}, 0);
  test({-2}, -2);
  test({-2, 3, -4}, 24);
  test({-1, -2, -3}, 6);
  test({2, -5, -2, -4, 3}, 24);
  test({0, 2}, 2);
  test({0, 0}, 0);
  test({10, 10, 10, 10, 10, 10, 10, 10, 10}, 1000000000);
  cout << "All tests passed\n";
}
