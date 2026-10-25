#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> answer(n);
    for (int i = 0; i < n; i++) {
      int product = 1;
      for (int j = 0; j < n; j++) {
        if (j != i) product *= nums[j];
      }
      answer[i] = product;
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
