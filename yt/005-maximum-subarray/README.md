# 005. Maximum Subarray

**Difficulty:** Medium · **Tags:** array, dynamic programming, Kadane's algorithm

**Problem:** [LeetCode 53](https://leetcode.com/problems/maximum-subarray/) · **Video:** [YouTube](https://youtu.be/8K4adjGnJTw)

## Problem in Simple Words

You get an array `nums`.
A **subarray** is a continuous part of it (no skipping), with at least one number.
Return the **largest sum** any subarray can have.

## Examples

| `nums`                            | Output | Why                                   |
| --------------------------------- | ------ | ------------------------------------- |
| `[-2, 1, -3, 4, -1, 2, 1, -5, 4]` | `6`    | `[4, -1, 2, 1]` sums to `6`           |
| `[1]`                             | `1`    | Only one subarray: `[1]`              |
| `[5, 4, -1, 7, 8]`                | `23`   | The whole array; the `-1` is worth it |

## Constraints → What They Tell Us

- `1 <= nums.length <= 10^5`
- `-10^4 <= nums[i] <= 10^4`

What this means:

- **n ≤ 10⁵:** there are about n²/2 = 5 × 10⁹ subarrays. Even checking each one in O(1) is **too slow**. We need O(n).
- **Sums stay small:** at most 10⁵ × 10⁴ = 10⁹ in size, which fits in `int`.
- **Numbers can be negative:** every number might be negative. The answer is then the **largest single number**, not `0`.
- **At least one number:** an empty subarray isn't allowed.

## Prerequisites

- **Arrays and loops:** nested loops over `i` and `j`.
- **Running sum:** adding one number at a time instead of re-adding everything.
- **`max`:** keeping the best value seen so far.

## How to Think About It

Ask yourself: _"Walking left to right, what's the best subarray that **ends right here**?"_

At each number `x`, there are only two choices:

- **Extend:** add `x` to the best subarray that ended just before it.
- **Restart:** start a new subarray at `x`.

When is restarting better? When the sum carried from the left is **negative**. A negative sum only drags `x` down, so drop it.

```
nums:      -2   1  -3   4  -1   2   1  -5   4
current:   -2   1  -2   4   3   5   6   1   5
                   ↑    ↑
     carried sum is -2  → restart at 4
```

The answer is the largest `current` seen anywhere. This is **Kadane's algorithm**.

## Approach 1: Brute Force

- **Idea:** Try every subarray `[i, j]`. Add up its numbers with a third loop. Keep the largest sum.
- **Why it works:** Every possible subarray is checked.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n³), Space O(1)
- **Why it's not enough:** The sum of `[i, j + 1]` is just the sum of `[i, j]` plus `nums[j + 1]`. We re-add the same numbers from scratch every time.

## Approach 2: Better (Running Sum)

- **Idea:** Fix the start `i`. Move `j` to the right, adding `nums[j]` to a running `sum`. Update `best` after every step.
- **Why it works:** For a fixed `i`, the running sum is exactly the sum of `[i, j]` at each step. So we still see every subarray, without the third loop.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** We still try every start `i`. But if the sum carried from the left is negative, no good subarray should start there. Kadane decides "extend or restart" on the spot, in one pass.

## Approach 3: Optimal (Kadane's Algorithm)

- **Idea:** Keep `current` = best sum of a subarray **ending at the current number**. For each `x`:
  1. `current = max(x, current + x)` → restart at `x`, or extend.
  2. `best = max(best, current)`.
- **Why it works:** Every subarray ends somewhere. At each position, `current` is the best sum ending there: either `x` alone, or `x` added to the best sum ending just before. So the overall best is the largest `current` ever seen.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1)

## Dry Run (Optimal)

`nums = [-2, 1, -3, 4, -1, 2, 1, -5, 4]`, start with `current = 0`, `best = INT_MIN`.

| `x` | `current + x` | `current = max(x, current + x)` | Choice  | `best` |
| --- | ------------- | ------------------------------- | ------- | ------ |
| -2  | -2            | -2                              | either  | -2     |
| 1   | -1            | 1                               | restart | 1      |
| -3  | -2            | -2                              | extend  | 1      |
| 4   | 2             | 4                               | restart | 4      |
| -1  | 3             | 3                               | extend  | 4      |
| 2   | 5             | 5                               | extend  | 5      |
| 1   | 6             | 6                               | extend  | **6**  |
| -5  | 1             | 1                               | extend  | 6      |
| 4   | 5             | 5                               | extend  | 6      |

Answer: `6`, from `[4, -1, 2, 1]`.

## Edge Cases

| Case                | Example               | What happens                                        |
| ------------------- | --------------------- | --------------------------------------------------- |
| One number          | `[-5]`                | That number is the answer → `-5`                    |
| All negative        | `[-3, -1, -2]`        | Best is the largest single number → `-1`            |
| All zeros           | `[0, 0, 0]`           | → `0`                                               |
| Whole array is best | `[5, 4, -1, 7, 8]`    | Never restarts → `23`                               |
| Dip worth keeping   | `[2, -1, 2]`          | `2 - 1 + 2 = 3` beats `2` → extend through the `-1` |
| Dip not worth it    | `[1, -10, 5]`         | Carried sum becomes `-9` → restart at `5`           |
| Extreme values      | `[-10^4, 10^4, 10^4]` | → `20000`, fits in `int`                            |

## Common Mistakes

- **Starting `best` at `0`:** for `[-3, -1, -2]` it returns `0`, but the answer is `-1`. Start at `INT_MIN` (or `nums[0]`).
- **Resetting to `0` before updating `best`:** in the "if `sum < 0` then `sum = 0`" version, update `best` **first**, or all-negative arrays break.
- **Restarting when `x` is negative:** the rule is about the **carried sum**, not `x`. `[2, -1, 2]` must keep the `-1`.
- **Confusing subarray with subsequence:** a subarray is continuous. You can't skip the negative numbers in the middle.

## Comparison

| Approach    | Time     | Space | Note                                |
| ----------- | -------- | ----- | ----------------------------------- |
| Brute force | O(n³)    | O(1)  | Re-adds every subarray from scratch |
| Running sum | O(n²)    | O(1)  | Still tries every start             |
| Kadane      | **O(n)** | O(1)  | Extend or restart, one pass         |

## Pattern Takeaway

- **"Best subarray" → think about the best one ending at each index.** Then the answer is the max over all ends.
- **Extend or restart:** if what you carry from the left hurts you (negative sum), drop it.
- **This is dynamic programming in disguise:** `dp[i] = max(nums[i], dp[i - 1] + nums[i])`. Kadane just keeps `dp[i - 1]` in one variable.
- **Same shape as Best Time to Buy and Sell Stock (#002):** remember the best thing so far, update it in one pass.

## Practice Next

| Problem                                                                                                                                             | Difficulty | How it relates                                                   |
| --------------------------------------------------------------------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------------- |
| [Best Time to Buy and Sell Stock](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) ([#002](../002-best-time-to-buy-and-sell-stock/)) | Easy       | Kadane on the daily price differences                            |
| [Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)                                                                 | Medium     | Same idea with products; track both max and min (negatives flip) |
| [Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/)                                                       | Medium     | Kadane twice: best subarray, or total minus the worst subarray   |
| [Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/)                                         | Medium     | Kadane for the max and for the min                               |

## Interview Follow-ups

- **"Return the subarray, not just the sum."** → Track `start`: when you restart, set `start = i`. When `best` improves, save `(start, i)`.
- **"Empty subarray allowed (answer at least `0`)?"** → Start `best` at `0` instead of `INT_MIN`.
- **"Solve it with prefix sums."** → Sum of `[i, j]` = `prefix[j + 1] - prefix[i]`. For each `j`, subtract the **smallest prefix before it**. That's exactly the stock problem. O(n), O(1).
- **"Divide and conquer?"** (LeetCode's follow-up) → Split in half. The answer is in the left half, the right half, or **crosses the middle** (best suffix of left + best prefix of right). O(n log n), slower than Kadane but a good recursion exercise.
- **"Numbers are huge?"** → Use `long long` for `current` and `best`.

## TL;DR

- At each number: `current = max(x, current + x)` (restart or extend).
- `best = max(best, current)`.
- Start `best` at `INT_MIN` so all-negative arrays work.
- O(n) time, O(1) space.
