#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX, best = 0;
    for (int price : prices) {
      minPrice = min(minPrice, price);
      best = max(best, price - minPrice);
    }
    return best;
  }
};

void test(vector<int> prices, int expected) {
  assert(Solution().maxProfit(prices) == expected);
}

int main() {
  test({7, 1, 5, 3, 6, 4}, 5);
  test({7, 6, 4, 3, 1}, 0);
  test({5}, 0);
  test({3, 3, 3}, 0);
  test({1, 2, 3, 4, 5}, 4);
  test({2, 4, 1}, 2);
  test({3, 8, 1, 4}, 5);
  test({0, 10000}, 10000);
  cout << "All tests passed\n";
}
