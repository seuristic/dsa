#include <bits/stdc++.h>
using namespace std;

// RMQ
class SegmentTree {
private:
  int n;
  vector<int> a, tree, lazy;

  int left(int p) { return p << 1; }
  int right(int p) { return (p << 1) + 1; }

  int conquer(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return min(a, b);
  }

  void build(int p, int l, int r) {
    if (l == r) tree[p] = a[l];
    else {
      int m = (l + r) / 2;
      build(left(p), l, m);
      build(right(p), m + 1, r);
      tree[p] = conquer(tree[left(p)], tree[right(p)]);
    }
  }

  void propagate(int p, int l, int r) {
    if (lazy[p] != -1) {
      tree[p] = lazy[p];
      if (l == r) a[l] = lazy[p];
      else lazy[left(p)] = lazy[right(p)] = lazy[p];
      lazy[p] = -1;
    }
  }

  void update(int p, int l, int r, int i, int j, int val) {
    propagate(p, l, r);
    if (i > j) return;
    if (i <= l && r <= j) {
      lazy[p] = val;
      propagate(p, l, r);
    } else {
      int m = (l + r) / 2;
      update(left(p), l, m, i, min(m, j), val);
      update(right(p), m + 1, r, max(i, m + 1), j, val);

      int left_subtree = (lazy[left(p)] != -1) ? lazy[left(p)] : tree[left(p)];
      int right_subtree =
          (lazy[right(p)] != -1) ? lazy[right(p)] : tree[right(p)];

      tree[p] =
          (left_subtree <= right_subtree) ? tree[left(p)] : tree[right(p)];
    }
  }

  int rmq(int p, int l, int r, int i, int j) {
    propagate(p, l, r);
    if (i > j) return -1;
    if (i <= l && r <= j) return tree[p];
    int m = (l + r) / 2;
    return conquer(
        rmq(left(p), l, m, i, min(m, j)),
        rmq(right(p), m + 1, r, max(i, m + 1), j)
    );
  }

public:
  SegmentTree(int sz) : n(sz), tree(4 * n), lazy(4 * n, -1) {}
  SegmentTree(const vector<int>& initial_a)
      : SegmentTree((int)initial_a.size()) {
    a = initial_a;
    build(1, 0, n - 1);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  int rmq(int i, int j) { return rmq(1, 0, n - 1, i, j); }
};

// RSQ
class SegmentTree2 {
private:
  int n;
  vector<int> tree, lazy;

  int left(int p) { return p << 1; }
  int right(int p) { return (p << 1) + 1; }

  int conquer(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    return a + b;
  }

  void build(int p, int l, int r, const vector<int>& arr) {
    if (l == r) tree[p] = arr[l];
    else {
      int m = (l + r) / 2;
      build(left(p), l, m, arr);
      build(right(p), m + 1, r, arr);
      tree[p] = conquer(tree[left(p)], tree[right(p)]);
    }
  }

  void propagate(int p, int l, int r) {
    if (lazy[p] != -1) {
      tree[p] = (r - l + 1) * lazy[p];

      if (l != r) {
        lazy[left(p)] = lazy[p];
        lazy[right(p)] = lazy[p];
      }

      lazy[p] = -1;
    }
  }

  void update(int p, int l, int r, int i, int j, int val) {
    propagate(p, l, r);

    if (i > j) return;

    if (i <= l && r <= j) {
      lazy[p] = val;
      propagate(p, l, r);
    } else {
      int m = (l + r) / 2;

      update(left(p), l, m, i, min(m, j), val);
      update(right(p), m + 1, r, max(i, m + 1), j, val);

      int left_subtree =
          (lazy[left(p)] != -1) ? (m - l + 1) * lazy[left(p)] : tree[left(p)];

      int right_subtree =
          (lazy[right(p)] != -1) ? (r - m) * lazy[right(p)] : tree[right(p)];

      tree[p] = left_subtree + right_subtree;
    }
  }

  int rsq(int p, int l, int r, int i, int j) {
    propagate(p, l, r);

    if (i > j) return -1;

    if (i <= l && r <= j) return tree[p];

    int m = (l + r) / 2;

    return conquer(
        rsq(left(p), l, m, i, min(m, j)),
        rsq(right(p), m + 1, r, max(i, m + 1), j)
    );
  }

public:
  SegmentTree2(int sz) : n(sz), tree(4 * n), lazy(4 * n, -1) {}

  SegmentTree2(const vector<int>& arr) : SegmentTree2((int)arr.size()) {
    build(1, 0, n - 1, arr);
  }

  void update(int i, int j, int val) { update(1, 0, n - 1, i, j, val); }

  int rsq(int i, int j) { return rsq(1, 0, n - 1, i, j); }
};
