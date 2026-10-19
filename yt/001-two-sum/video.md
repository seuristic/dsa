# Video: Two Sum

## Title Options

1. Two Sum — From O(n²) to O(n) | LeetCode 1 Explained in C++
2. Two Sum: The Hash Map Trick Every Beginner Must Know | Blind 75 #1
3. LeetCode Two Sum — Brute Force, Two Pointers & Hash Map (C++)

## Hook (first 30 sec)

> "Two Sum is problem #1 on LeetCode and one of the most common warm-up questions in coding interviews.
> Most beginners solve it in O(n²) and stop there. In this video, we'll go from O(n²) to O(n) with one simple question:
> _'What number do I need right now?'_ That same question solves dozens of other problems too."

## Recording Flow

### 1. Problem (≈1 min)

- Read the problem in simple words. Stress: **return indices**, **can't reuse the same element**, **exactly one answer**.
- Whiteboard: draw `[2, 7, 11, 15]` with indices below, circle `2` and `7`.
- Show example 2 (`[3, 2, 4]`, `6`) and point out why `[0, 0]` is wrong.

### 2. Constraints (≈1 min)

- n ≤ 10⁴ → O(n²) ≈ 5 × 10⁷: passes, but the follow-up wants better.
- Negatives allowed. Sum fits in `int` (±2 × 10⁹ < 2.147 × 10⁹).

### 3. Brute Force (≈2 min)

- Whiteboard: an arrow from `i` and an arrow from `j` scanning everything after `i`.
- Show [brute.cpp](brute.cpp), run it live.
- Bottleneck: "for every number we **search** for its partner. Can the search be instant?"

### 4. Better: Sort + Two Pointers (≈3 min)

- Whiteboard: the sorted `(value, index)` pairs, with `l` at the left and `r` at the right.
- Explain why moving a pointer never skips the answer (too small → `l++`, too big → `r--`).
- Show [better.cpp](better.cpp), run it.
- Why move on: sorting costs O(n log n), and we already use O(n) space.

### 5. Key Insight (≈1 min)

- "Standing at `x`, I need `target - x`." Write `need = target - x` big on the board.
- "Have I seen it?" → hash map.

### 6. Optimal: Hash Map (≈3 min)

- Whiteboard: an array on top and a map box below. Fill the map step by step.
- Do the dry run on `[3, 2, 4]`, `6` (README table).
- Stress the **check before insert** order, using the `3 + 3` trap.
- Show [optimal.cpp](optimal.cpp), run it.

### 7. Edge Cases + Common Mistakes (≈1 min)

- Duplicates `[3, 3]`, negatives, zeros. Mistake: inserting before checking.

### 8. Comparison + Pattern (≈1 min)

- Show the comparison table.
- Pattern: "pair search → complement + hash map", "sorted array → two pointers".

### 9. Follow-ups + Practice (≈1 min)

- Sorted input → Two Sum II. Three numbers → 3Sum. Next video teaser.

## YouTube Description

Two Sum (LeetCode 1) explained step by step in C++: brute force O(n²) → sort + two pointers O(n log n) → hash map O(n). Learn the "complement" trick that solves dozens of interview problems.

00:00 Intro
00:00 Problem explained
00:00 Constraints
00:00 Brute force — O(n²)
00:00 Sort + two pointers — O(n log n)
00:00 Key insight
00:00 Hash map — O(n)
00:00 Dry run
00:00 Edge cases & mistakes
00:00 Pattern takeaway
00:00 Follow-ups & practice

Problem: https://leetcode.com/problems/two-sum/
Notes + code: https://github.com/seuristic/dsa/tree/main/yt/001-two-sum

## Tags

two sum, leetcode 1, two sum leetcode, two sum c++, hash map, unordered_map, two pointers, blind 75, leetcode easy, dsa for beginners, coding interview, data structures and algorithms

## Thumbnail Text

O(n²) → O(n)
