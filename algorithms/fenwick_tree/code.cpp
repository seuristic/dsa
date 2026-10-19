#include <bits/stdc++.h>
using namespace std;

#define LSOne(x) ((x) & -(x))

class FenwickTree {
  vector<long long> ft;

public:
  FenwickTree(int m) { ft.assign(m + 1, 0); }

  long long rsq(int i) {
    long long sum = 0;
    for (; i; i -= LSOne(i)) {
      sum += ft[i];
    }
    return sum;
  }

  void update(int i, long long v) {
    for (; i < int(ft.size()); i += LSOne(i)) {
      ft[i] += v;
    }
  }
};
