# 002. Best Time to Buy and Sell Stock

**Difficulty:** Easy · **Tags:** array, greedy, prefix minimum

**Problem:** [LeetCode 121](https://leetcode.com/problems/best-time-to-buy-and-sell-stock/) · **Video:** [YouTube](https://youtu.be/FMtLPvhBLos)

## Problem in Simple Words

You get `prices`, where `prices[i]` is a stock's price on day `i`.
Buy **once** on one day, then sell **once** on a **later** day.
Return the biggest profit you can make. If every choice loses money, return `0` (just don't trade).

## Examples

| `prices`             | Output | Why                                                     |
| -------------------- | ------ | ------------------------------------------------------- |
| `[7, 1, 5, 3, 6, 4]` | `5`    | Buy at `1` (day 1), sell at `6` (day 4): `6 - 1 = 5`    |
| `[7, 6, 4, 3, 1]`    | `0`    | Prices only fall. Any trade loses money, so don't trade |

Note for example 1: the highest price is `7`, but it comes **before** the lowest price `1`. You can't sell before you buy, so the answer is not `7 - 1`.

## Constraints → What They Tell Us

- `1 <= prices.length <= 10^5`
- `0 <= prices[i] <= 10^4`

What this means:

- **n ≤ 10⁵:** checking every (buy, sell) pair is about 5 × 10⁹ checks. **Too slow** (time limit exceeded). We need O(n) or O(n log n).
- **`prices.length` can be 1:** with a single day there is no later day to sell on, so the answer is `0`.
- **Prices ≤ 10⁴:** any profit fits easily in `int`.
- **Answer is never negative:** "not trading" is always an option, so start the answer at `0`.

## Prerequisites

- **Arrays and loops:** reading `prices[i]` left to right.
- **Prefix minimum:** the smallest value seen from the start up to index `i`. Built in one pass with `minUpTo[i] = min(minUpTo[i - 1], prices[i])`.

## How to Think About It

Flip the question. Instead of _"when should I buy?"_, ask:

> _"If I sell **today**, what's the best day I could have bought?"_

The answer: the **cheapest day before today**.

So for every day, profit today = `today's price - cheapest price so far`.
The answer is the biggest of these.

We don't care _which_ day was cheapest, only _how cheap_ it was. So one number, `minPrice`, is enough to remember.

## Approach 1: Brute Force

- **Idea:** Try every buy day `i` and every later sell day `j`. Keep the biggest `prices[j] - prices[i]`.
- **Why it works:** It checks every legal trade, so it can't miss the best one.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** For each sell day `j`, the inner loop scans **all earlier days** to find the cheapest one. But the cheapest earlier day for day `j` is almost the same as for day `j - 1`: just one more day to compare. We keep redoing the same work.

## Approach 2: Better (Prefix Minimum Array)

- **Idea:**
  1. Build `minUpTo[i]` = cheapest price from day `0` to day `i`.
  2. For every day `i`, profit = `prices[i] - minUpTo[i]`. Keep the biggest.
- **Why it works:** `minUpTo[i]` is exactly the best buy price for selling on day `i`. (Including day `i` itself just gives profit `0`, which is allowed.)
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n), Space O(n) for `minUpTo`
- **Why it's not enough:** On day `i` we only ever read `minUpTo[i]`, never older entries. Storing the whole array is wasted memory. One variable can hold "cheapest so far".

## Approach 3: Optimal (One Pass, Track the Minimum)

- **Idea:** Walk the prices once, keeping `minPrice` (cheapest price so far) and `best` (best profit so far). For each `price`:
  1. `minPrice = min(minPrice, price)`
  2. `best = max(best, price - minPrice)`
- **Why it works:** Same logic as approach 2, but `minPrice` replaces the array, since we only ever need its latest value.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1)

## Dry Run (Optimal)

`prices = [7, 1, 5, 3, 6, 4]`

| Day | `price` | `minPrice` after update | `price - minPrice` | `best` |
| --- | ------- | ----------------------- | ------------------ | ------ |
| 0   | 7       | 7                       | 0                  | 0      |
| 1   | 1       | **1**                   | 0                  | 0      |
| 2   | 5       | 1                       | 4                  | 4      |
| 3   | 3       | 1                       | 2                  | 4      |
| 4   | 6       | 1                       | **5**              | **5**  |
| 5   | 4       | 1                       | 3                  | 5      |

Answer: `5` (buy at `1` on day 1, sell at `6` on day 4).

## Edge Cases

| Case                         | Example           | What happens                                                         |
| ---------------------------- | ----------------- | -------------------------------------------------------------------- |
| Only one day                 | `[5]`             | No second day to sell on → `0`                                       |
| Prices only fall             | `[7, 6, 4, 3, 1]` | Every `price - minPrice` is `0` → `0`                                |
| All prices equal             | `[3, 3, 3]`       | No profit possible → `0`                                             |
| Prices only rise             | `[1, 2, 3, 4, 5]` | Buy first day, sell last day → `4`                                   |
| Lowest price is the last day | `[2, 4, 1]`       | Can't sell after day 2. Best is `4 - 2 = 2`, not anything with `1`   |
| Best trade skips the lowest  | `[3, 8, 1, 4]`    | `8 - 3 = 5` beats `4 - 1 = 3`, even though `1` is the cheapest price |
| Price can be zero            | `[0, 10000]`      | `10000 - 0 = 10000`                                                  |

## Common Mistakes

- **Answer = max price − min price:** ignores order. In `[7, 1, 5, 3, 6, 4]` that gives `6`, but `7` comes before `1`.
- **Always buying at the global minimum:** in `[3, 8, 1, 4]` the cheapest day is `1`, but the best trade is `3 → 8`.
- **Starting `best` at `INT_MIN` or `-1`:** the problem says return `0` when no profit is possible.
- **Starting `minPrice` at `0`:** then `price - minPrice` is just `price`, which is wrong. Start at `INT_MAX` or `prices[0]`.
- **Brute force inner loop from `j = 0`:** that "sells" before buying. Start at `j = i + 1`.

## Comparison

| Approach              | Time     | Space    | Note                                   |
| --------------------- | -------- | -------- | -------------------------------------- |
| Brute force           | O(n²)    | O(1)     | Times out for n = 10⁵                  |
| Prefix minimum array  | O(n)     | O(n)     | Fast, but stores values we never reuse |
| One pass + `minPrice` | **O(n)** | **O(1)** | Best                                   |

## Pattern Takeaway

- **"Best pair `(i, j)` with `i < j`" → fix `j`, and keep the best `i` seen so far in a variable.** This turns O(n²) into O(n). Two Sum (#001) used the same trick with a hash map.
- **Prefix min/max:** if each step only needs "the min/max so far", one variable replaces the whole array.
- **Same problem, different view:** buy-and-sell profit = sum of daily price changes in between. So this is **Maximum Subarray** (Kadane's algorithm) on the array of daily differences.

## Practice Next

| Problem                                                                                                                         | Difficulty | How it relates                                                   |
| ------------------------------------------------------------------------------------------------------------------------------- | ---------- | ---------------------------------------------------------------- |
| [Maximum Difference Between Increasing Elements](https://leetcode.com/problems/maximum-difference-between-increasing-elements/) | Easy       | Same problem, returns `-1` instead of `0` when there's no profit |
| [Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)                                                             | Medium     | Kadane's algorithm: the same idea on daily differences           |
| [Best Time to Buy and Sell Stock II](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/)                         | Medium     | Unlimited trades: add up every price rise                        |
| [Best Time to Buy and Sell Stock with Cooldown](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)   | Medium     | Adds a rest day after selling: needs DP with states              |
| [Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)                       | Hard       | At most 2 trades: DP, or prefix + suffix best profits            |

## Interview Follow-ups

- **"Return the buy and sell days too."** → Also store the index of `minPrice`, and save both indices whenever `best` improves.
- **"You must make exactly one trade, even at a loss."** → Start `best` at a very small number, and compute `price - minPrice` **before** updating `minPrice` (so you never buy and sell on the same day).
- **"Unlimited trades."** → Add every positive `prices[i] - prices[i - 1]` (Stock II).
- **"At most `k` trades" / "fee per trade" / "cooldown day."** → Dynamic programming with "holding" and "not holding" states (Stock IV, Stock with Fee, Stock with Cooldown).

## TL;DR

- Sell today → the best buy is the cheapest day **before** today.
- Keep `minPrice` (cheapest so far) and `best` (best profit so far).
- Each day: `minPrice = min(minPrice, price)`, `best = max(best, price - minPrice)`.
- O(n) time, O(1) space. Never return a negative answer: start `best` at `0`.
