# 003. Contains Duplicate

**Difficulty:** Easy · **Tags:** array, hash set, sorting

**Problem:** [LeetCode 217](https://leetcode.com/problems/contains-duplicate/) · **Video:** [YouTube](https://youtu.be/BI9EpeAjRlM)

## Problem in Simple Words

You get an array `nums`.
Return `true` if **any number appears at least twice**.
Return `false` if every number is different.

## Examples

| `nums`                           | Output  | Why                                      |
| -------------------------------- | ------- | ---------------------------------------- |
| `[1, 2, 3, 1]`                   | `true`  | `1` appears twice                        |
| `[1, 2, 3, 4]`                   | `false` | All four numbers are different           |
| `[1, 1, 1, 3, 3, 4, 3, 2, 4, 2]` | `true`  | Many repeats; finding just one is enough |

## Constraints → What They Tell Us

- `1 <= nums.length <= 10^5`
- `-10^9 <= nums[i] <= 10^9`

What this means:

- **n ≤ 10⁵:** comparing every pair is about 5 × 10⁹ checks. **Too slow.** We need O(n log n) or O(n).
- **Values up to ±10⁹:** too big to use as array indices (a "seen" array of size 2 × 10⁹ won't fit). Use a hash set or sorting instead.
- **`nums.length` can be 1:** one number can't repeat → `false`.
- **We only need yes/no:** stop at the first repeat. No need to count or list them.

## Prerequisites

- **Arrays and loops:** reading `nums[i]` one by one.
- **Sorting (`sort`):** puts equal values next to each other. O(n log n).
- **Hash set (`unordered_set`):** stores values with no duplicates. Checking "is `x` inside?" takes O(1) on average.

## How to Think About It

Ask yourself: _"While reading the array left to right, how do I know if I've **seen this number before**?"_

- If you remember nothing, you must look back over everything → slow.
- If equal numbers were **next to each other**, one look at the neighbor would be enough → sorting.
- If you keep a **notebook of numbers already seen** with instant lookup → hash set.

"Have I seen this before?" is the same question as Two Sum (#001). Here we look for the **same** value instead of a partner value.

## Approach 1: Brute Force

- **Idea:** Compare every pair `(i, j)` with `i < j`. If `nums[i] == nums[j]`, return `true`.
- **Why it works:** Every possible pair is checked, so no repeat is missed.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** For each number we scan **everything after it** to find a match. A repeat could be anywhere, so we keep searching far away. If equal numbers sat side by side, we'd only need to check one neighbor.

## Approach 2: Better (Sort + Check Neighbors)

- **Idea:**
  1. Sort `nums`.
  2. Walk once: if `nums[i] == nums[i - 1]` for any `i`, return `true`.
- **Why it works:** After sorting, equal values are always **next to each other**. So a duplicate exists exactly when some neighbor pair is equal.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(n log n) for sorting, Space O(1) extra (the sort itself uses O(log n) stack)
- **Why it's not enough:** We sort the **whole** array (O(n log n)) just to answer yes/no, even when the repeat is in the first two numbers. It also changes the caller's array. A hash set answers in one O(n) pass and stops at the first repeat.

## Approach 3: Optimal (Hash Set)

- **Idea:** Walk the array once with a set `seen`. For each `x`:
  1. If `x` is already in `seen` → return `true`.
  2. Otherwise, add `x` to `seen`.

  If the loop ends, return `false`.

- **Why it works:** When we reach the second copy of a number, the first copy is already in `seen`. So we always catch it.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n) on average, Space O(n)

## Dry Run (Optimal)

`nums = [1, 2, 3, 1]`

| Step | `x` | `x` in `seen`? | `seen` after step |
| ---- | --- | -------------- | ----------------- |
| 1    | 1   | No             | `{1}`             |
| 2    | 2   | No             | `{1, 2}`          |
| 3    | 3   | No             | `{1, 2, 3}`       |
| 4    | 1   | **Yes**        | return `true`     |

## Edge Cases

| Case                   | Example              | What happens                                    |
| ---------------------- | -------------------- | ----------------------------------------------- |
| Only one number        | `[5]`                | Nothing to repeat → `false`                     |
| Just two equal numbers | `[7, 7]`             | Second `7` is found in `seen` → `true`          |
| Negative numbers       | `[-1, 2, -1]`        | Sets and sorting handle negatives fine → `true` |
| Extreme values         | `[10^9, -10^9]`      | Different values → `false`                      |
| Repeat far apart       | `[1, 2, 3, 4, 5, 1]` | Found on the last number → `true`               |
| Many repeats           | `[1, 1, 1, 3, 3, …]` | Stops at the very first repeat → `true`         |

## Common Mistakes

- **Using a fixed-size array as a "seen" table:** values go up to ±10⁹ and can be negative. Use `unordered_set` instead.
- **Brute force inner loop from `j = 0`:** then `i == j` compares a number with itself and always says `true`. Start at `j = i + 1`.
- **Sorted check starting at `i = 0`:** `nums[i - 1]` would read `nums[-1]`. Start at `i = 1`.
- **Forgetting that sorting changes the input:** fine on LeetCode, but in real code the caller may not expect their array to be reordered. Sort a copy if that matters.
- **Inserting before checking:** then every number "finds itself" in the set. Check first, then insert.

## Comparison

| Approach              | Time         | Space | Note                                                |
| --------------------- | ------------ | ----- | --------------------------------------------------- |
| Brute force           | O(n²)        | O(1)  | Too slow for n = 10⁵                                |
| Sort + check neighbor | O(n log n)   | O(1)  | Best when extra memory isn't allowed; changes input |
| Hash set              | **O(n)** avg | O(n)  | Fastest; stops at the first repeat                  |

## Pattern Takeaway

- **"Have I seen this before?" → hash set** (or a hash map if you also need the index or a count).
- **Sorting brings equal values together.** Any "find duplicates / group equal things" problem gets easier after sorting.
- **Time vs. space trade-off:** sorting saves memory, hashing saves time. Say this out loud in interviews.

## Practice Next

| Problem                                                                               | Difficulty | How it relates                                                     |
| ------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------------------------ |
| [Two Sum](https://leetcode.com/problems/two-sum/) ([#001](../001-two-sum/))           | Easy       | Same "seen before?" lookup, but for a partner value                |
| [Contains Duplicate II](https://leetcode.com/problems/contains-duplicate-ii/)         | Easy       | Repeat must be within `k` positions: store last index in a map     |
| [Valid Anagram](https://leetcode.com/problems/valid-anagram/)                         | Easy       | Count values with a hash map (or sort both strings and compare)    |
| [Find the Duplicate Number](https://leetcode.com/problems/find-the-duplicate-number/) | Medium     | Same question with O(1) space and no changes to the array          |
| [Contains Duplicate III](https://leetcode.com/problems/contains-duplicate-iii/)       | Hard       | "Nearly equal" values within `k` positions: buckets or ordered set |

## Interview Follow-ups

- **"No extra memory."** → Sort, then check neighbors: O(n log n) time, O(1) extra space.
- **"Don't change the input array."** → Use the hash set, or sort a copy (O(n) space).
- **"Return the duplicate values" / "count how many times each appears."** → Use `unordered_map<int, int>` to count.
- **"Values are small, like 0 to 1000."** → A plain `bool seen[1001]` array is faster than a hash set.
- **"Can a hash set be slow?"** → Yes, in the worst case (many values landing in the same bucket) lookups become O(n). Average case is O(1). `set` (a balanced tree) is always O(log n).
- **"One-liner?"** → `return unordered_set<int>(nums.begin(), nums.end()).size() < nums.size();` Short, but it never stops early.

## TL;DR

- Question: "have I seen this number before?"
- Hash set: check `x` in `seen` → if yes, `true`; else insert `x`. O(n) time, O(n) space.
- No extra memory allowed? Sort and compare neighbors. O(n log n) time, O(1) space.
- Check **before** inserting.
