# Video: Search in Rotated Sorted Array

## Title Options

1. Search in Rotated Sorted Array: One Half Is Always Sorted | Blind 75 #8
2. Search in Rotated Sorted Array: Binary Search Without a Sorted Array | Blind 75 #8
3. Search in Rotated Sorted Array: Which Half Is Sorted? | Blind 75 #8

## YouTube Description

```text
Search in Rotated Sorted Array (LeetCode 33) explained step by step in C++, from an O(n) linear scan to an O(log n) one-pass binary search solution.

What you'll learn:
• Brute force: scan every index. O(n) time, O(1) space
• Find the pivot, then binary search: reuse Find Minimum in Rotated Sorted Array. O(log n) time, O(1) space
• One binary search: at every mid, pick the sorted half and check if the target fits. O(log n) time, O(1) space
• Why nums[left] less than or equal to nums[mid]: with only two numbers left, a strict check gives the wrong half
• Edge cases: one number, two numbers, not rotated, target missing
• The pattern: rotated sorted array → one half is always sorted

Problem: https://leetcode.com/problems/search-in-rotated-sorted-array/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/008-search-in-rotated-sorted-array
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

One Half Is Sorted
