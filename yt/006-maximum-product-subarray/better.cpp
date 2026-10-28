#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxProduct(vector<int>& nums) {
    int n = nums.size();
    long long best = LLONG_MIN;
    for (int i = 0; i < n; i++) {
      long long product = 1;
      for (int j = i; j < n; j++) {
        product *= nums[j];
        best = max(best, product);
      }
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
