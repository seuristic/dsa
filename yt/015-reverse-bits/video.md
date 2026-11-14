# Video: Reverse Bits

## Title Options

1. Reverse Bits: Pop from the Right, Push to the Left | Blind 75 #15
2. Reverse Bits: Why Leading Zeros Matter | Blind 75 #15
3. Reverse Bits: From 32 Steps to Just 5 with Masks | Blind 75 #15

## YouTube Description

```text
Reverse Bits (LeetCode 190) explained step by step in C++, from reversing a binary string to bit-by-bit shifting to swapping halves with masks in just 5 steps.

What you'll learn:
• String reverse: turn n into 32 characters, reverse, convert back. O(32) time, O(32) space
• Bit by bit: take the last bit of n, push it onto the result, 32 times. O(32) time, O(1) space
• Mask swaps: swap 16, 8, 4, 2, then 1 bit neighbors across the whole number. 5 steps, O(1) space
• The trap: leading zeros are real bits, so always loop all 32, never stop when n becomes 0
• Follow-up: called many times? Mask swaps or a 256-entry byte lookup table
• Edge cases: zero, small numbers, bit palindromes
• The pattern: reverse with bits = pop with AND 1 and shift right, push with shift left and OR

Problem: https://leetcode.com/problems/reverse-bits/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/015-reverse-bits
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

Pop Right, Push Left
