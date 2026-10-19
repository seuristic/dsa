# DSA

C++ implementations of data structures and algorithms, plus notes for my YouTube problem videos.

## Structure

```
algorithms/   reusable implementations
yt/           one folder per video problem
```

## Algorithms

| Name         | Use                                                     | Code                                         |
| ------------ | ------------------------------------------------------- | -------------------------------------------- |
| Fenwick Tree | Range sum queries, point updates                        | [code.cpp](algorithms/fenwick_tree/code.cpp) |
| Segment Tree | Range min/sum queries, range updates (lazy propagation) | [code.cpp](algorithms/segment_tree/code.cpp) |

## YouTube

Each `yt/NNN-problem-slug/` folder has:

- `README.md`: problem, intuition, brute force → optimal, dry run, patterns, practice
- `video.md`: recording script and YouTube details
- `brute.cpp`, `better.cpp`, `optimal.cpp`: tested solutions

See the [index](yt/README.md). New folders are generated with the `/yt-problem` Claude Code skill.

## Build

```
g++ -std=c++17 -O2 -Wall file.cpp && ./a.out
```

Code style: `.clang-format` (Google-based).
