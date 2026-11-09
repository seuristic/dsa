# Video: Sum of Two Integers

## Title Options

1. Sum of Two Integers: Add Without Plus Using XOR and AND | Blind 75 #11
2. Sum of Two Integers: How Computers Really Add | Blind 75 #11
3. Sum of Two Integers: XOR Is the Sum, AND Is the Carry | Blind 75 #11

## YouTube Description

```text
Sum of Two Integers (LeetCode 371) explained step by step in C++: add two numbers without using + or -, from bit-by-bit addition to the XOR + carry trick.

What you'll learn:
• Bit by bit: school addition in binary, one column at a time with a carry. O(32) time, O(1) space
• XOR + carry: XOR adds every bit without carries, AND finds the carries, shift them left and repeat. O(32) time, O(1) space
• Why it stops: the carry moves at least one bit left every round, so at most 32 rounds
• The C++ trap: shifting a negative int left is undefined behavior before C++20, so cast to unsigned
• Edge cases: zeros, negative numbers, mixed signs, -1 + 1 taking all 32 rounds
• The pattern: no arithmetic allowed → think bits. a + b = (a XOR b) + (a AND b, shifted left by 1)

Problem: https://leetcode.com/problems/sum-of-two-integers/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/011-sum-of-two-integers
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

No + Allowed
