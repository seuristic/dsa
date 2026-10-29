# 008. Search in Rotated Sorted Array

**Difficulty:** Medium · **Tags:** array, binary search

**Problem:** [LeetCode 33](https://leetcode.com/problems/search-in-rotated-sorted-array/) · **Video:** TODO

## Problem in Simple Words

You get a sorted array of **unique** numbers that may have been **rotated** (for example, `[0, 1, 2, 4, 5, 6, 7]` → `[4, 5, 6, 7, 0, 1, 2]`), and a `target`.
Return the **index** of `target`, or `-1` if it isn't there.
It must run in **O(log n)** time.

## Examples

| `nums`                  | `target` | Output | Why                    |
| ----------------------- | -------- | ------ | ---------------------- |
| `[4, 5, 6, 7, 0, 1, 2]` | `0`      | `4`    | `nums[4] = 0`          |
| `[4, 5, 6, 7, 0, 1, 2]` | `3`      | `-1`   | `3` isn't in the array |
| `[1]`                   | `0`      | `-1`   | `0` isn't in the array |

## Constraints → What They Tell Us

- `1 <= nums.length <= 5000`
- `-10^4 <= nums[i], target <= 10^4`
- All values are **unique**.
- `nums` is sorted, possibly rotated.

What this means:

- **O(log n) is required:** a scan works for n = 5000, but the problem asks for **binary search**.
- **Unique values:** comparisons never tie, so we always know which side is sorted.
- **"Possibly rotated":** the array may be fully sorted. The solution must handle that too.
- **Target may be missing:** return `-1`.

## Prerequisites

- **Binary search:** halve the range with one comparison per step.
- **Find Minimum in Rotated Sorted Array** ([#007](../007-find-minimum-in-rotated-sorted-array/)): a rotated sorted array is two sorted parts, and you can find where they meet in O(log n).

## How to Think About It

Normal binary search needs the whole range to be sorted. Here it isn't. But look at what happens when you cut at `mid`:

```
[4, 5, 6, 7, 0, 1, 2]
          ↑
         mid
[4, 5, 6, 7]  [0, 1, 2]
 sorted ✓      sorted ✓  (here both are; in general at least one is)
```

- Cutting a rotated sorted array at any `mid` leaves **at least one half fully sorted**.
- How to tell which one? If `nums[left] <= nums[mid]`, the left half has no "drop" in it, so it's sorted. Otherwise, the right half is.
- In a **sorted** half, checking "is `target` in here?" is easy: just compare with its two ends.
- If `target` is in the sorted half, go there. If not, it can only be in the other half.

Each step still throws away half the array. That's O(log n).

## Approach 1: Brute Force

- **Idea:** Scan every index. Return it if `nums[i] == target`.
- **Why it works:** We look at every number.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n), Space O(1)
- **Why it's not enough:** It ignores that the array is two sorted parts. The problem asks for O(log n).

## Approach 2: Better (Find the Pivot, Then Binary Search)

- **Idea:**
  1. Find the index of the minimum, `pivot`, with the binary search from #007.
  2. Now we know the two sorted parts: `[0, pivot - 1]` and `[pivot, n - 1]`.
  3. If `nums[pivot] <= target <= nums[n - 1]`, search the right part. Otherwise, search the left part.
  4. Normal binary search in that part.
- **Why it works:** Each part is plain sorted, so normal binary search is correct inside it. And the target can only be in the part whose range covers it.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(log n), Space O(1)
- **Why it's not enough:** It's already O(log n), but it uses **two** binary searches and more code. We can decide the direction in a single binary search, by checking which half of `mid` is sorted at every step.

## Approach 3: Optimal (One Binary Search)

- **Idea:** `left = 0`, `right = n - 1`. While `left <= right`:
  1. `mid = left + (right - left) / 2`. If `nums[mid] == target`, return `mid`.
  2. **Left half sorted** (`nums[left] <= nums[mid]`):
     - If `nums[left] <= target < nums[mid]` → `right = mid - 1`.
     - Else → `left = mid + 1`.
  3. **Right half sorted** (otherwise):
     - If `nums[mid] < target <= nums[right]` → `left = mid + 1`.
     - Else → `right = mid - 1`.

  Not found → return `-1`.

- **Why it works:** At least one half is sorted, and for a sorted half, the range check is exact. If the target is in its range, it can only be there. If not, it can only be in the other half. Either way, we never throw away the target.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(log n), Space O(1)

## Dry Run (Optimal)

`nums = [4, 5, 6, 7, 0, 1, 2]`, `target = 0`

| `left` | `right` | `mid` | `nums[mid]` | Sorted half    | `target` in it?   | Next         |
| ------ | ------- | ----- | ----------- | -------------- | ----------------- | ------------ |
| 0      | 6       | 3     | 7           | left `[4 … 7]` | No                | `left = 4`   |
| 4      | 6       | 5     | 1           | left `[0 … 1]` | Yes (`0 ≤ 0 < 1`) | `right = 4`  |
| 4      | 4       | 4     | 0           | —              | —                 | **return 4** |

## Edge Cases

| Case                 | Example                                 | What happens                                            |
| -------------------- | --------------------------------------- | ------------------------------------------------------- |
| One number, missing  | `[1]`, target `0`                       | `nums[0] != 0`, range empties → `-1`                    |
| One number, found    | `[1]`, target `1`                       | Found at `mid = 0` → `0`                                |
| Two numbers, rotated | `[3, 1]`, target `1`                    | `left == mid`, left half is just `[3]` → go right → `1` |
| Not rotated          | `[1, 2, 3, 4, 5]`, target `4`           | Left half always sorted → normal binary search → `3`    |
| Target is the max    | `[4, 5, 6, 7, 0, 1, 2]`, target `7`     | Found at the first `mid` → `3`                          |
| Target out of range  | `[6, 7, 1, 2, 3, 4, 5]`, target `10000` | Never matches → `-1`                                    |

## Common Mistakes

- **`nums[left] < nums[mid]` instead of `<=`:** when `left == mid` (two numbers left), the left "half" is one number, which is sorted. With `<`, `[3, 1]` with target `1` returns `-1`.
- **Range check on the unsorted half:** "is `target` between `nums[mid]` and `nums[right]`?" only means something if that half is sorted. Always check the **sorted** half first.
- **Wrong range ends:** the left check is `nums[left] <= target < nums[mid]` (both ends inside the half). Missing the `=` on `nums[left]` skips the target when it's at `left`.
- **Using the #007 template (`left < right`, `right = mid`):** here we're looking for an exact value, so use `left <= right` and move past `mid` (`mid ± 1`).

## Comparison

| Approach                   | Time         | Space | Note                               |
| -------------------------- | ------------ | ----- | ---------------------------------- |
| Linear scan                | O(n)         | O(1)  | Ignores the sorted structure       |
| Find pivot + binary search | O(log n)     | O(1)  | Two searches; reuses #007          |
| One binary search          | **O(log n)** | O(1)  | Pick the sorted half at every step |

## Pattern Takeaway

- **Rotated sorted array → one half is always sorted.** Use the sorted half to decide where to go.
- **Binary search doesn't need fully sorted data.** It needs a way to rule out half the range with one check.
- **Break a hard problem into solved ones:** "find pivot" (#007) + "binary search" already gets O(log n). Then merge them.

## Practice Next

| Problem                                                                                                                                                            | Difficulty | How it relates                                              |
| ------------------------------------------------------------------------------------------------------------------------------------------------------------------ | ---------- | ----------------------------------------------------------- |
| [Binary Search](https://leetcode.com/problems/binary-search/)                                                                                                      | Easy       | The basic template used inside                              |
| [Find Minimum in Rotated Sorted Array](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/) ([#007](../007-find-minimum-in-rotated-sorted-array/)) | Medium     | The pivot search used in the better approach                |
| [Search in Rotated Sorted Array II](https://leetcode.com/problems/search-in-rotated-sorted-array-ii/)                                                              | Medium     | Same problem with duplicates                                |
| [Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/)                  | Medium     | Two binary searches for the two ends of a range             |
| [Search a 2D Matrix](https://leetcode.com/problems/search-a-2d-matrix/)                                                                                            | Medium     | Binary search on data that's "sorted" in a less obvious way |

## Interview Follow-ups

- **"What if there are duplicates?"** → `[1, 0, 1, 1, 1]`: `nums[left] == nums[mid] == nums[right]` and you can't tell which half is sorted. Shrink both ends (`left++`, `right--`) and try again. Worst case becomes O(n).
- **"Just return true/false."** → Same code, return `true` instead of `mid`.
- **"How many times was it rotated?"** → That's the pivot index, from #007.
- **"Why not just find the pivot and do one search?"** → That's the better approach. Also O(log n), and fine to give in an interview. The one-pass version is shorter and shows you understand the sorted-half idea.

## TL;DR

- At every `mid`, one half is sorted: left if `nums[left] <= nums[mid]`, else right.
- If `target` is inside the sorted half's range, go there. Otherwise go to the other half.
- `while (left <= right)`, return `mid` on a match, `-1` at the end.
- O(log n) time, O(1) space.
