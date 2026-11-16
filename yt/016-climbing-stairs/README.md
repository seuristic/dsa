# 016. Climbing Stairs

**Difficulty:** Easy · **Tags:** dynamic programming, math, memoization

**Problem:** [LeetCode 70](https://leetcode.com/problems/climbing-stairs/) · **Video:** TODO

## Problem in Simple Words

There's a staircase with `n` steps.
Each move, you climb **1 step or 2 steps**.
Return how many **different ways** there are to reach the top.

## Examples

| `n` | Output | Ways                                        |
| --- | ------ | ------------------------------------------- |
| `2` | `2`    | `1+1`, `2`                                  |
| `3` | `3`    | `1+1+1`, `1+2`, `2+1`                       |
| `4` | `5`    | `1+1+1+1`, `1+1+2`, `1+2+1`, `2+1+1`, `2+2` |

Order matters: `1+2` and `2+1` are different ways.

## Constraints → What They Tell Us

- `1 <= n <= 45`

What this means:

- **n ≤ 45:** small, but trying every path grows exponentially: about 10⁹ calls at `n = 45`. **Too slow.** We need O(n).
- **The answer for n = 45 is 1,836,311,903:** that fits in `int` (max ≈ 2.1 × 10⁹), barely. At `n = 46` it wouldn't.

## Prerequisites

- **Recursion:** a function that calls itself on a smaller input, with a base case to stop.
- **Fibonacci numbers:** `1, 1, 2, 3, 5, 8, 13, …`, each is the sum of the two before it.
- **Dynamic programming (DP):** solve each smaller problem **once**, save the answer, and reuse it.

## How to Think About It

Don't think about the whole climb. Think about the **last move**.

Ask: _"How did I get to step `n`?"_

- Either my last move was **1 step**, from step `n − 1`,
- or my last move was **2 steps**, from step `n − 2`.

Those two groups don't overlap, and together they cover every way. So:

```
ways(n) = ways(n − 1) + ways(n − 2)
ways(1) = 1        (1)
ways(2) = 2        (1+1, 2)
```

That's the **Fibonacci** rule: `1, 2, 3, 5, 8, 13, …`

Now the question is just: how to compute it fast.

## Approach 1: Brute Force (Plain Recursion)

- **Idea:** Write the formula as code: `climbStairs(n) = climbStairs(n − 1) + climbStairs(n − 2)`, with `n ≤ 2` returning `n`.
- **Why it works:** It's exactly the "last move" rule.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(2ⁿ) (each call makes two more), Space O(n) for the recursion stack
- **Why it's not enough:** It solves the **same** subproblems again and again:

  ```
                   f(5)
              /           \
          f(4)            [f(3)]
         /    \           /    \
    [f(3)]   f(2)     f(2)    f(1)
    /    \
  f(2)   f(1)
  ```

  `f(3)` (in brackets) is computed twice, `f(2)` three times. At `n = 45` that's about 10⁹ calls. There are only `n` different subproblems, so let's solve each one **once**.

## Approach 2: Better (Memoization, Top-Down)

- **Idea:** Same recursion, plus a `memo` array. Before computing `ways(n)`, check `memo[n]`. After computing it, save it.
- **Why it works:** Each `ways(i)` is computed once. Every later call returns the saved value right away.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n), Space O(n) (memo + recursion stack)
- **Why it's not enough:** It still uses recursion: `n` stack frames deep, plus the function-call overhead. We know the order we need (1, 2, 3, …), so we can just loop.

## Approach 3: Better (Tabulation, Bottom-Up)

- **Idea:** Fill an array `dp` from small to big: `dp[1] = 1`, `dp[2] = 2`, `dp[i] = dp[i − 1] + dp[i − 2]`. Return `dp[n]`.
- **Why it works:** When we reach `i`, `dp[i − 1]` and `dp[i − 2]` are already filled.
- **Code:** [better2.cpp](better2.cpp)
- **Complexity:** Time O(n), Space O(n) for the array
- **Why it's not enough:** To compute `dp[i]` we only look at the **last two** values. Everything older is never used again. We don't need the whole array.

## Approach 4: Optimal (Two Variables)

- **Idea:**
  1. `prev = 1` (ways to step 1), `curr = 2` (ways to step 2).
  2. For `i` from `3` to `n`: `next = prev + curr`, then slide: `prev = curr`, `curr = next`.
  3. Return `curr`.
- **Why it works:** Same as the table, but we keep only the two values we need.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1)

## Dry Run (Optimal)

`n = 5`

| `i`   | `next = prev + curr` | `prev` | `curr` |
| ----- | -------------------- | ------ | ------ |
| start | —                    | 1      | 2      |
| 3     | 1 + 2 = 3            | 2      | 3      |
| 4     | 2 + 3 = 5            | 3      | 5      |
| 5     | 3 + 5 = 8            | 5      | **8**  |

Answer: `8`.

## Edge Cases

| Case          | Example  | What happens                                            |
| ------------- | -------- | ------------------------------------------------------- |
| One step      | `n = 1`  | Base case → `1`                                         |
| Two steps     | `n = 2`  | Base case → `2`                                         |
| Largest input | `n = 45` | Loop runs 43 times → `1836311903`, just fits in `int`   |
| Brute at 45   | `n = 45` | About 10⁹ calls → too slow (that's why it's not enough) |

## Common Mistakes

- **Wrong base cases:** `ways(1) = 1`, `ways(2) = 2`. Using `ways(2) = 1` gives Fibonacci shifted by one and every answer is off.
- **Accessing `dp[2]` when `n = 1`:** an array of size `n + 1 = 2` has no index `2`. Return early for `n ≤ 2`.
- **Forgetting to save in the memo:** checking `memo[n]` but never writing it is still O(2ⁿ).
- **Updating in the wrong order:** `prev = curr; curr = prev + curr;` uses the **new** `prev`. Compute `next` first, then slide.
- **Counting combinations instead of orders:** `1+2` and `2+1` are different ways here.

## Comparison

| Approach        | Time     | Space    | Note                                     |
| --------------- | -------- | -------- | ---------------------------------------- |
| Plain recursion | O(2ⁿ)    | O(n)     | Recomputes the same subproblems          |
| Memoization     | O(n)     | O(n)     | Recursion + save each answer             |
| Tabulation      | O(n)     | O(n)     | Loop from small to big, fill an array    |
| Two variables   | **O(n)** | **O(1)** | Only the last two values are ever needed |

## Pattern Takeaway

- **"How many ways to reach the end?" → think about the last move.** `ways(n)` = sum of `ways` of every place you could have come from.
- **Recursion with repeated subproblems → memoize.** Then turn it into a loop, then keep only what you need.
- **This is the DP recipe for every problem after this one:** recursion → memo → table → space-optimized.
- **If `dp[i]` only depends on the last k values, keep k variables.**

## Practice Next

| Problem                                                                             | Difficulty | How it relates                                       |
| ----------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------- |
| [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)                 | Easy       | The same recurrence with different starting values   |
| [N-th Tribonacci Number](https://leetcode.com/problems/n-th-tribonacci-number/)     | Easy       | Sum of the last **three**: keep three variables      |
| [Min Cost Climbing Stairs](https://leetcode.com/problems/min-cost-climbing-stairs/) | Easy       | Same stairs, but minimize cost instead of counting   |
| [House Robber](https://leetcode.com/problems/house-robber/)                         | Medium     | `dp[i]` from `dp[i − 1]` and `dp[i − 2]`, with a max |
| [Coin Change](https://leetcode.com/problems/coin-change/)                           | Medium     | Steps of any coin size, next in Blind 75             |

## Interview Follow-ups

- **"Steps of 1, 2, or 3?"** → `ways(n) = ways(n − 1) + ways(n − 2) + ways(n − 3)`. Keep three variables.
- **"Any set of step sizes?"** → `ways(n) = sum of ways(n − s)` for each allowed step `s`. O(n × number of step sizes).
- **"n up to 10⁹, answer mod 10⁹ + 7?"** → Matrix exponentiation on `[[1, 1], [1, 0]]`: O(log n).
- **"Some steps are broken?"** → Set `ways` of a broken step to `0`.
- **"Is there a formula?"** → Yes, Binet's formula with the golden ratio. But floating-point errors make it unreliable for big `n`.

## TL;DR

- Last move was 1 step or 2 steps → `ways(n) = ways(n − 1) + ways(n − 2)`.
- It's Fibonacci: `1, 2, 3, 5, 8, …`
- Recursion → memo → table → two variables.
- O(n) time, O(1) space.
