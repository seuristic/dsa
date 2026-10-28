# 006. Maximum Product Subarray

**Difficulty:** Medium · **Tags:** array, dynamic programming

**Problem:** [LeetCode 152](https://leetcode.com/problems/maximum-product-subarray/) · **Video:** TODO

## Problem in Simple Words

You get an array `nums`.
A **subarray** is a continuous part of it, with at least one number.
Return the **largest product** any subarray can have.

## Examples

| `nums`          | Output | Why                                                          |
| --------------- | ------ | ------------------------------------------------------------ |
| `[2, 3, -2, 4]` | `6`    | `[2, 3]` gives `6`. Adding `-2` makes it negative            |
| `[-2, 0, -1]`   | `0`    | `[-2, -1]` would give `2`, but it skips the `0`: not allowed |

## Constraints → What They Tell Us

- `1 <= nums.length <= 2 * 10^4`
- `-10 <= nums[i] <= 10`
- The product of any subarray fits in a 32-bit `int`.

What this means:

- **n ≤ 2 × 10⁴:** about 2 × 10⁸ subarrays. Checking them all is borderline at best. We want O(n).
- **Negatives:** two negatives multiply into a positive. The **smallest** product so far can become the **largest** after one more negative.
- **Zeros:** a `0` wipes out every product through it. A subarray should never cross a zero (unless the answer is `0` itself).
- **Products grow fast:** nine `10`s already make 10⁹. LeetCode promises every subarray product fits in `int`, but we use `long long` as a cheap safety net.

## Prerequisites

- **Maximum Subarray / Kadane's algorithm** ([#005](../005-maximum-subarray/)): "best subarray ending here", extend or restart.
- **Sign rules:** negative × negative = positive, anything × 0 = 0.
- **`max({a, b, c})` / `min({a, b, c})`:** max or min of three values in C++.

## How to Think About It

Start from Kadane (#005): keep the best product **ending here**, and either extend or restart.

Now try it on `[-2, 3, -4]`:

```
best ending at -2: -2
best ending at  3:  3        (restart; -2 · 3 = -6 is worse)
best ending at -4: max(-4, 3 · -4 = -12) = -4   ✗ wrong!
real answer: -2 · 3 · -4 = 24
```

What went wrong? At `3`, we threw away `-6` because it was the **worst**. But a very negative number times a negative becomes a very **positive** number.

So ask: _"What's the best product ending here, **and** what's the worst?"_

- `maxEnd` = largest product of a subarray ending here.
- `minEnd` = smallest (most negative) product of a subarray ending here.
- At each `x`, the new max and min both come from one of: `x` alone, `maxEnd · x`, or `minEnd · x`.

## Approach 1: Brute Force

- **Idea:** Try every subarray `[i, j]`. Multiply its numbers with a third loop. Keep the largest product.
- **Why it works:** Every possible subarray is checked.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n³), Space O(1)
- **Why it's not enough:** The product of `[i, j + 1]` is the product of `[i, j]` times `nums[j + 1]`. We redo the same multiplications every time.

## Approach 2: Better (Running Product)

- **Idea:** Fix the start `i`. Move `j` to the right, multiplying a running `product` by `nums[j]`. Update `best` after every step.
- **Why it works:** For a fixed `i`, the running product is exactly the product of `[i, j]`. We still see every subarray, without the third loop.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** We still try every start. Kadane does it in one pass, but only if we also remember the **smallest** product ending at each spot, because negatives flip it.

## Approach 3: Optimal (Track Max and Min)

- **Idea:** Start with `maxEnd = minEnd = best = nums[0]`. For each next `x`:
  1. `a = maxEnd · x`, `b = minEnd · x`.
  2. `maxEnd = max(x, a, b)`, `minEnd = min(x, a, b)`.
  3. `best = max(best, maxEnd)`.
- **Why it works:** Any subarray ending at `x` is either `x` alone, or `x` times a subarray ending just before it. Multiplying by `x` keeps the order when `x` is positive and flips it when `x` is negative. So the new extremes always come from the old extremes. Both `a` and `b` are computed **before** updating, so we never use a half-updated value.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1)

## Dry Run (Optimal)

`nums = [-2, 3, -4]`, start with `maxEnd = minEnd = best = -2`.

| `x` | `a = maxEnd · x` | `b = minEnd · x` | `maxEnd` | `minEnd` | `best` |
| --- | ---------------- | ---------------- | -------- | -------- | ------ |
| 3   | -6               | -6               | 3        | -6       | 3      |
| -4  | -12              | **24**           | 24       | -12      | **24** |

At `-4`, the **min** (`-6`) times a negative gives the new **max** (`24`). Without `minEnd`, we'd miss it.

## Edge Cases

| Case                  | Example                  | What happens                                 |
| --------------------- | ------------------------ | -------------------------------------------- |
| One number            | `[-2]`                   | That number is the answer → `-2`             |
| Zero splits the array | `[-2, 0, -1]`            | `x = 0` resets both max and min to `0` → `0` |
| Two negatives         | `[-1, -2, -3]`           | `-2 · -3 = 6`                                |
| Odd negatives         | `[2, -5, -2, -4, 3]`     | Drop one negative: `-2 · -4 · 3 = 24`        |
| Zero then positive    | `[0, 2]`                 | Restart after the `0` → `2`                  |
| All zeros             | `[0, 0]`                 | → `0`                                        |
| Big products          | `[10, 10, …, 10]` (nine) | → `10^9`, still fits in `int`                |

## Common Mistakes

- **Copying Kadane with only `maxEnd`:** fails on `[-2, 3, -4]` (returns `3`, answer is `24`). Track `minEnd` too.
- **Updating `maxEnd` before computing `minEnd`:** then `minEnd` uses the **new** `maxEnd`. Compute `a` and `b` first (or save the old value).
- **Starting `best` at `0`:** `[-2]` must return `-2`. Start at `nums[0]`.
- **Treating it like the sum version:** "drop negatives" doesn't work here. A negative can be the best thing to keep, if another negative comes later.
- **Forgetting zeros:** `0` is a valid answer, and it also breaks the array into separate parts.

## Comparison

| Approach          | Time     | Space | Note                                    |
| ----------------- | -------- | ----- | --------------------------------------- |
| Brute force       | O(n³)    | O(1)  | Re-multiplies every subarray            |
| Running product   | O(n²)    | O(1)  | Still tries every start                 |
| Track max and min | **O(n)** | O(1)  | Kadane, plus the min for negative flips |

## Pattern Takeaway

- **Kadane works for products if you keep both extremes.** Negatives turn the worst into the best.
- **"Best subarray ending here" is the DP state.** When one value isn't enough to decide the future, keep two (max and min).
- **Multiplying by a negative flips order:** whenever signs matter, ask "could the smallest become the largest?"

## Practice Next

| Problem                                                                                                                             | Difficulty | How it relates                                             |
| ----------------------------------------------------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------- |
| [Maximum Product of Three Numbers](https://leetcode.com/problems/maximum-product-of-three-numbers/)                                 | Easy       | The two most negative numbers can make the biggest product |
| [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/) ([#005](../005-maximum-subarray/))                              | Medium     | The sum version: Kadane with only one value                |
| [Maximum Length of Subarray With Positive Product](https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/) | Medium     | Same sign-flip idea, tracking lengths instead of products  |
| [Subarray Product Less Than K](https://leetcode.com/problems/subarray-product-less-than-k/)                                         | Medium     | Products over subarrays, with a sliding window             |

## Interview Follow-ups

- **"Another O(n) way?"** → Prefix and suffix scan. Multiply left to right and right to left, resetting to `1` after a `0`. The answer is the largest running product seen in either direction. It works because the best subarray always drops either a left part or a right part (to remove one extra negative).
- **"Return the subarray itself."** → Track where `maxEnd` and `minEnd` start, the same way as in #005.
- **"Products can be huge?"** → `long long` for bigger limits, or compare with logarithms if only the position matters.
- **"Maximum product of a subsequence (can skip numbers)?"** → Different problem: take all non-zero numbers, then drop the negative closest to zero if the count of negatives is odd.

## TL;DR

- Keep `maxEnd` and `minEnd` for subarrays ending here.
- At each `x`: candidates are `x`, `maxEnd · x`, `minEnd · x`. New max = max of them, new min = min of them.
- `best = max(best, maxEnd)`, starting from `nums[0]`.
- O(n) time, O(1) space.
