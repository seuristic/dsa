# 001. Two Sum

**Difficulty:** Easy · **Tags:** array, hash map, binary search, two pointers
**Problem:** [LeetCode 1](https://leetcode.com/problems/two-sum/) · **Video:** [YouTube](https://youtu.be/fTVYqq1hjaQ)

## Problem in Simple Words

You get an array `nums` and a number `target`.
Find **two different positions** whose values add up to `target`, and return those two positions (indices).
There is always exactly one answer. You can return the two indices in any order.

## Examples

| `nums`           | `target` | Output   | Why                                                         |
| ---------------- | -------- | -------- | ----------------------------------------------------------- |
| `[2, 7, 11, 15]` | `9`      | `[0, 1]` | `2 + 7 = 9`                                                 |
| `[3, 2, 4]`      | `6`      | `[1, 2]` | `2 + 4 = 6`. Not `[0, 0]`: you can't use the same `3` twice |
| `[3, 3]`         | `6`      | `[0, 1]` | Two different `3`s at different indices are fine            |

## Constraints → What They Tell Us

- `2 <= nums.length <= 10^4`
- `-10^9 <= nums[i], target <= 10^9`
- Exactly one valid answer exists.

What this means:

- **n ≤ 10⁴:** checking every pair is about 5 × 10⁷ checks. That passes, but the follow-up asks for better than O(n²), and interviewers expect O(n).
- **Values can be negative:** any trick that assumes positive numbers breaks.
- **Values up to ±10⁹:** a sum is at most ±2 × 10⁹. That still fits in `int` (max ≈ 2.147 × 10⁹), but only just.
- **Exactly one answer:** stop as soon as you find it. No need to handle "no answer" or "many answers".

## Prerequisites

- **Arrays and indices:** `nums[i]` is the value, `i` is its position.
- **Hash map (`unordered_map`):** stores key → value pairs. Looking up a key takes O(1) on average.
- **Binary search** (approach 2): finds a value in a sorted array in O(log n) by halving the search range each step.
- **Two pointers** (approach 3): two indices that move toward each other on a sorted array.

## How to Think About It

Ask yourself: _"I'm standing at the number `x`. Which number would complete it?"_

The answer is always `target - x`. We call it the **complement**.

So the question changes from _"which two numbers add up to target?"_ (pairs, slow)
to _"have I already seen `target - x`?"_ (a single lookup, fast).

Whenever a problem asks "have I seen this before?", think **hash map**.

## Approach 1: Brute Force

- **Idea:** Try every pair `(i, j)` with `i < j`. If `nums[i] + nums[j] == target`, return them.
- **Why it works:** It checks every possible pair, so it can't miss the answer.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** For each `nums[i]` we **search the whole rest of the array** for its partner. That search is the bottleneck. If finding the partner were faster, the whole thing would be faster.

## Approach 2: Better (Sort + Binary Search)

- **Idea:** Store `(value, index)` pairs and sort them by value. For each position `i`, compute `need = target - a[i].value` and binary-search for `need` only in the part **to the right of `i`** (`i + 1` to `n - 1`).
- **Why it works:** Sorting lets us find any value in O(log n) instead of O(n). Searching only to the right means an element never matches itself, and no pair is missed: the left element of the answer pair always finds the right one.
- **Code:** [better1.cpp](better1.cpp)
- **Complexity:** Time O(n log n) (sort + `n` searches of O(log n) each), Space O(n) for the pairs
- **Why it's not enough:** We start a fresh search for every element. But in a sorted array, as the left value grows, its partner can only get smaller, so the partner only moves left. Two pointers use this to find every partner in one O(n) scan.

## Approach 3: Better (Sort + Two Pointers)

- **Idea:** Store `(value, index)` pairs and sort them by value. Put `l` at the start and `r` at the end.
  - Sum too small → move `l` right (bigger value).
  - Sum too big → move `r` left (smaller value).
  - Sum equals target → return both original indices.
- **Why it works:** In a sorted array, if `a[l] + a[r]` is too small, `a[l]` can't work with any value at or left of `r`, because those are all ≤ `a[r]`. So `a[l]` can be dropped safely. The same logic, flipped, drops `a[r]` when the sum is too big. Each step removes one candidate, and the answer is never thrown away.
- **Code:** [better2.cpp](better2.cpp)
- **Complexity:** Time O(n log n) for sorting, Space O(n) for the pairs
- **Why it's not enough:** The scan is O(n) now, but sorting still costs O(n log n), and we need extra space to remember the original indices anyway. If we're using O(n) space, we can get O(n) time with a hash map.

## Approach 4: Optimal (One-Pass Hash Map)

- **Idea:** Walk the array once. For each `nums[i]`:
  1. Compute `need = target - nums[i]`.
  2. If `need` is in the map → return `{map[need], i}`.
  3. Otherwise, store `nums[i] → i` in the map.
- **Why it works:** When we reach the second number of the answer pair, the first one is already in the map, so we always find it. We check **before** inserting, so a number can never match itself.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(n)

## Dry Run (Optimal)

`nums = [3, 2, 4]`, `target = 6`

| Step | `i` | `nums[i]` | `need = 6 - nums[i]` | `need` in map?      | Map after step  |
| ---- | --- | --------- | -------------------- | ------------------- | --------------- |
| 1    | 0   | 3         | 3                    | No (map is empty)   | `{3:0}`         |
| 2    | 1   | 2         | 4                    | No                  | `{3:0, 2:1}`    |
| 3    | 2   | 4         | 2                    | **Yes, at index 1** | return `[1, 2]` |

At step 1, `3` needs another `3`. The map is still empty, so it does **not** match itself. That's why we check before inserting.

## Edge Cases

| Case                     | Example                 | What happens                                                           |
| ------------------------ | ----------------------- | ---------------------------------------------------------------------- |
| Same value twice         | `[3, 3]`, `6`           | First `3` is stored, second `3` finds it → `[0, 1]`                    |
| Number is half of target | `[3, 2, 4]`, `6`        | `3` doesn't match itself (check happens before insert)                 |
| Negative numbers         | `[-3, 4, 3, 90]`, `0`   | `need = 0 - 3 = -3`, found → `[0, 2]`. Hash maps handle negatives fine |
| Zeros                    | `[0, 4, 3, 0]`, `0`     | Second `0` finds the first → `[0, 3]`                                  |
| Extreme values           | `[10^9, 5, -10^9]`, `0` | `need` stays within ±2 × 10⁹, so no overflow                           |
| Answer at the end        | `[1, 2, 3, 4, 5]`, `9`  | Found on the last element → `[3, 4]`                                   |

## Common Mistakes

- **Using the same element twice:** inserting `nums[i]` _before_ checking makes `[3, 2, 4], 6` return `[0, 0]`.
- **Returning values instead of indices:** the problem asks for positions.
- **Sorting `nums` directly in approaches 2–3:** you lose the original indices. Sort `(value, index)` pairs instead.
- **Binary-searching the whole array in approach 2:** with `[3, 2, 4], 6`, the `3` searches for `3` and finds itself. Search only from `i + 1`.
- **Starting the inner loop at `j = 0`:** it checks pairs twice and pairs an element with itself. Start at `j = i + 1`.
- **Assuming numbers are positive:** don't stop early when a value exceeds `target`. Negatives can bring the sum back down.

## Comparison

| Approach             | Time       | Space | Note                                                                 |
| -------------------- | ---------- | ----- | -------------------------------------------------------------------- |
| Brute force          | O(n²)      | O(1)  | Simplest, slow for big inputs                                        |
| Sort + binary search | O(n log n) | O(n)  | Search per element drops from O(n) to O(log n)                       |
| Sort + two pointers  | O(n log n) | O(n)  | Best if the array is **already sorted** (then O(n) time, O(1) space) |
| Hash map             | **O(n)**   | O(n)  | Best in general                                                      |

## Pattern Takeaway

- **"Find a pair that satisfies X" → for each element, ask what partner it needs, and look that partner up in a hash map.** This turns O(n²) into O(n).
- **"Have I seen this before?" → hash set or hash map.**
- **Pair sum on a sorted array → two pointers**, with O(1) extra space.

## Practice Next

| Problem                                                                                               | Difficulty | How it relates                                                |
| ----------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------------------- |
| [Contains Duplicate](https://leetcode.com/problems/contains-duplicate/)                               | Easy       | Same "have I seen it?" hash set idea                          |
| [Two Sum IV - Input is a BST](https://leetcode.com/problems/two-sum-iv-input-is-a-bst/)               | Easy       | Same complement idea, on a tree                               |
| [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Medium     | Approach 3 with O(1) space, since the array is already sorted |
| [3Sum](https://leetcode.com/problems/3sum/)                                                           | Medium     | Fix one number, then run Two Sum (two pointers) on the rest   |
| [Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)                         | Medium     | Same complement lookup, but on prefix sums                    |

## Interview Follow-ups

- **"The array is sorted."** → Two pointers: O(n) time, O(1) space.
- **"Return the values, not the indices."** → Sort and use two pointers. No index bookkeeping needed.
- **"Find all pairs" / "count pairs".** → Store counts in the hash map instead of indices, and handle duplicates carefully.
- **"Numbers arrive one by one (a stream)."** → Keep a hash map of counts; for each query, look up `target - x`.
- **"No extra memory allowed."** → Sort in place and use two pointers: O(n log n) time, O(1) space.
- **"There might be no answer."** → Return `{}` (or `[-1, -1]`) after the loop.

## TL;DR

- For each `x`, the partner is `target - x`.
- Store each number you've seen in a hash map (`value → index`).
- Check the map **before** inserting the current number.
- O(n) time, O(n) space. If the array is already sorted, two pointers need O(1) space.
