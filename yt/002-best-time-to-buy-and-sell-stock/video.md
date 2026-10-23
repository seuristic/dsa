# Video: Best Time to Buy and Sell Stock

## Title Options

1. Best Time to Buy and Sell Stock — O(n²) to O(n) | LeetCode 121 in C++
2. Buy Low, Sell High: One Variable Solves It | Blind 75 #2
3. LeetCode 121 Explained — Brute Force, Prefix Min & One Pass (C++)

## Hook (first 30 sec)

> "Buy low, sell high. Easy, right? Just take the highest price minus the lowest price.
> Except that's wrong: in `[7, 1, 5, 3, 6, 4]` the highest price comes _before_ the lowest, and you can't sell before you buy.
> In this video, one small change in the question you ask takes this from O(n²) to O(n) with a single variable."

## Recording Flow

### 1. Problem (≈1 min)

- Read it in simple words. Stress: **one buy, one sell, sell must be later**, return `0` if no profit.
- Whiteboard: plot `[7, 1, 5, 3, 6, 4]` as a line chart (day on x-axis, price on y-axis). Mark the buy at `1` and the sell at `6`.
- Show example 2 (`[7, 6, 4, 3, 1]`): a falling line, answer `0`.

### 2. The Trap (≈1 min)

- "Max minus min" → `7 - 1 = 6`. Point at the chart: `7` is on the left of `1`. Wrong.
- "Always buy at the lowest" → `[3, 8, 1, 4]`: lowest is `1`, but `3 → 8` wins.

### 3. Constraints (≈1 min)

- n ≤ 10⁵ → O(n²) ≈ 5 × 10⁹: times out. We need O(n).
- Prices ≤ 10⁴: `int` is fine. Answer never negative.

### 4. Brute Force (≈2 min)

- Whiteboard: an arrow for buy day `i`, an arrow for sell day `j` scanning all later days.
- Show [brute.cpp](brute.cpp), run it.
- Bottleneck: "for each sell day, we rescan every earlier day just to find the cheapest one."

### 5. Key Insight (≈1 min)

- Flip the question: "If I sell **today**, what's the best day I could have bought?" → the cheapest day before today.
- Write on the board: `profit today = price - cheapest so far`.

### 6. Better: Prefix Minimum Array (≈2 min)

- Whiteboard: write `prices` and `minUpTo` as two rows, fill `minUpTo` left to right.
- Show [better1.cpp](better1.cpp), run it.
- Why move on: "on day `i`, we only read `minUpTo[i]`. Do we need the whole array?"

### 7. Optimal: One Pass (≈3 min)

- Replace the array with one variable, `minPrice`.
- Do the dry run on `[7, 1, 5, 3, 6, 4]` (README table), filling `minPrice` and `best` live.
- Show [optimal.cpp](optimal.cpp), run it.

### 8. Edge Cases + Common Mistakes (≈1 min)

- One day, falling prices, lowest price on the last day `[2, 4, 1]`.
- Mistakes: max − min, `minPrice` starting at `0`, `best` starting negative.

### 9. Comparison + Pattern (≈1 min)

- Show the comparison table.
- Pattern: "best pair `i < j` → fix `j`, remember the best `i` so far." Callback to Two Sum.
- Bonus: this is Maximum Subarray (Kadane) on daily price changes.

### 10. Follow-ups + Practice (≈1 min)

- Return the days, exactly one trade, unlimited trades (Stock II). Next video teaser.

## YouTube Description

Best Time to Buy and Sell Stock (LeetCode 121) explained step by step in C++: brute force O(n²) → prefix minimum O(n) → one pass with O(1) space. Learn why "max minus min" fails, and the "fix the right end, remember the best left end" trick.

00:00 Intro
00:00 Problem explained
00:00 The max − min trap
00:00 Constraints
00:00 Brute force — O(n²)
00:00 Key insight
00:00 Prefix minimum — O(n), O(n) space
00:00 One pass — O(n), O(1) space
00:00 Dry run
00:00 Edge cases & mistakes
00:00 Pattern takeaway
00:00 Follow-ups & practice

Problem: https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
Notes + code: https://github.com/seuristic/dsa/tree/main/yt/002-best-time-to-buy-and-sell-stock

## Tags

best time to buy and sell stock, leetcode 121, buy and sell stock c++, stock problem leetcode, prefix minimum, greedy, kadane, blind 75, leetcode easy, dsa for beginners, coding interview, data structures and algorithms

## Thumbnail Text

Buy Low, Sell High
