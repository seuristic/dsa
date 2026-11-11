# Video: Counting Bits

## Title Options

1. Counting Bits: Reuse the Answer for i / 2 | Blind 75 #13
2. Counting Bits: Drop the Last Bit, Reuse the Rest | Blind 75 #13
3. Counting Bits: From O(n log n) to O(n) with One Line of DP | Blind 75 #13

## YouTube Description

```text
Counting Bits (LeetCode 338) explained step by step in C++, from O(n log n) brute force to an O(n) one-pass DP solution.

What you'll learn:
• Count each number: run Number of 1 Bits for every i from 0 to n. O(n log n) time, O(1) extra space
• DP with i shifted right by 1: ans[i] = ans[i / 2] + last bit of i. O(n) time, O(1) extra space
• The key insight: i / 2 has the same bits as i minus the last one, and its answer is already computed
• Another formula: ans[i] = ans[i AND (i - 1)] + 1, using the trick from Number of 1 Bits
• Edge cases: n = 0, powers of 2, all ones
• The pattern: answer for every number from 0 to n → DP, reuse a smaller number's answer

Problem: https://leetcode.com/problems/counting-bits/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/013-counting-bits
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

Reuse i / 2
