#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int findMin(vector<int>& nums) {
    int smallest = nums[0];
    for (int x : nums) smallest = min(smallest, x);
    return smallest;
  }
};

void test(vector<int> nums, int expected) {
  assert(Solution().findMin(nums) == expected);
}

int main() {
  test({3, 4, 5, 1, 2}, 1);
  test({4, 5, 6, 7, 0, 1, 2}, 0);
  test({11, 13, 15, 17}, 11);
  test({1}, 1);
  test({2, 1}, 1);
  test({1, 2}, 1);
  test({5, 1, 2, 3, 4}, 1);
  test({2, 3, 4, 5, 1}, 1);
  test({0, 5000, -5000, -1}, -5000);
  cout << "All tests passed\n";
}
