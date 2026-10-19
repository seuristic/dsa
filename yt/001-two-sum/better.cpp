// Better: Sort + Two Pointers — Time: O(n log n), Space: O(n)
// Idea: Sort (value, original index) pairs, then move two pointers inward
// from both ends until their sum equals target.
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    // Keep original indices: sorting moves the values around
    vector<pair<int, int>> a(n);  // (value, original index)
    for (int i = 0; i < n; i++) a[i] = {nums[i], i};
    sort(a.begin(), a.end());

    int l = 0, r = n - 1;
    while (l < r) {
      int sum = a[l].first + a[r].first;
      if (sum == target) return {a[l].second, a[r].second};
      if (sum < target) l++;  // too small: only a bigger left value can help
      else r--;               // too big: only a smaller right value can help
    }
    return {};  // never reached: exactly one answer is guaranteed
  }
};

void test(vector<int> nums, int target, vector<int> expected) {
  vector<int> got = Solution().twoSum(nums, target);
  sort(got.begin(), got.end());  // any order is accepted
  assert(got == expected);
}

int main() {
  // Examples from the statement
  test({2, 7, 11, 15}, 9, {0, 1});
  test({3, 2, 4}, 6, {1, 2});
  test({3, 3}, 6, {0, 1});
  // Edge cases
  test({-3, 4, 3, 90}, 0, {0, 2});                // negative numbers
  test({0, 4, 3, 0}, 0, {0, 3});                  // zeros + duplicates
  test({1000000000, 5, -1000000000}, 0, {0, 2});  // extreme values
  test({1, 2, 3, 4, 5}, 9, {3, 4});               // answer at the very end
  cout << "All tests passed\n";
}
