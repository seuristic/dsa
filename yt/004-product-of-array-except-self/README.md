# 004. Product of Array Except Self

**Difficulty:** Medium · **Tags:** array, prefix sum (prefix product)

**Problem:** [LeetCode 238](https://leetcode.com/problems/product-of-array-except-self/) · **Video:** [YouTube](https://youtu.be/QBfYD1D2ZQE)

## Problem in Simple Words

You get an array `nums`.
Build a new array `answer` where `answer[i]` is the product of **every number except `nums[i]`**.
You **can't use division**, and it must run in O(n) time.

## Examples

| `nums`              | Output            | Why                                                          |
| ------------------- | ----------------- | ------------------------------------------------------------ |
| `[1, 2, 3, 4]`      | `[24, 12, 8, 6]`  | `answer[0] = 2·3·4 = 24`, `answer[1] = 1·3·4 = 12`, …        |
| `[-1, 1, 0, -3, 3]` | `[0, 0, 9, 0, 0]` | Every product includes the `0`, except at the `0`'s own spot |

## Constraints → What They Tell Us

- `2 <= nums.length <= 10^5`
- `-30 <= nums[i] <= 30`
- The product of any prefix or suffix fits in a 32-bit `int`.

What this means:

- **n ≤ 10⁵:** for each `i`, multiplying all other numbers is about 10¹⁰ operations. **Too slow.** We need O(n).
- **Prefix/suffix products fit in `int`:** no `long long` needed. The problem promises it.
- **Values can be `0` or negative:** zeros are the reason "total product ÷ `nums[i]`" breaks (you can't divide by zero). And division isn't allowed anyway.
- **n ≥ 2:** every `answer[i]` has at least one other number to multiply.

## Prerequisites

- **Arrays and loops:** going left to right, and right to left.
- **Prefix sums:** `prefix[i]` = sum of everything before `i`. Here we use the same idea with **multiplication** (a prefix product).

## How to Think About It

Ask yourself: _"What does 'everything except `nums[i]`' look like?"_

```
nums:   [ a   b   c   d   e ]
                  ↑
                  i
except i = (a · b)  ·  (d · e)
           left of i   right of i
```

- "Everything except `i`" = **everything to the left** × **everything to the right**.
- Both sides grow one number at a time as `i` moves. So we never need to recompute them from scratch.
- Left products are easy going left → right. Right products are easy going right → left. Do both passes.

## Approach 1: Brute Force

- **Idea:** For each `i`, multiply every `nums[j]` with `j != i`.
- **Why it works:** It's the definition of the problem, done directly.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n²), Space O(1) extra (the output array doesn't count)
- **Why it's not enough:** For `i` and `i + 1`, almost the same numbers get multiplied again. The left part for `i + 1` is just the left part for `i` times `nums[i]`. We redo that work for every `i`.

## Approach 2: Better (Prefix and Suffix Arrays)

- **Idea:**
  1. `prefix[i]` = product of everything **before** `i`. `prefix[0] = 1`, then `prefix[i] = prefix[i - 1] * nums[i - 1]`.
  2. `suffix[i]` = product of everything **after** `i`. `suffix[n - 1] = 1`, then `suffix[i] = suffix[i + 1] * nums[i + 1]`.
  3. `answer[i] = prefix[i] * suffix[i]`.
- **Why it works:** `prefix[i]` covers indices `0 … i-1`, and `suffix[i]` covers `i+1 … n-1`. Together that's every index except `i`, each used exactly once.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n), Space O(n) extra (two helper arrays)
- **Why it's not enough:** The time is already optimal, but we use two extra arrays. The follow-up asks for O(1) extra space. We can store the prefix products **in `answer` itself**, and keep the suffix product in a single variable.

## Approach 3: Optimal (Two Passes, O(1) Extra Space)

- **Idea:**
  1. **Left pass:** fill `answer[i]` with the prefix product (same as `prefix[i]` above).
  2. **Right pass:** walk from the end with a variable `suffix = 1`. At each `i`, do `answer[i] *= suffix`, then `suffix *= nums[i]`.
- **Why it works:** After the left pass, `answer[i]` = product of the left side. In the right pass, `suffix` holds the product of the right side at the moment we reach `i` (we update it **after** using it). So `answer[i]` ends as left × right.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1) extra (the output array doesn't count)

## Dry Run (Optimal)

`nums = [1, 2, 3, 4]`

**Left pass** (`answer[i] = answer[i - 1] * nums[i - 1]`):

| `i` | `answer[i]` | `answer` after step |
| --- | ----------- | ------------------- |
| 0   | `1` (start) | `[1, 1, 1, 1]`      |
| 1   | `1 · 1 = 1` | `[1, 1, 1, 1]`      |
| 2   | `1 · 2 = 2` | `[1, 1, 2, 1]`      |
| 3   | `2 · 3 = 6` | `[1, 1, 2, 6]`      |

**Right pass** (`answer[i] *= suffix`, then `suffix *= nums[i]`):

| `i` | `suffix` before | `answer[i]`   | `suffix` after | `answer` after step |
| --- | --------------- | ------------- | -------------- | ------------------- |
| 3   | 1               | `6 · 1 = 6`   | `1 · 4 = 4`    | `[1, 1, 2, 6]`      |
| 2   | 4               | `2 · 4 = 8`   | `4 · 3 = 12`   | `[1, 1, 8, 6]`      |
| 1   | 12              | `1 · 12 = 12` | `12 · 2 = 24`  | `[1, 12, 8, 6]`     |
| 0   | 24              | `1 · 24 = 24` | `24 · 1 = 24`  | `[24, 12, 8, 6]`    |

## Edge Cases

| Case              | Example             | What happens                                             |
| ----------------- | ------------------- | -------------------------------------------------------- |
| Only two numbers  | `[2, 3]`            | Each answer is just the other number → `[3, 2]`          |
| One zero          | `[0, 4, 5]`         | Only the `0`'s spot is non-zero → `[20, 0, 0]`           |
| Two or more zeros | `[5, 0, 2, 0]`      | Every product includes a `0` → all `0`                   |
| Negatives         | `[-2, -3, 4]`       | Signs work out by normal multiplication → `[-12, -8, 6]` |
| All ones          | `[1, 1, 1, 1]`      | Every product is `1`                                     |
| Zero + negatives  | `[-1, 1, 0, -3, 3]` | Only the `0`'s spot is non-zero: `-1 · 1 · -3 · 3 = 9`   |

## Common Mistakes

- **Using division:** "total product ÷ `nums[i]`" fails when `nums[i] = 0` (divide by zero), and the problem forbids it.
- **Starting prefix/suffix at `0`:** the starting value for a product is `1`, not `0`. A `0` start makes everything `0`.
- **Including `nums[i]` in its own prefix:** `prefix[i]` must use `nums[i - 1]`, not `nums[i]`. Off by one → `nums[i]` gets multiplied into its own answer.
- **Updating `suffix` before using it:** in the right pass, do `answer[i] *= suffix` **first**, then `suffix *= nums[i]`. Swapping them includes `nums[i]` in its own answer.
- **Thinking the output counts as extra space:** the problem says the output array doesn't count. So the optimal is O(1) extra.

## Comparison

| Approach               | Time     | Space (extra) | Note                                         |
| ---------------------- | -------- | ------------- | -------------------------------------------- |
| Brute force            | O(n²)    | O(1)          | Too slow for n = 10⁵                         |
| Prefix + suffix arrays | O(n)     | O(n)          | Easiest O(n) idea to explain                 |
| Two passes in `answer` | **O(n)** | **O(1)**      | Prefix stored in `answer`, suffix in one var |

## Pattern Takeaway

- **"Everything except `i`" → left part × right part.** Split around `i`.
- **Prefix/suffix works for any operation that combines step by step:** sum, product, max, min.
- **Saving space:** if you need two helper arrays, store one in the output and replace the other with a running variable.

## Practice Next

| Problem                                                                                 | Difficulty | How it relates                                             |
| --------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------- |
| [Range Sum Query - Immutable](https://leetcode.com/problems/range-sum-query-immutable/) | Easy       | The basic prefix sum                                       |
| [Find Pivot Index](https://leetcode.com/problems/find-pivot-index/)                     | Easy       | Left sum vs right sum around each `i`                      |
| [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)     | Medium     | Products with zeros and negatives, next in Blind 75        |
| [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)               | Hard       | Prefix max and suffix max around each `i`, same two passes |

## Interview Follow-ups

- **"Do it in O(1) extra space."** → The optimal: prefix in `answer`, suffix in one variable.
- **"What if division were allowed?"** → Count zeros first.
  - No zeros: `answer[i] = total / nums[i]`.
  - One zero: only the zero's spot gets the product of the rest. Everything else is `0`.
  - Two or more zeros: everything is `0`.
- **"What if the products can overflow?"** → Use `long long`, or return results modulo a number if the problem allows it.
- **"Product except a range `[l, r]`?"** → `prefix[l] * suffix[r]`. Same split, just a wider gap.

## TL;DR

- `answer[i]` = (product left of `i`) × (product right of `i`).
- Pass 1 (left → right): `answer[i] = answer[i - 1] * nums[i - 1]`, starting at `1`.
- Pass 2 (right → left): `answer[i] *= suffix`, then `suffix *= nums[i]`.
- O(n) time, O(1) extra space, no division.
