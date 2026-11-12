#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int result = n;

    for (int i = 0; i < n; i++) {
      result ^= i ^ nums[i];
    }

    return result;
  }
};

void test(vector<int> nums, int expected) {
  assert(Solution().missingNumber(nums) == expected);
}

int main() {
  test({3, 0, 1}, 2);
  test({0, 1}, 2);
  test({9, 6, 4, 2, 3, 5, 7, 0, 1}, 8);
  test({0}, 1);
  test({1}, 0);
  test({1, 2, 3}, 0);
  test({0, 1, 2, 3}, 4);
  test({2, 0}, 1);

  vector<int> big;
  for (int x = 10000; x >= 0; x--) {
    if (x != 5000) {
      big.push_back(x);
    }
  }
  test(big, 5000);
  cout << "All tests passed\n";
}
