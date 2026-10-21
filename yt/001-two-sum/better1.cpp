#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) a[i] = {nums[i], i};
    sort(a.begin(), a.end());

    for (int i = 0; i < n; i++) {
      int need = target - a[i].first;
      int lo = i + 1, hi = n - 1;
      while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid].first == need) return {a[i].second, a[mid].second};
        if (a[mid].first < need) lo = mid + 1;
        else hi = mid - 1;
      }
    }
    return {};
  }
};

void test(vector<int> nums, int target, vector<int> expected) {
  vector<int> got = Solution().twoSum(nums, target);
  sort(got.begin(), got.end());
  assert(got == expected);
}

int main() {
  test({2, 7, 11, 15}, 9, {0, 1});
  test({3, 2, 4}, 6, {1, 2});
  test({3, 3}, 6, {0, 1});
  test({-3, 4, 3, 90}, 0, {0, 2});
  test({0, 4, 3, 0}, 0, {0, 3});
  test({1000000000, 5, -1000000000}, 0, {0, 2});
  test({1, 2, 3, 4, 5}, 9, {3, 4});
  cout << "All tests passed\n";
}
