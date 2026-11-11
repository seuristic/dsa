# 013. Counting Bits

**Difficulty:** Easy · **Tags:** bit manipulation, dynamic programming

**Problem:** [LeetCode 338](https://leetcode.com/problems/counting-bits/) · **Video:** TODO

## Problem in Simple Words

You get an integer `n`.
For **every** number `i` from `0` to `n`, count the `1`s in its binary form.
Return all the counts as an array `ans` of size `n + 1`, where `ans[i]` is the count for `i`.
Built-ins like `__builtin_popcount` are not allowed.

## Examples

| `n` | Output               | Why                                                   |
| --- | -------------------- | ----------------------------------------------------- |
| `2` | `[0, 1, 1]`          | `0 → 0`, `1 → 1`, `2 → 10`                            |
| `5` | `[0, 1, 1, 2, 1, 2]` | `3 → 11` has two 1s, `4 → 100` has one, `5 → 101` two |

## Constraints → What They Tell Us

- `0 <= n <= 10^5`

What this means:

- **n + 1 numbers, each at most 17 bits:** counting each one bit by bit is about 17 × 10⁵ ≈ 2 × 10⁶ steps. That already passes.
- **The follow-up asks for O(n), in one pass.** So the real question is: can each answer take **O(1)**?
- **n can be 0:** the answer is just `[0]`.

## Prerequisites

- **Number of 1 Bits** ([#012](../012-number-of-1-bits/)): count the `1`s of one number.
- **`i >> 1`:** shift right, drops the last bit. Same as `i / 2`.
- **`i & 1`:** the last bit of `i` (`1` if odd, `0` if even).
- **Dynamic programming (DP):** build each answer from answers you already computed, instead of starting over.

## How to Think About It

We compute the answers **in order**: `0, 1, 2, …`. So when we're at `i`, every smaller number is already done.

Ask: _"Is there a smaller number whose bits are almost the same as `i`?"_

Yes: `i >> 1`. It's `i` with the last bit dropped.

```
i       = 1 0 1 1 0 1   (45)
i >> 1  =   1 0 1 1 0   (22)   same bits, minus the last one
i & 1   =           1          the bit we dropped
```

So:

```
ones(i) = ones(i >> 1) + (i & 1)
```

`i >> 1` is smaller than `i`, so its answer is already in the array. Each answer is **one lookup and one addition**.

## Approach 1: Brute Force (Count Each Number)

- **Idea:** For each `i` from `0` to `n`, count its bits the #012 way: add `x & 1`, then `x >>= 1`, until `x` is `0`.
- **Why it works:** It's just Number of 1 Bits, run `n + 1` times.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n log n) (each number has up to log n bits), Space O(1) besides the output
- **Why it's not enough:** Every number is counted **from scratch**. But `i` and `i >> 1` share all bits but one, and we already counted `i >> 1`. We're redoing work.

Using `x &= x - 1` from #012 for each number is a little faster (one step per `1`), but it's still O(n log n) in the worst case. The fix isn't a faster count, it's **not counting again**.

## Approach 2: Optimal (DP with i >> 1)

- **Idea:**
  1. `ans[0] = 0`.
  2. For `i` from `1` to `n`: `ans[i] = ans[i >> 1] + (i & 1)`.
- **Why it works:**
  - `i >> 1` has the same bits as `i`, without the last one. So `i` has the same number of `1`s, plus 1 if its last bit is `1`.
  - `i >> 1` is less than `i`, so `ans[i >> 1]` is already filled in.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), one pass, Space O(1) besides the output

## Dry Run (Optimal)

`n = 5`

| `i` | Binary | `i >> 1` | `ans[i >> 1]` | `i & 1` | `ans[i]` |
| --- | ------ | -------- | ------------- | ------- | -------- |
| 0   | `0`    | —        | —             | —       | **0**    |
| 1   | `1`    | 0        | 0             | 1       | **1**    |
| 2   | `10`   | 1        | 1             | 0       | **1**    |
| 3   | `11`   | 1        | 1             | 1       | **2**    |
| 4   | `100`  | 2        | 1             | 0       | **1**    |
| 5   | `101`  | 2        | 1             | 1       | **2**    |

Result: `[0, 1, 1, 2, 1, 2]`.

## Edge Cases

| Case          | Example  | What happens                                 |
| ------------- | -------- | -------------------------------------------- |
| `n = 0`       | `0`      | Loop doesn't run → `[0]`                     |
| `n = 1`       | `1`      | `ans[1] = ans[0] + 1` → `[0, 1]`             |
| Powers of 2   | `16`     | `ans[16] = ans[8] + 0 = … = ans[1] = 1`      |
| All ones      | `65535`  | Sixteen `1`s → each step adds 1 → `16`       |
| Largest input | `100000` | 100,001 lookups, instant → `ans[100000] = 6` |

## Common Mistakes

- **Array of size `n` instead of `n + 1`:** the answer includes both `0` and `n`.
- **`i >> 1 + (i & 1)`:** `+` binds tighter than `>>`, so this is `i >> (1 + (i & 1))`. Write `ans[i >> 1] + (i & 1)` with the index in its own brackets.
- **`ans[i >> 1] + i & 1`:** `+` binds tighter than `&` too. Bracket `(i & 1)`.
- **Starting the loop at 0:** `ans[0 >> 1]` is `ans[0]` itself. It happens to work, but start at `1` and let `ans[0] = 0` be the base case.
- **Using `__builtin_popcount`:** works, but the problem says not to.

## Comparison

| Approach          | Time       | Space (extra) | Note                                        |
| ----------------- | ---------- | ------------- | ------------------------------------------- |
| Count each number | O(n log n) | O(1)          | Number of 1 Bits, n + 1 times               |
| DP with `i >> 1`  | **O(n)**   | O(1)          | Reuse the answer for `i / 2`, plus last bit |

## Pattern Takeaway

- **"Answer for every number from 0 to n" → try DP.** Ask which smaller number's answer you can reuse.
- **Bits + DP:** `i >> 1` (drop last bit) and `i & (i - 1)` (drop lowest `1`) both give a smaller number that's already solved.
- **Compute in order so the smaller answers are ready** when you need them.

## Practice Next

| Problem                                                                                                | Difficulty | How it relates                                  |
| ------------------------------------------------------------------------------------------------------ | ---------- | ----------------------------------------------- |
| [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) ([#012](../012-number-of-1-bits/)) | Easy       | Count bits of one number                        |
| [Power of Two](https://leetcode.com/problems/power-of-two/)                                            | Easy       | Exactly one `1` bit: `n & (n - 1) == 0`         |
| [Missing Number](https://leetcode.com/problems/missing-number/)                                        | Easy       | Bits over all numbers 0 to n, next in Blind 75  |
| [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)                                      | Easy       | Classic DP: build each answer from earlier ones |

## Interview Follow-ups

- **"Another O(n) formula?"** → `ans[i] = ans[i & (i - 1)] + 1`. `i & (i - 1)` is `i` with its lowest `1` removed (the #012 trick), so it has exactly one `1` fewer.
- **"Another one, with powers of 2?"** → Keep `offset` = the largest power of 2 up to `i`. Then `ans[i] = 1 + ans[i - offset]` (remove the top bit instead of the bottom one).
- **"Only need the total number of 1s from 0 to n?"** → Sum the array, or count per bit position with a formula in O(log n).
- **"Why not just call popcount n times?"** → That's O(n) with a hardware instruction, but the problem bans it, and the DP shows you can reuse work without it.

## TL;DR

- `i >> 1` is `i` without its last bit, and it's already solved.
- `ans[i] = ans[i >> 1] + (i & 1)`.
- One pass from `1` to `n`, `ans[0] = 0`.
- O(n) time, O(1) extra space.
