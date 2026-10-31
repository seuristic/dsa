#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    int n = nums.size();
    set<vector<int>> found;

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        for (int k = j + 1; k < n; k++) {
          if (nums[i] + nums[j] + nums[k] == 0) {
            vector<int> triplet = {nums[i], nums[j], nums[k]};
            sort(triplet.begin(), triplet.end());
            found.insert(triplet);
          }
        }
      }
    }

    return vector<vector<int>>(found.begin(), found.end());
  }
};

void test(vector<int> nums, vector<vector<int>> expected) {
  vector<vector<int>> result = Solution().threeSum(nums);
  for (auto& triplet : result) sort(triplet.begin(), triplet.end());
  sort(result.begin(), result.end());
  assert(result == expected);
}

int main() {
  test({-1, 0, 1, 2, -1, -4}, {{-1, -1, 2}, {-1, 0, 1}});
  test({0, 1, 1}, {});
  test({0, 0, 0}, {{0, 0, 0}});
  test({0, 0, 0, 0}, {{0, 0, 0}});
  test({-2, 0, 1, 1, 2}, {{-2, 0, 2}, {-2, 1, 1}});
  test({1, 2, 3}, {});
  test({-1, -1, -1, 2, 2}, {{-1, -1, 2}});
  test({3, -2, 1, 0}, {});
  test({-100000, 50000, 50000}, {{-100000, 50000, 50000}});
  cout << "All tests passed\n";
}
