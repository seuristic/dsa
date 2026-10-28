# Video: Maximum Product Subarray

## Title Options

1. Maximum Product Subarray: Why You Need the Minimum Too | Blind 75 #6
2. Maximum Product Subarray: When Negatives Flip the Answer | Blind 75 #6
3. Maximum Product Subarray: Kadane's Algorithm with a Twist | Blind 75 #6

## YouTube Description

```text
Maximum Product Subarray (LeetCode 152) explained step by step in C++, from O(n³) brute force to an O(n) solution that tracks both the max and the min.

What you'll learn:
• Brute force: multiply every subarray from scratch. O(n³) time, O(1) space
• Running product: fix the start, extend the end. O(n²) time, O(1) space
• Track max and min: Kadane, but negatives can turn the smallest product into the largest. O(n) time, O(1) space
• Why plain Kadane fails: on -2, 3, -4 it returns 3 instead of 24
• Edge cases: zeros, one number, odd number of negatives, big products
• The pattern: signs can flip order → keep both extremes

Problem: https://leetcode.com/problems/maximum-product-subarray/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/006-maximum-product-subarray
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

Min Becomes Max
