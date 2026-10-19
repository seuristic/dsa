// Optimal: One-Pass Hash Map — Time: O(n), Space: O(n)
// Idea: For each number, check if its partner (target - num) was already
// seen. If yes, done. If not, remember this number and its index.
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;  // value -> index
    for (int i = 0; i < (int)nums.size(); i++) {
      int need = target - nums[i];  // fits in int: |need| <= 2e9 < INT_MAX
      if (seen.count(need)) return {seen[need], i};
      seen[nums[i]] = i;  // add after the check: never pair with itself
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
