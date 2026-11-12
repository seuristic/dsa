# 011. Sum of Two Integers

**Difficulty:** Medium · **Tags:** bit manipulation, math

**Problem:** [LeetCode 371](https://leetcode.com/problems/sum-of-two-integers/) · **Video:** [YouTube](https://youtu.be/UMwUtTqa7WI)

## Problem in Simple Words

You get two integers `a` and `b`.
Return `a + b`, but you are **not allowed** to use the `+` or `-` operators.
The numbers can be **negative**.

## Examples

| `a` | `b`  | Output | Why                            |
| --- | ---- | ------ | ------------------------------ |
| `1` | `2`  | `3`    | `01 + 10 = 11` in binary       |
| `2` | `3`  | `5`    | `010 + 011 = 101` in binary    |
| `5` | `3`  | `8`    | Carries ripple across 3 bits   |
| `5` | `-3` | `2`    | Negative numbers work the same |

## Constraints → What They Tell Us

- `-1000 <= a, b <= 1000`

What this means:

- **Negatives are allowed:** the solution must work with how computers store negative numbers (two's complement).
- **The sum fits in `int`:** at most `2000` in size. No overflow to worry about.
- **Speed isn't the challenge:** any O(32) method is instant. The challenge is doing it **with bits only**.

## Prerequisites

- **Binary:** `5 = 101`, `3 = 011`. Each position is a bit, worth 1, 2, 4, 8, …
- **Bitwise operators**, applied to every bit at once:
  - `a & b` (AND): `1` only where **both** bits are `1`.
  - `a ^ b` (XOR): `1` where the bits are **different**.
  - `a | b` (OR): `1` where **at least one** bit is `1`.
  - `x << 1` (shift left): moves every bit one place left, which is the same as `× 2`.
- **Two's complement:** how negative numbers are stored. `-1` is all ones (`111…1`). `-x` is `~x` plus 1. The good news: adding bits works **the same** for negative and positive numbers.

## How to Think About It

Ask: _"How did I learn to add on paper?"_ Column by column, right to left, with a **carry**.

In binary each column has only `0` or `1`. So there are just four cases:

| Bit of `a` | Bit of `b` | Sum bit | Carry |
| ---------- | ---------- | ------- | ----- |
| 0          | 0          | 0       | 0     |
| 0          | 1          | 1       | 0     |
| 1          | 0          | 1       | 0     |
| 1          | 1          | 0       | **1** |

Look at the columns:

- **Sum bit = `a ^ b`** (1 when the bits are different).
- **Carry = `a & b`** (1 only when both are 1). The carry goes to the **next column**, so shift it: `(a & b) << 1`.

Now do it for **all 32 bits at once**:

```
a + b  =  (a ^ b)  +  ((a & b) << 1)
          sum without    the carries, moved
          the carries    one column left
```

The right side is still an addition. But it's the **same problem again** with new numbers. Repeat until there's no carry left. Then the answer is just the XOR part.

## Approach 1: Brute Force (Bit by Bit)

- **Idea:** Do school addition, one bit at a time, for all 32 bits:
  1. Take bit `i` of `a` and of `b`.
  2. Sum bit = `bitA ^ bitB ^ carry`. Put it at position `i` of the result.
  3. New carry = `1` if at least two of `bitA`, `bitB`, `carry` are `1`.
- **Why it works:** It is exactly how a hardware adder works: one column at a time, passing the carry left. Bit 31 (the sign bit) is handled like any other, so negatives just work.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(32) = O(1), Space O(1)
- **Why it's not enough:** It works on **one bit per step** and always does all 32 steps. It also needs a 3-way formula for the carry. The bitwise operators already work on **all 32 bits at once**, so let's use that.

## Approach 2: Optimal (XOR + Carry)

- **Idea:**
  1. While `b != 0` (there are still carries to add):
     - `carry = (a & b) << 1`
     - `a = a ^ b`
     - `b = carry`
  2. Return `a`.
- **Why it works:**
  - `a + b = (a ^ b) + ((a & b) << 1)` is always true, so each round keeps the total the same.
  - Each round, the carry moves **at least one bit to the left**. After at most 32 rounds it falls off the end and becomes `0`.
  - When `b` is `0`, there's nothing left to add, so `a` is the answer.
- **The `unsigned` cast:** in C++ (before C++20), shifting a **negative** `int` left is undefined behavior. `a & b` can be negative, so we cast it to `unsigned` before `<< 1`.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(32) = O(1) (stops as soon as there are no carries), Space O(1)

## Dry Run (Optimal)

`a = 5`, `b = 3` (showing 4 bits)

| Round | `a`        | `b`        | `carry = (a & b) << 1` | `a ^ b`    |
| ----- | ---------- | ---------- | ---------------------- | ---------- |
| 1     | `0101` (5) | `0011` (3) | `0010` (2)             | `0110` (6) |
| 2     | `0110` (6) | `0010` (2) | `0100` (4)             | `0100` (4) |
| 3     | `0100` (4) | `0100` (4) | `1000` (8)             | `0000` (0) |
| 4     | `0000` (0) | `1000` (8) | `0000` (0)             | `1000` (8) |
| end   | `1000` (8) | `0000` (0) | `b == 0` → stop        |            |

Answer: `8`. Notice the total `a + b` stays `8` in every row. The carry just moves left until it lands.

## Edge Cases

| Case               | Example         | What happens                                                            |
| ------------------ | --------------- | ----------------------------------------------------------------------- |
| No carries at all  | `1 + 2`         | `a & b = 0` → one round, answer is `a ^ b = 3`                          |
| One number is zero | `0 + -7`        | `b` becomes `0` after one round → `-7`                                  |
| Both zero          | `0 + 0`         | Loop never runs → `0`                                                   |
| Result is zero     | `-1 + 1`        | Carry walks all the way to bit 31 and falls off → 32 rounds, answer `0` |
| Both negative      | `-2 + -3`       | Two's complement handles it → `-5`                                      |
| Mixed signs        | `5 + -3`        | Same bit rules → `2`                                                    |
| Negative `a & b`   | `-1000 + -1000` | `a & b` is negative; the `unsigned` cast makes `<< 1` safe → `-2000`    |

## Common Mistakes

- **Forgetting `<< 1` on the carry:** the carry belongs to the **next** column, not the same one.
- **Updating `a` before computing the carry:** `a = a ^ b` first, then `a & b`, uses the wrong `a`. Compute the carry from the old values first.
- **Stopping after one round:** adding the carry can create **new** carries (`5 + 3` needs 4 rounds). Loop until `b == 0`.
- **Shifting a negative `int` left:** undefined behavior in C++ before C++20. Cast to `unsigned` first.
- **Counting with `a++` / `a--` in a loop:** it avoids the `+` symbol, but it's O(|b|) and misses the point. Interviewers won't accept it.
- **Python:** integers have no fixed size, so negative carries never fall off and the loop runs forever. Mask with `0xFFFFFFFF` and convert back at the end.

## Comparison

| Approach    | Time                  | Space | Note                                         |
| ----------- | --------------------- | ----- | -------------------------------------------- |
| Bit by bit  | O(32)                 | O(1)  | One column per step, always 32 steps         |
| XOR + carry | **O(32)**, often less | O(1)  | All columns at once; stops when carry is `0` |

## Pattern Takeaway

- **"No `+`" / "no arithmetic" → think bits.** XOR is addition without carry. AND finds where the carries are.
- **`a + b = (a ^ b) + ((a & b) << 1)`.** Remember this identity; it shows up in other bit problems.
- **"Same problem with smaller input" → loop or recurse.** Here, each round the carry part moves left, until it's gone.
- **Fixed-width numbers (32 bits) make bit loops O(1).**

## Practice Next

| Problem                                                                   | Difficulty | How it relates                                      |
| ------------------------------------------------------------------------- | ---------- | --------------------------------------------------- |
| [Add Binary](https://leetcode.com/problems/add-binary/)                   | Easy       | The same school addition with carry, on strings     |
| [Single Number](https://leetcode.com/problems/single-number/)             | Easy       | XOR cancels equal numbers: `x ^ x = 0`              |
| [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/)       | Easy       | Read bits one by one, next in Blind 75              |
| [Missing Number](https://leetcode.com/problems/missing-number/)           | Easy       | XOR all indexes and values; the leftover is missing |
| [Divide Two Integers](https://leetcode.com/problems/divide-two-integers/) | Medium     | Arithmetic without `*`, `/`, `%`, using shifts      |

## Interview Follow-ups

- **"Subtract without `-`?"** → `a - b = a + (-b)`, and `-b = ~b + 1`. So `getSum(a, getSum(~b, 1))`.
- **"Write it recursively."** → `getSum(a, b) = b == 0 ? a : getSum(a ^ b, (a & b) << 1)`.
- **"How many rounds at most?"** → 32. The carry moves at least one bit left each round. `-1 + 1` hits the worst case.
- **"Multiply without `*`?"** → Shift and add: for each `1` bit of `b` at position `i`, add `a << i` (using this `getSum`).
- **"Python version?"** → Keep everything inside 32 bits with `& 0xFFFFFFFF`. At the end, if bit 31 is set, convert back to negative with `~(a ^ 0xFFFFFFFF)`.

## TL;DR

- XOR = sum without carry. AND = where carries happen. Shift the carry left by 1.
- Loop: `carry = (a & b) << 1; a = a ^ b; b = carry;` until `b == 0`.
- Cast to `unsigned` before shifting so negatives are safe in C++.
- O(1) time (at most 32 rounds), O(1) space.
