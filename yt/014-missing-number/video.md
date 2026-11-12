# Video: Missing Number

## Title Options

1. Missing Number: Every Number Cancels Out But One | Blind 75 #14
2. Missing Number: Sum Formula vs XOR | Blind 75 #14
3. Missing Number: Why XOR Beats the Sum Formula | Blind 75 #14

## YouTube Description

```text
Missing Number (LeetCode 268) explained step by step in C++, from O(n²) brute force to an O(n) time, O(1) space XOR solution.

What you'll learn:
• Brute force: check every number from 0 to n against the array. O(n²) time, O(1) space
• Seen array: mark each number, find the unmarked one. O(n) time, O(n) space
• Sum formula: n(n + 1) / 2 minus the sum of the array. O(n) time, O(1) space
• XOR: XOR all indexes, n, and all values, so pairs cancel and the missing number is left. O(n) time, O(1) space
• Why XOR beats the sum: the sum grows like n squared and can overflow, XOR never can
• Edge cases: missing 0, missing n, a single element
• The pattern: every number appears twice except one → XOR everything

Problem: https://leetcode.com/problems/missing-number/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/014-missing-number
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

x ^ x = 0
