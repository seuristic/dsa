#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> answer(n, 1);
    for (int i = 1; i < n; i++) answer[i] = answer[i - 1] * nums[i - 1];
    int suffix = 1;
    for (int i = n - 1; i >= 0; i--) {
      answer[i] *= suffix;
      suffix *= nums[i];
    }
    return answer;
  }
};

void test(vector<int> nums, vector<int> expected) {
  assert(Solution().productExceptSelf(nums) == expected);
}

int main() {
  test({1, 2, 3, 4}, {24, 12, 8, 6});
  test({-1, 1, 0, -3, 3}, {0, 0, 9, 0, 0});
  test({2, 3}, {3, 2});
  test({0, 4, 5}, {20, 0, 0});
  test({5, 0, 2, 0}, {0, 0, 0, 0});
  test({-2, -3, 4}, {-12, -8, 6});
  test({1, 1, 1, 1}, {1, 1, 1, 1});
  cout << "All tests passed\n";
}
