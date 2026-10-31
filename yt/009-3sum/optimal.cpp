#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> result;

    for (int i = 0; i < n - 2; i++) {
      if (i > 0 && nums[i] == nums[i - 1]) continue;

      int left = i + 1, right = n - 1;

      while (left < right) {
        int sum = nums[i] + nums[left] + nums[right];

        if (sum < 0) {
          left++;
        } else if (sum > 0) {
          right--;
        } else {
          result.push_back({nums[i], nums[left], nums[right]});
          left++;
          right--;
          while (left < right && nums[left] == nums[left - 1]) left++;
        }
      }
    }

    return result;
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
