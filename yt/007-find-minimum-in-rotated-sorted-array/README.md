# 007. Find Minimum in Rotated Sorted Array

**Difficulty:** Medium · **Tags:** array, binary search

**Problem:** [LeetCode 153](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) · **Video:** TODO

## Problem in Simple Words

You get a sorted array of **unique** numbers that has been **rotated**: some numbers from the end were moved to the front.
For example, `[0, 1, 2, 4, 5, 6, 7]` can become `[4, 5, 6, 7, 0, 1, 2]`.
Return the **smallest** number. It must run in **O(log n)** time.

## Examples

| `nums`                  | Output | Why                                               |
| ----------------------- | ------ | ------------------------------------------------- |
| `[3, 4, 5, 1, 2]`       | `1`    | `[1, 2, 3, 4, 5]` rotated 3 times                 |
| `[4, 5, 6, 7, 0, 1, 2]` | `0`    | `[0, 1, 2, 4, 5, 6, 7]` rotated 4 times           |
| `[11, 13, 15, 17]`      | `11`   | Rotated 4 times = back to the start, still sorted |

## Constraints → What They Tell Us

- `1 <= n <= 5000`
- `-5000 <= nums[i] <= 5000`
- All numbers are **unique**.
- `nums` is sorted, then rotated between `1` and `n` times.

What this means:

- **O(log n) is required:** a simple scan is O(n). It passes for n = 5000, but the problem asks for O(log n), so the interviewer wants **binary search**.
- **Unique numbers:** no ties. Every comparison clearly tells us which side we're on.
- **Rotated `n` times = not rotated at all:** the array can be fully sorted. The answer is then `nums[0]`.
- **n can be 1:** the only number is the answer.

## Prerequisites

- **Binary search:** cut the search range in half every step using one comparison. O(log n).
- **`mid = lo + (hi - lo) / 2`:** the middle index without overflow.

## How to Think About It

Draw the rotated array as a graph:

```
value
  7 |       ●
  6 |     ●
  5 |   ●
  4 | ●
  2 |                   ●
  1 |                 ●
  0 |               ●   ← minimum: where the "cliff" ends
    +----------------------
      4  5  6  7  0  1  2
      left part   right part
```

- A rotated sorted array is **two sorted parts**. Every number in the left part is **bigger** than every number in the right part.
- The minimum is the **first number of the right part**.
- So the question is: _"Is `mid` in the left part or the right part?"_
- Compare `nums[mid]` with the **last number**, `nums[hi]`:
  - `nums[mid] > nums[hi]` → `mid` is in the left (bigger) part. The minimum is **to the right** of `mid`.
  - `nums[mid] < nums[hi]` → `mid` is in the right part. The minimum is `mid` **or to its left**.

One comparison throws away half the array. That's binary search.

## Approach 1: Brute Force

- **Idea:** Scan every number and keep the smallest.
- **Why it works:** The minimum is somewhere in the array, and we look at all of it.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n), Space O(1)
- **Why it's not enough:** It ignores that the array is **almost sorted**. The problem asks for O(log n). Sorted data means binary search: we only need to know which part `mid` is in.

## Approach 2: Optimal (Binary Search)

- **Idea:** Keep `lo = 0`, `hi = n - 1`. While `lo < hi`:
  1. `mid = lo + (hi - lo) / 2`.
  2. If `nums[mid] > nums[hi]` → the minimum is right of `mid`: `lo = mid + 1`.
  3. Else → the minimum is `mid` or left of it: `hi = mid`.

  When `lo == hi`, that's the minimum.

- **Why it works:** The minimum always stays inside `[lo, hi]`:
  - If `nums[mid] > nums[hi]`, there's a drop somewhere after `mid`, so `mid` isn't the minimum. Skip it.
  - Otherwise `mid` to `hi` is sorted, so nothing after `mid` is smaller. But `mid` might be the minimum, so keep it (`hi = mid`, not `mid - 1`).
  - The range shrinks every step, so the loop ends.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(log n), Space O(1)

## Dry Run (Optimal)

`nums = [4, 5, 6, 7, 0, 1, 2]`

| `lo` | `hi` | `mid` | `nums[mid]` | `nums[hi]` | Decision                          |
| ---- | ---- | ----- | ----------- | ---------- | --------------------------------- |
| 0    | 6    | 3     | 7           | 2          | `7 > 2` → go right: `lo = 4`      |
| 4    | 6    | 5     | 1           | 2          | `1 < 2` → keep `mid`: `hi = 5`    |
| 4    | 5    | 4     | 0           | 1          | `0 < 1` → keep `mid`: `hi = 4`    |
| 4    | 4    | —     | —           | —          | `lo == hi` → return `nums[4] = 0` |

## Edge Cases

| Case                 | Example                | What happens                                          |
| -------------------- | ---------------------- | ----------------------------------------------------- |
| Not rotated          | `[11, 13, 15, 17]`     | `nums[mid] < nums[hi]` every time → `hi` walks to `0` |
| One number           | `[1]`                  | Loop never runs → `nums[0]`                           |
| Two numbers, rotated | `[2, 1]`               | `2 > 1` → `lo = 1` → `1`                              |
| Two numbers, sorted  | `[1, 2]`               | `1 < 2` → `hi = 0` → `1`                              |
| Minimum at index 1   | `[5, 1, 2, 3, 4]`      | Binary search narrows down to index 1                 |
| Minimum at the end   | `[2, 3, 4, 5, 1]`      | Keeps going right → last index                        |
| Negative numbers     | `[0, 5000, -5000, -1]` | Works the same → `-5000`                              |

## Common Mistakes

- **Comparing with `nums[lo]` instead of `nums[hi]`:** on a sorted array like `[1, 2, 3, 4, 5]`, `nums[mid] > nums[lo]` sends you right, away from the minimum. Comparing with `nums[hi]` works in every case.
- **`hi = mid - 1`:** `mid` might be the minimum. Dropping it loses the answer. Use `hi = mid`.
- **`while (lo <= hi)` with `hi = mid`:** when `lo == hi`, nothing changes and the loop never ends. Use `lo < hi`.
- **`mid = (lo + hi) / 2`:** fine here (n ≤ 5000), but `lo + (hi - lo) / 2` is the habit that never overflows.

## Comparison

| Approach      | Time         | Space | Note                               |
| ------------- | ------------ | ----- | ---------------------------------- |
| Linear scan   | O(n)         | O(1)  | Ignores the sorted structure       |
| Binary search | **O(log n)** | O(1)  | Compare `mid` with the last number |

## Pattern Takeaway

- **"Sorted but rotated" → still binary search.** One side of `mid` is always sorted.
- **Binary search on a condition, not a value:** here the question is "is `mid` in the left part?". The answer is `yes, yes, …, no, no` across the array. Binary search finds where it flips.
- **`lo < hi` with `hi = mid`** is the template for "find the first index where something becomes true".

## Practice Next

| Problem                                                                                                           | Difficulty | How it relates                                   |
| ----------------------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------ |
| [Binary Search](https://leetcode.com/problems/binary-search/)                                                     | Easy       | The basic template                               |
| [Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/)                   | Medium     | Same array, find a target. Next in Blind 75      |
| [Find Peak Element](https://leetcode.com/problems/find-peak-element/)                                             | Medium     | Binary search on a condition, not a sorted array |
| [Find Minimum in Rotated Sorted Array II](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/) | Hard       | Same problem with duplicates                     |

## Interview Follow-ups

- **"How many times was it rotated?"** → The index of the minimum, `lo`. (For `[4, 5, 6, 7, 0, 1, 2]`, that's 4.)
- **"Find the maximum."** → It's just before the minimum: `nums[(lo - 1 + n) % n]`.
- **"What if there are duplicates?"** → When `nums[mid] == nums[hi]`, you can't tell which part `mid` is in. Do `hi--` (safe, since `nums[mid]` still holds the same value). Worst case becomes O(n), e.g. `[1, 1, 1, 0, 1]`.
- **"Search for a target instead?"** → Find which half of `mid` is sorted, check if the target falls in it, and go that way. That's Search in Rotated Sorted Array.

## TL;DR

- Rotated sorted = two sorted parts. The minimum starts the right part.
- `nums[mid] > nums[hi]` → `lo = mid + 1`. Otherwise → `hi = mid`.
- Loop while `lo < hi`. Answer is `nums[lo]`.
- O(log n) time, O(1) space.
