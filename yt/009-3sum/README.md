# 009. 3Sum

**Difficulty:** Medium · **Tags:** array, two pointers, sorting

**Problem:** [LeetCode 15](https://leetcode.com/problems/3sum/) · **Video:** TODO

## Problem in Simple Words

You get an array `nums`.
Find every group of **three numbers** (at three different positions) that **adds up to `0`**.
Return each group once: **no duplicate triplets**, even if the same numbers appear at different positions.

## Examples

| `nums`                  | Output                      | Why                                                                 |
| ----------------------- | --------------------------- | ------------------------------------------------------------------- |
| `[-1, 0, 1, 2, -1, -4]` | `[[-1, -1, 2], [-1, 0, 1]]` | `[-1, 0, 1]` can be made two ways (two `-1`s), but it's listed once |
| `[0, 1, 1]`             | `[]`                        | The only triplet sums to `2`                                        |
| `[0, 0, 0]`             | `[[0, 0, 0]]`               | The only triplet sums to `0`                                        |

The order of triplets, and of numbers inside a triplet, doesn't matter.

## Constraints → What They Tell Us

- `3 <= nums.length <= 3000`
- `-10^5 <= nums[i] <= 10^5`

What this means:

- **n ≤ 3000:** trying every triplet is about n³/6 ≈ 4.5 × 10⁹. **Too slow.** But n² ≈ 9 × 10⁶ is fine. Target: **O(n²)**.
- **O(n²) is already huge compared to sorting:** sorting costs O(n log n), which is basically free here. So sorting first is a good idea.
- **Sums stay small:** at most 3 × 10⁵, fits in `int`.
- **Duplicates in the input:** `nums` can repeat values. Avoiding duplicate triplets is the **hard part** of this problem.

## Prerequisites

- **Two Sum** ([#001](../001-two-sum/)): find two numbers that add up to a target.
- **Two pointers on a sorted array:** `left` at the start, `right` at the end. Sum too small → move `left` right. Too big → move `right` left.
- **Sorting:** `sort` in O(n log n). Equal values end up next to each other.

## How to Think About It

Ask yourself: _"If I fix one number, what's left?"_

- Fix `nums[i]`. Now you need two other numbers that add up to `-nums[i]`.
- That's just **Two Sum** with target `-nums[i]`. So 3Sum = "for each `i`, solve Two Sum".
- Two Sum on a **sorted** array uses two pointers, with no extra memory.

Then the duplicates:

- After sorting, equal values sit **next to each other**.
- If `nums[i]` equals `nums[i - 1]`, every triplet it could make was already found. **Skip it.**
- Same inside Two Sum: after finding a triplet, move `left` past all copies of the same value.

```
sorted: [-4, -1, -1, 0, 1, 2]
          i   ↑   ↑
              │   └─ same as before → skip
              └─ fix -1, find two numbers that sum to 1
```

## Approach 1: Brute Force

- **Idea:** Try every triplet `i < j < k`. If the sum is `0`, sort the three numbers and put them in a `set` (which removes duplicates).
- **Why it works:** Every triplet is checked. Sorting each one makes `[-1, 0, 1]` and `[0, 1, -1]` look the same, so the `set` keeps only one.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n³ · log n), Space O(k) for the `set`, where `k` is the number of distinct triplets
  - Three nested loops: O(n³) triplets.
  - Each match is inserted into the `set`, which costs O(log k). In the worst case almost every triplet matches, and `k` can be up to n² (two values fix the third), so log k = O(log n).
- **Why it's not enough:** The third loop just searches for one value: `-(nums[i] + nums[j])`. Searching for a value is what a hash set does in O(1).

## Approach 2: Better (Hash Set)

- **Idea:** Fix `i`. Walk `j` from `i + 1`. The third number must be `need = -(nums[i] + nums[j])`. Keep a hash set `seen` of the numbers between `i` and `j`. If `need` is in `seen`, we found a triplet. Then add `nums[j]` to `seen`.
- **Why it works:** For a fixed `i`, this is Two Sum (#001) with target `-nums[i]`, solved with a hash set. Each triplet is sorted and put in a `set` to remove duplicates.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n² · log n) (hash lookups are O(1), the `set` of triplets adds the log), Space O(n) for `seen` + O(k) for the triplets
- **Why it's not enough:** It still needs the hash set and the `set` of triplets just to remove duplicates. If we **sort the array first**, equal values sit together. Then we can skip duplicates directly, and Two Sum can use two pointers with no extra memory.

## Approach 3: Optimal (Sort + Two Pointers)

- **Idea:**
  1. Sort `nums`.
  2. For each `i` (skip it if `nums[i] == nums[i - 1]`):
     - `left = i + 1`, `right = n - 1`.
     - `sum = nums[i] + nums[left] + nums[right]`.
     - `sum < 0` → `left++` (need bigger). `sum > 0` → `right--` (need smaller).
     - `sum == 0` → save the triplet, move both pointers, then skip copies of `nums[left]`.
- **Why it works:**
  - In a sorted array, moving `left` right makes the sum bigger, and moving `right` left makes it smaller. So we never skip a valid pair.
  - Skipping equal `nums[i]` and equal `nums[left]` means each value combination is found exactly once. No `set` needed.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n²) (sort is O(n log n), then n × a two-pointer scan), Space O(1) extra besides the output (ignoring the sort's own stack)

## Dry Run (Optimal)

`nums = [-1, 0, 1, 2, -1, -4]` → sorted: `[-4, -1, -1, 0, 1, 2]`

| `i` | `nums[i]` | `left`, `right` | Values | `sum` | Action                                       |
| --- | --------- | --------------- | ------ | ----- | -------------------------------------------- |
| 0   | -4        | 1, 5            | -1, 2  | -3    | too small → `left++`                         |
| 0   | -4        | 2, 5            | -1, 2  | -3    | too small → `left++`                         |
| 0   | -4        | 3, 5            | 0, 2   | -2    | too small → `left++`                         |
| 0   | -4        | 4, 5            | 1, 2   | -1    | too small → `left++` → `left == right`, stop |
| 1   | -1        | 2, 5            | -1, 2  | 0     | **save `[-1, -1, 2]`**, move both            |
| 1   | -1        | 3, 4            | 0, 1   | 0     | **save `[-1, 0, 1]`**, move both → stop      |
| 2   | -1        | —               | —      | —     | same as `nums[1]` → **skip**                 |
| 3   | 0         | 4, 5            | 1, 2   | 3     | too big → `right--` → stop                   |

Result: `[[-1, -1, 2], [-1, 0, 1]]`.

## Edge Cases

| Case                     | Example                   | What happens                                              |
| ------------------------ | ------------------------- | --------------------------------------------------------- |
| No triplet               | `[0, 1, 1]`               | Never hits `sum == 0` → `[]`                              |
| All zeros                | `[0, 0, 0, 0]`            | Found once, the other `0`s are skipped → `[[0, 0, 0]]`    |
| Same triplet many ways   | `[-1, -1, -1, 2, 2]`      | Skips repeat `i` and repeat `left` → `[[-1, -1, 2]]`      |
| Two triplets for one `i` | `[-2, 0, 1, 1, 2]`        | Keeps scanning after a match → `[[-2, 0, 2], [-2, 1, 1]]` |
| All positive             | `[1, 2, 3]`               | Sum is always too big → `[]`                              |
| Extreme values           | `[-10^5, 5·10^4, 5·10^4]` | Sums fit in `int` → one triplet                           |

## Common Mistakes

- **Returning duplicates:** forgetting to skip equal `nums[i]` or equal `nums[left]`. `[-1, -1, -1, 2, 2]` then returns `[-1, -1, 2]` more than once.
- **Skipping with `nums[i] == nums[i + 1]`:** that skips the **first** copy, and loses triplets that use two copies, like `[-1, -1, 2]`. Compare with the **previous** one: `nums[i] == nums[i - 1]`.
- **Stopping after the first match for `i`:** there can be several pairs for the same `i`. Move both pointers and keep going.
- **Skipping duplicates before saving:** skip copies **after** saving a triplet, not before you check it.
- **Two pointers without sorting:** the "too small → move `left`" rule only works on a sorted array.

## Comparison

| Approach            | Time          | Space (extra) | Note                                  |
| ------------------- | ------------- | ------------- | ------------------------------------- |
| Brute force         | O(n³ · log n) | O(k)          | Too slow for n = 3000                 |
| Hash set            | O(n² · log n) | O(n + k)      | Two Sum with a hash set for each `i`  |
| Sort + two pointers | **O(n²)**     | **O(1)**      | Sorting makes duplicates easy to skip |

## Pattern Takeaway

- **k-Sum → fix one number, solve (k−1)-Sum.** 3Sum = loop + Two Sum. 4Sum = loop + 3Sum.
- **"No duplicate results" → sort first.** Equal values sit together, so you can skip them with one comparison.
- **Sorted array + pair with a target sum → two pointers.** Sum too small, move `left`. Too big, move `right`.
- **If your answer is already O(n²), sorting (O(n log n)) is free.**

## Practice Next

| Problem                                                                                               | Difficulty | How it relates                                |
| ----------------------------------------------------------------------------------------------------- | ---------- | --------------------------------------------- |
| [Two Sum](https://leetcode.com/problems/two-sum/) ([#001](../001-two-sum/))                           | Easy       | The inner problem, with a hash map            |
| [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Medium     | The inner problem, with two pointers          |
| [3Sum Closest](https://leetcode.com/problems/3sum-closest/)                                           | Medium     | Same loop; track the sum closest to a target  |
| [4Sum](https://leetcode.com/problems/4sum/)                                                           | Medium     | One more outer loop; watch out for overflow   |
| [Container With Most Water](https://leetcode.com/problems/container-with-most-water/)                 | Medium     | Two pointers from both ends, next in Blind 75 |

## Interview Follow-ups

- **"Can you stop early?"** → After sorting, if `nums[i] > 0`, every number after it is positive too. No triplet can sum to `0`, so `break`.
- **"Target is not 0?"** → Same code, compare `sum` with `target` instead of `0`.
- **"Return indices, not values."** → Sorting loses the original positions. Sort pairs of `(value, index)`, or use the hash set approach.
- **"Count the triplets instead of listing them."** → Same two pointers. For "sum less than target" counts (3Sum Smaller), when `sum < target`, all `right - left` pairs work at once.
- **"4Sum, kSum?"** → Fix one number and recurse down to Two Sum. O(n^(k−1)). Use `long long` for the sum.

## TL;DR

- Sort. For each `i`, run two pointers on the rest to find pairs summing to `-nums[i]`.
- Skip `i` if `nums[i] == nums[i - 1]`. After a match, move both pointers and skip equal `nums[left]`.
- Sum too small → `left++`. Too big → `right--`.
- O(n²) time, O(1) extra space.
