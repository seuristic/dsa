#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int search(vector<int>& nums, int target) {
    for (int i = 0; i < (int)nums.size(); i++) {
      if (nums[i] == target) return i;
    }
    return -1;
  }
};

void test(vector<int> nums, int target, int expected) {
  assert(Solution().search(nums, target) == expected);
}

int main() {
  test({4, 5, 6, 7, 0, 1, 2}, 0, 4);
  test({4, 5, 6, 7, 0, 1, 2}, 3, -1);
  test({1}, 0, -1);
  test({1}, 1, 0);
  test({3, 1}, 1, 1);
  test({3, 1}, 3, 0);
  test({1, 3}, 3, 1);
  test({5, 1, 3}, 5, 0);
  test({4, 5, 6, 7, 0, 1, 2}, 7, 3);
  test({1, 2, 3, 4, 5}, 4, 3);
  test({6, 7, 1, 2, 3, 4, 5}, 10000, -1);
  test({-10000, 10000}, -10000, 0);
  cout << "All tests passed\n";
}
