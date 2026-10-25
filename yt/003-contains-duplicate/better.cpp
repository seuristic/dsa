#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  bool containsDuplicate(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    for (int i = 1; i < (int)nums.size(); i++) {
      if (nums[i] == nums[i - 1]) return true;
    }
    return false;
  }
};

void test(vector<int> nums, bool expected) {
  assert(Solution().containsDuplicate(nums) == expected);
}

int main() {
  test({1, 2, 3, 1}, true);
  test({1, 2, 3, 4}, false);
  test({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}, true);
  test({5}, false);
  test({7, 7}, true);
  test({-1, 2, -1}, true);
  test({1000000000, -1000000000}, false);
  test({1, 2, 3, 4, 5, 1}, true);
  cout << "All tests passed\n";
}
