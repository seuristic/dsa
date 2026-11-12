# 012. Number of 1 Bits

**Difficulty:** Easy · **Tags:** bit manipulation

**Problem:** [LeetCode 191](https://leetcode.com/problems/number-of-1-bits/) · **Video:** [YouTube](https://youtu.be/DS9rur5uG-A)

## Problem in Simple Words

You get a positive integer `n`.
Write it in binary and count how many `1`s it has.
(This count is also called the **Hamming weight** or **popcount**.)

## Examples

| `n`          | Binary                            | Output | Why                    |
| ------------ | --------------------------------- | ------ | ---------------------- |
| `11`         | `1011`                            | `3`    | Three `1`s             |
| `128`        | `10000000`                        | `1`    | A power of 2 has one 1 |
| `2147483645` | `1111111111111111111111111111101` | `30`   | 31 bits, one of them 0 |

## Constraints → What They Tell Us

- `1 <= n <= 2^31 - 1`

What this means:

- **n is positive:** it fits in 31 bits, and the sign bit is always `0`. Shifting right never runs forever.
- **At most 31 bits:** any method that looks at each bit is at most 31 steps. Already O(1).
- **So the question is:** can we skip the `0` bits and only spend a step on each `1`?

## Prerequisites

- **Binary:** `11 = 1011` = 8 + 2 + 1.
- **`n & 1`:** the last bit of `n` (`1` if odd, `0` if even).
- **`n >>= 1`:** shift right, drops the last bit. Same as `n / 2` for positive numbers.
- **`a & b`:** keeps a bit only where both numbers have a `1`.

## How to Think About It

The simple way: look at the last bit, count it, drop it, repeat. That's one step per bit, `1` or `0`.

Then ask: _"Can I jump straight from one `1` to the next?"_

Look at what `n - 1` does in binary:

```
n      = 1011000
n - 1  = 1010111
          └┬─┘
     the lowest 1 becomes 0, the 0s after it become 1s
```

Everything **left** of the lowest `1` stays the same. So `n & (n - 1)` keeps the left part and wipes the rest:

```
n            = 1011000
n - 1        = 1010111
n & (n - 1)  = 1010000   ← the lowest 1 is gone
```

Each `n &= n - 1` removes exactly one `1`. Count how many times you can do it before `n` hits `0`.

## Approach 1: Brute Force (Check Every Bit)

- **Idea:** While `n > 0`: add `n & 1` to the count, then `n >>= 1`.
- **Why it works:** Every bit becomes the last bit once, so every `1` is counted exactly once.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(log n) (number of bits, at most 31), Space O(1)
- **Why it's not enough:** It spends a step on every bit, even the `0`s. `128 = 10000000` takes 8 steps to find one `1`. We want one step **per `1`**.

## Approach 2: Optimal (n & (n − 1))

- **Idea:** While `n > 0`: `n &= n - 1`, `count++`.
- **Why it works:** `n - 1` flips the lowest `1` to `0` and the `0`s below it to `1`. AND with `n` clears all of them. So each step removes exactly the lowest `1`, and the loop runs once per `1`.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(k), where k = number of `1` bits (at most 31), Space O(1)

This is often called **Brian Kernighan's trick**.

## Dry Run (Optimal)

`n = 11`

| Step | `n`         | `n - 1`     | `n & (n - 1)` | `count` |
| ---- | ----------- | ----------- | ------------- | ------- |
| 1    | `1011` (11) | `1010` (10) | `1010` (10)   | 1       |
| 2    | `1010` (10) | `1001` (9)  | `1000` (8)    | 2       |
| 3    | `1000` (8)  | `0111` (7)  | `0000` (0)    | 3       |
| end  | `0`         |             |               | **3**   |

3 steps for 3 ones. The brute force would take 4 steps (one per bit).

## Edge Cases

| Case             | Example      | What happens                                       |
| ---------------- | ------------ | -------------------------------------------------- |
| Smallest input   | `1`          | One step → `1`                                     |
| Power of 2       | `128`        | Optimal: 1 step. Brute: 8 steps → `1`              |
| All ones         | `2^31 - 1`   | Both take 31 steps → `31`                          |
| Alternating bits | `1431655765` | `0101…01`: optimal 16 steps, brute 31 steps → `16` |
| Highest bit only | `2^30`       | Optimal: 1 step. Brute: 31 steps → `1`             |

## Common Mistakes

- **`n & 1 == 1` without brackets:** `==` binds tighter than `&`, so it means `n & (1 == 1)`. Write `(n & 1) == 1`, or just add `n & 1`.
- **Negative numbers with `>>`:** shifting a negative `int` right copies the sign bit, so `n` never reaches `0`. Not a problem here (`n` is positive), but use `unsigned` if negatives are possible.
- **Confusing `n & (n - 1)` with `n & 1`:** `n & 1` reads the **last** bit. `n & (n - 1)` removes the **lowest `1`**, wherever it is.
- **Converting to a string:** `bitset<32>(n).to_string()` and counting `'1'` works, but it builds a string for no reason.

## Comparison

| Approach    | Time                     | Space | Note                                 |
| ----------- | ------------------------ | ----- | ------------------------------------ |
| Check bits  | O(number of bits) ≤ 31   | O(1)  | One step per bit, `0` or `1`         |
| n & (n − 1) | **O(number of 1s)** ≤ 31 | O(1)  | One step per `1`; skips all the `0`s |

## Pattern Takeaway

- **`n & (n - 1)` removes the lowest set bit.** Remember it; it's one of the most used bit tricks.
- **`n & (n - 1) == 0` → n is a power of 2** (it has exactly one `1`).
- **`n & 1` reads the last bit, `n >> 1` drops it.** Together they walk through every bit.
- **"Count / check bits" → think of loops that remove one bit per step.**

## Practice Next

| Problem                                                                                                         | Difficulty | How it relates                                          |
| --------------------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------------- |
| [Power of Two](https://leetcode.com/problems/power-of-two/)                                                     | Easy       | One `n & (n - 1)` check                                 |
| [Hamming Distance](https://leetcode.com/problems/hamming-distance/)                                             | Easy       | Count the 1s in `x ^ y`                                 |
| [Counting Bits](https://leetcode.com/problems/counting-bits/)                                                   | Easy       | Popcount for every number from 0 to n, next in Blind 75 |
| [Reverse Bits](https://leetcode.com/problems/reverse-bits/)                                                     | Easy       | Same `& 1` and `>> 1` walk, building a new number       |
| [Sum of Two Integers](https://leetcode.com/problems/sum-of-two-integers/) ([#011](../011-sum-of-two-integers/)) | Medium     | More bit operators: XOR, AND, shifts                    |

## Interview Follow-ups

- **"Called many times, how to speed it up?"** →
  - Precompute a table `bits[0..255]` for every byte. Then the answer is 4 table lookups, one per byte of `n`.
  - Or use the built-in: `__builtin_popcount(n)` in GCC/Clang, `std::popcount` in C++20. Most CPUs do it in one instruction.
- **"What if n can be negative?"** → Cast to `unsigned` first. Then `>>` fills with `0`s and both loops end. A negative number has 32 bits to look at.
- **"Is a number a power of 2?"** → `n > 0 && (n & (n - 1)) == 0`.
- **"Get the lowest set bit itself?"** → `n & -n` (for `12 = 1100` it gives `0100`).

## TL;DR

- `n & (n - 1)` removes the lowest `1` bit.
- Loop: `n &= n - 1; count++;` until `n == 0`.
- One step per `1` bit, not per bit.
- O(k) time (k = number of 1s), O(1) space.
