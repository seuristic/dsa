# 014. Missing Number

**Difficulty:** Easy · **Tags:** array, bit manipulation, math

**Problem:** [LeetCode 268](https://leetcode.com/problems/missing-number/) · **Video:** TODO

## Problem in Simple Words

You get an array `nums` of `n` **different** numbers.
They should be all the numbers from `0` to `n`, but that's `n + 1` numbers, so **exactly one is missing**.
Return the missing one.

## Examples

| `nums`                        | Output | Why                                             |
| ----------------------------- | ------ | ----------------------------------------------- |
| `[3, 0, 1]`                   | `2`    | n = 3, range is 0 to 3, and `2` isn't there     |
| `[0, 1]`                      | `2`    | n = 2, range is 0 to 2. The missing one is `n`! |
| `[9, 6, 4, 2, 3, 5, 7, 0, 1]` | `8`    | n = 9, range is 0 to 9, and `8` isn't there     |

## Constraints → What They Tell Us

- `n == nums.length`, `1 <= n <= 10^4`
- `0 <= nums[i] <= n`
- All numbers are unique.

What this means:

- **n ≤ 10⁴:** even O(n²) ≈ 10⁸ passes, but it's slow. O(n) is the goal.
- **Follow-up: O(1) extra space.** No hash set, no extra array.
- **Unique and in `[0, n]`:** every number from `0` to `n` appears **once**, except one that appears **zero** times. That's the property we'll use.
- **The missing number can be `0` or `n`** (the ends of the range), not just something in the middle.

## Prerequisites

- **Sum from 0 to n:** `0 + 1 + … + n = n(n + 1) / 2` (Gauss's formula).
- **XOR (`^`):** a bitwise operator with three rules you need:
  - `x ^ x = 0` (a number cancels itself)
  - `x ^ 0 = x`
  - Order doesn't matter: `a ^ b ^ a = b`.

## How to Think About It

Two lists:

- **Should be there:** `0, 1, 2, …, n`
- **Actually there:** `nums`

They match except for **one** number. Ask: _"How can I combine everything so the matching numbers cancel out?"_

- **Subtraction:** `(0 + 1 + … + n) − (sum of nums)`. The matching numbers cancel, the missing one is left.
- **XOR:** XOR everything in both lists. Each matching number shows up **twice**, so `x ^ x = 0` wipes it. The missing number shows up **once**, so it survives.

```
should be:  0 1 2 3
actual:     3 0 1
XOR all:    0^1^2^3 ^ 3^0^1  =  (0^0) ^ (1^1) ^ (3^3) ^ 2  =  2
```

## Approach 1: Brute Force

- **Idea:** For each `x` from `0` to `n`, scan `nums` to see if `x` is there. The first `x` not found is the answer.
- **Why it works:** We check every candidate directly.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** For each candidate we scan the whole array again. "Is `x` there?" should be an O(1) question.

## Approach 2: Better (Seen Array)

- **Idea:** Make `seen` of size `n + 1`. Mark `seen[num] = true` for each number. Return the `x` with `seen[x] == false`.
- **Why it works:** Numbers are between `0` and `n`, so each one is a valid index. One pass marks, one pass finds.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n), Space O(n)
- **Why it's not enough:** The follow-up wants O(1) extra space. We don't need to know **which** numbers are there, just **what's left over**.

(Sorting and finding the first `i` with `nums[i] != i` also works, in O(n log n).)

## Approach 3: Better (Sum Formula)

- **Idea:** `expected = n(n + 1) / 2`, `actual = sum of nums`. Return `expected - actual`.
- **Why it works:** Both sums have the same numbers, except `actual` is missing one. The difference is that number.
- **Code:** [better2.cpp](better2.cpp)
- **Complexity:** Time O(n), Space O(1)
- **Why it's not enough:** Here it's fine (`n ≤ 10⁴` → sum ≈ 5 × 10⁷, fits in `int`). But the sum grows like n². At `n = 10⁵` it's ≈ 5 × 10⁹, which **overflows `int`**. XOR never grows past the bits of `n`, so it can't overflow.

## Approach 4: Optimal (XOR)

- **Idea:**
  1. `result = n`.
  2. For each `i` from `0` to `n - 1`: `result ^= i ^ nums[i]`.
  3. Return `result`.
- **Why it works:**
  - The loop XORs every index `0 … n − 1`, and we started with `n`, so all of `0 … n` are in. That's the "should be" list.
  - The loop also XORs every value in `nums`. That's the "actual" list.
  - Every number in both lists appears twice and cancels. The missing one appears once and stays.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1)

## Dry Run (Optimal)

`nums = [3, 0, 1]`, `n = 3`

| Step  | `i` | `nums[i]` | `result ^= i ^ nums[i]` | `result`   |
| ----- | --- | --------- | ----------------------- | ---------- |
| start | —   | —         | `result = n`            | `3` (`11`) |
| 1     | 0   | 3         | `3 ^ 0 ^ 3`             | `0` (`00`) |
| 2     | 1   | 0         | `0 ^ 1 ^ 0`             | `1` (`01`) |
| 3     | 2   | 1         | `1 ^ 2 ^ 1`             | `2` (`10`) |

Answer: `2`. The `3`s, `0`s and `1`s each appeared twice and cancelled. `2` appeared only once (as index `i = 2`).

## Edge Cases

| Case             | Example        | What happens                                                  |
| ---------------- | -------------- | ------------------------------------------------------------- |
| Missing `n`      | `[0, 1]`       | `n` only enters through `result = n` → `2`                    |
| Missing `0`      | `[1, 2, 3]`    | `1`, `2`, `3` cancel; `0` only appears as an index → `0`      |
| One element, `0` | `[0]`          | `1 ^ 0 ^ 0 = 1` → `1`                                         |
| One element, `1` | `[1]`          | `1 ^ 0 ^ 1 = 0` → `0`                                         |
| Unsorted         | `[9, 6, 4, …]` | XOR doesn't care about order → `8`                            |
| Largest input    | n = 10⁴        | One pass; sum approach is ≈ 5 × 10⁷, still fits in `int` here |

## Common Mistakes

- **Forgetting `n`:** the loop only covers indexes `0 … n − 1`. Start `result` (or `expected`) with `n`, or `[0, 1]` returns `0` instead of `2`.
- **Assuming the missing number is in the middle:** it can be `0` or `n`. "Find the first gap in a sorted array" must also handle "no gap → answer is `n`".
- **Sum overflow:** `n * (n + 1) / 2` overflows `int` once `n` passes about 46,000 (`n * (n + 1)` overflows before the `/ 2`). Use `long long`, or XOR.
- **Using a `set` and calling it O(1) space:** a hash set of `n` numbers is O(n) space.

## Comparison

| Approach    | Time     | Space    | Note                                               |
| ----------- | -------- | -------- | -------------------------------------------------- |
| Brute force | O(n²)    | O(1)     | Scan the array for every candidate                 |
| Seen array  | O(n)     | O(n)     | Mark, then find the unmarked one                   |
| Sum formula | O(n)     | O(1)     | Simple, but the sum can overflow for big n         |
| XOR         | **O(n)** | **O(1)** | Pairs cancel, the missing one is left; no overflow |

## Pattern Takeaway

- **"Every number appears twice (or in two lists) except one" → XOR everything.** Pairs cancel, the odd one out is left.
- **"Numbers in range `[0, n]`" → the values can be indexes.** Use them to mark, compare, or cancel against `i`.
- **Expected vs actual:** when you know what the full set should be, compare it to what you have (by sum or XOR).

## Practice Next

| Problem                                                                                                             | Difficulty | How it relates                                        |
| ------------------------------------------------------------------------------------------------------------------- | ---------- | ----------------------------------------------------- |
| [Single Number](https://leetcode.com/problems/single-number/)                                                       | Easy       | Every number twice except one → XOR all               |
| [Find All Numbers Disappeared in an Array](https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/) | Easy       | Many missing; mark by flipping signs at `nums[x] - 1` |
| [Set Mismatch](https://leetcode.com/problems/set-mismatch/)                                                         | Easy       | One missing **and** one duplicated                    |
| [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/)                               | Medium     | The opposite: one number appears twice                |
| [First Missing Positive](https://leetcode.com/problems/first-missing-positive/)                                     | Hard       | Missing number with any values, O(1) space            |

## Interview Follow-ups

- **"Sum or XOR, which is better?"** → Both O(n) time, O(1) space. XOR can't overflow. The sum is easier to explain. Mention both.
- **"Two numbers missing?"** → XOR gives `a ^ b`. Pick any `1` bit of it (`x & -x`), split all numbers by that bit, and XOR each group to get `a` and `b`. Or use sum and sum of squares.
- **"The array is sorted?"** → Binary search for the first `i` with `nums[i] != i`. O(log n).
- **"Can you modify the input?"** → Cyclic sort: put each `x` at index `x`, then find the index where `nums[i] != i`. O(n) time, O(1) space.

## TL;DR

- Should be `0 … n`, actually `nums`. One number is missing.
- XOR all indexes, `n`, and all values: `result = n; result ^= i ^ nums[i]`.
- Pairs cancel (`x ^ x = 0`), the missing number is left.
- O(n) time, O(1) space, no overflow.
