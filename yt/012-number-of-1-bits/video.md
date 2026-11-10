# Video: Number of 1 Bits

## Title Options

1. Number of 1 Bits: The n & (n - 1) Trick | Blind 75 #12
2. Number of 1 Bits: Skip the Zeros, Count Only the Ones | Blind 75 #12
3. Number of 1 Bits: Brian Kernighan's Trick Explained | Blind 75 #12

## YouTube Description

```text
Number of 1 Bits (LeetCode 191) explained step by step in C++, from checking every bit to the n AND (n - 1) trick that only does one step per 1 bit.

What you'll learn:
• Check every bit: read the last bit with n AND 1, then shift right. O(number of bits) time, O(1) space
• n AND (n - 1): remove the lowest 1 bit each step. O(number of 1 bits) time, O(1) space
• Why it works: n - 1 flips the lowest 1 and every 0 after it, so AND clears exactly that 1
• Follow-up: called many times? A 256-entry lookup table, or the built-in popcount
• Edge cases: powers of 2, all ones, alternating bits
• The pattern: n AND (n - 1) removes the lowest set bit, and equals 0 only for powers of 2

Problem: https://leetcode.com/problems/number-of-1-bits/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/012-number-of-1-bits
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

n & (n − 1)
