# 010. Container With Most Water

**Difficulty:** Medium · **Tags:** array, two pointers, greedy

**Problem:** [LeetCode 11](https://leetcode.com/problems/container-with-most-water/) · **Video:** TODO

## Problem in Simple Words

You get an array `height`. Each `height[i]` is a vertical line standing at position `i`.
Pick **two lines**. Together with the ground, they form a container.
Return the **most water** any container can hold.

Water in a container = **width × height**, where:

- width = distance between the two lines (`j - i`)
- height = the **shorter** of the two lines (water spills over the shorter one)

## Examples

| `height`                      | Output | Why                                                 |
| ----------------------------- | ------ | --------------------------------------------------- |
| `[1, 8, 6, 2, 5, 4, 8, 3, 7]` | `49`   | Lines at `1` (height 8) and `8` (height 7): `7 × 7` |
| `[1, 1]`                      | `1`    | Only one container: `1 × 1`                         |

```
8 |    █              █
7 |    █  ~  ~  ~  ~  █  ~  █
6 |    █  █  ~  ~  ~  █  ~  █
5 |    █  █  ~  █  ~  █  ~  █
4 |    █  █  ~  █  █  █  ~  █
3 |    █  █  ~  █  █  █  █  █
2 |    █  █  █  █  █  █  █  █
1 | █  █  █  █  █  █  █  █  █
  +---------------------------
    0  1  2  3  4  5  6  7  8
       └──── width 7 ───────┘    water up to height 7 → 7 × 7 = 49
```

## Constraints → What They Tell Us

- `2 <= n <= 10^5`
- `0 <= height[i] <= 10^4`

What this means:

- **n ≤ 10⁵:** checking every pair is about 5 × 10⁹. **Too slow.** We need O(n).
- **Area fits in `int`:** at most 10⁴ × 10⁵ = 10⁹.
- **Heights can be `0`:** a container with a `0` line holds nothing.
- **n ≥ 2:** there's always at least one container.

## Prerequisites

- **Two pointers from both ends:** `left` starts at `0`, `right` at `n - 1`, and they move toward each other.
- **`min` and `max`:** water height is `min` of two lines; we keep the `max` area.

## How to Think About It

Start with the **widest** container: `left = 0`, `right = n - 1`. Now we must move one pointer inward. Which one?

Ask: _"Can the **shorter** line ever be part of a bigger container?"_

- Say `height[left]` is the shorter one.
- Any other container using `left` would pair it with a line **between** `left` and `right`.
- That container is **narrower** (smaller width).
- And its water height is **at most `height[left]`** (the shorter line still caps it).
- So it can never beat what we have now. The shorter line is **used up**. Drop it: `left++`.

Moving the **taller** line instead can't help: the width shrinks and the shorter line still caps the height.

```
 shorter line  → already gave its best container → move it
 taller line   → might still be useful            → keep it
```

Every step throws away one line for good. After n − 1 steps, we're done.

## Approach 1: Brute Force

- **Idea:** Try every pair `i < j`. Area = `min(height[i], height[j]) * (j - i)`. Keep the largest.
- **Why it works:** Every possible container is checked.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(n²), Space O(1)
- **Why it's not enough:** Most pairs can't possibly win. Once the shorter line of a pair is known, every narrower container using it is worse. We can rule those out without checking them.

## Approach 2: Optimal (Two Pointers)

- **Idea:**
  1. `left = 0`, `right = n - 1`, `best = 0`.
  2. While `left < right`:
     - `area = min(height[left], height[right]) * (right - left)`, update `best`.
     - Move the **shorter** line inward: if `height[left] < height[right]`, `left++`, else `right--`.
- **Why it works:** Each time we move the shorter line, we only skip containers that are narrower **and** no taller than the one we just measured. So the best container is never skipped.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(n), Space O(1)

## Dry Run (Optimal)

`height = [1, 8, 6, 2, 5, 4, 8, 3, 7]`

| `left` | `right` | Heights | Width | Area | `best` | Move                |
| ------ | ------- | ------- | ----- | ---- | ------ | ------------------- |
| 0      | 8       | 1, 7    | 8     | 8    | 8      | `1 < 7` → `left++`  |
| 1      | 8       | 8, 7    | 7     | 49   | **49** | `8 ≥ 7` → `right--` |
| 1      | 7       | 8, 3    | 6     | 18   | 49     | `right--`           |
| 1      | 6       | 8, 8    | 5     | 40   | 49     | equal → `right--`   |
| 1      | 5       | 8, 4    | 4     | 16   | 49     | `right--`           |
| 1      | 4       | 8, 5    | 3     | 15   | 49     | `right--`           |
| 1      | 3       | 8, 2    | 2     | 4    | 49     | `right--`           |
| 1      | 2       | 8, 6    | 1     | 6    | 49     | `right--` → stop    |

Answer: `49`.

## Edge Cases

| Case                        | Example                                 | What happens                           |
| --------------------------- | --------------------------------------- | -------------------------------------- |
| Only two lines              | `[1, 1]`                                | One container → `1`                    |
| All zeros                   | `[0, 0]`                                | No water → `0`                         |
| One zero line               | `[0, 5]`                                | Shorter line is `0` → `0`              |
| Tallest lines at both ends  | `[4, 3, 2, 1, 4]`                       | First container is the best → `16`     |
| Best pair is close together | `[2, 3, 4, 5, 18, 17, 6]`               | Two tall lines, width 1 → `17`         |
| Equal heights               | `[1, 8, 6, 2, 5, 4, 8, 3, 7]` at `8, 8` | Move either one; neither can do better |
| Extreme values              | `[10^4, 1, 10^4]`                       | `10^4 × 2 = 20000`, fits in `int`      |

## Common Mistakes

- **Using the taller line for height:** water spills over the **shorter** line. Use `min`.
- **Moving the taller line:** the width shrinks, and the height is still capped by the shorter line. You can only lose. Move the shorter one.
- **Width `right - left + 1`:** the width is the distance between the lines, `right - left`, not the number of lines.
- **Confusing it with Trapping Rain Water:** here only **two** lines hold water, and the lines in between don't matter (they don't block anything).

## Comparison

| Approach     | Time     | Space | Note                                     |
| ------------ | -------- | ----- | ---------------------------------------- |
| Brute force  | O(n²)    | O(1)  | Too slow for n = 10⁵                     |
| Two pointers | **O(n)** | O(1)  | Start wide, always move the shorter line |

## Pattern Takeaway

- **"Best pair" + "the answer depends on both ends" → try two pointers from both ends.**
- **Start with the widest option, then shrink.** Each step, ask which end can't possibly help anymore, and drop it.
- **Greedy needs a reason:** here it's "the shorter line already gave its best container". Always be able to say why the skipped options can't win.

## Practice Next

| Problem                                                                                               | Difficulty | How it relates                                               |
| ----------------------------------------------------------------------------------------------------- | ---------- | ------------------------------------------------------------ |
| [Valid Palindrome](https://leetcode.com/problems/valid-palindrome/)                                   | Easy       | Two pointers from both ends, the simplest version            |
| [Two Sum II - Input Array Is Sorted](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/) | Medium     | Two pointers from both ends; move based on the sum           |
| [3Sum](https://leetcode.com/problems/3sum/) ([#009](../009-3sum/))                                    | Medium     | Two pointers inside a loop                                   |
| [Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)                             | Hard       | Same "move the shorter side" idea, but every bar holds water |

## Interview Follow-ups

- **"Prove the greedy is correct."** → When `height[left] <= height[right]`, every container `(left, k)` with `k < right` is narrower and no taller than `(left, right)`. So `left` can't be in a better container. Drop it.
- **"What if heights are equal?"** → Move either one. Both are capped at the same height, and any container between them is narrower.
- **"Return the two indices, not the area."** → Save `left` and `right` whenever `best` improves.
- **"Can you skip faster?"** → After moving, keep moving while the new line is no taller than the one you dropped. Those lines can't do better. Same O(n), fewer area checks.

## TL;DR

- `left = 0`, `right = n - 1`.
- Area = `min(height[left], height[right]) * (right - left)`. Keep the max.
- Move the **shorter** line inward.
- O(n) time, O(1) space.
