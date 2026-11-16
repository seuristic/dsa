# Video: Climbing Stairs

## Title Options

1. Climbing Stairs: It's Just Fibonacci in Disguise | Blind 75 #16
2. Climbing Stairs: Your First Dynamic Programming Problem | Blind 75 #16
3. Climbing Stairs: Recursion to Memo to O(1) Space | Blind 75 #16

## YouTube Description

```text
Climbing Stairs (LeetCode 70) explained step by step in C++, from O(2^n) recursion to an O(n) time, O(1) space dynamic programming solution.

What you'll learn:
• Plain recursion: ways(n) = ways(n - 1) + ways(n - 2). O(2^n) time, O(n) space
• Memoization: same recursion, save each answer. O(n) time, O(n) space
• Tabulation: fill a dp array from small to big. O(n) time, O(n) space
• Two variables: keep only the last two answers. O(n) time, O(1) space
• The key insight: think about the last move, 1 step or 2 steps, and it turns into Fibonacci
• Edge cases: n = 1, n = 2, n = 45 just fits in int
• The pattern: count the ways to reach the end → DP on the last move, then recursion → memo → table → variables

Problem: https://leetcode.com/problems/climbing-stairs/
Notes + C++ code: https://github.com/seuristic/dsa/tree/main/yt/016-climbing-stairs
Blind 75 list on LeetCode: https://leetcode.com/problem-list/027rn1u6/

#leetcode #blind75 #dsa
```

## Thumbnail Text

It's Fibonacci!
