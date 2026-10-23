---
name: yt-problem
argument-hint: <problem link | problem name | pasted statement>
description: Generate a complete YouTube-ready problem folder in yt/ for a DSA problem — student README (problem, intuition, brute → optimal approaches, dry run, patterns, practice), a recording script (video.md), and tested C++ solutions. Use when the user shares a DSA problem (link, name, or pasted statement) and wants a video folder / notes / README for it, or says /yt-problem.
---

# yt-problem

Build `yt/NNN-problem-slug/` for one DSA problem. Goal: a student who reads the README never needs another resource for this problem, and can solve similar problems later. Write in simple, short sentences. No jargon without a one-line explanation.

## 1. Understand the problem first

- **Known problem** (LeetCode/Codeforces/GFG link or well-known name): use the official statement, constraints, and examples. Fetch the link if you are unsure of exact details.
- **Unknown problem**: you need the full statement, constraints, and at least one example. If any are missing, ask the user before writing anything. Never guess constraints — they decide the target complexity.
- Know the full solution path (brute → optimal) and _why_ each step improves before writing.

## 2. Create the folder

- `NNN` = highest existing number in `yt/` + 1, zero-padded to 3 digits (`001`, `002`, …).
- `problem-slug` = kebab-case problem name, e.g. `005-longest-substring-without-repeating`.

Files:

| File                            | Audience     | Notes                                                       |
| ------------------------------- | ------------ | ----------------------------------------------------------- |
| `README.md`                     | Students     | Linked in the video description                             |
| `video.md`                      | Creator only | Recording script + YouTube metadata                         |
| `brute.cpp`                     | Both         | Simplest correct solution                                   |
| `better1.cpp`, `better2.cpp`, … | Both         | One file per meaningful middle step, in order; skip if none |
| `optimal.cpp`                   | Both         | Best known solution                                         |

## 3. C++ files

Match the repo style (`.clang-format`, Google-based, 2-space indent):

```cpp
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  ...
};

int main() {
  assert(...);
  cout << "All tests passed\n";
}
```

- **No comments at all** in `.cpp` files — no header, no inline, no test labels. All explanation lives in the README.
- LeetCode: `class Solution` with the exact official signature (students can paste it). Otherwise: a plain function taking inputs as arguments and returning the answer.
- `main()` runs the statement's examples first, then edge cases.
- Each file is self-contained and compiles on its own.
- Same tests in every file so they can be compared on camera.
- Use `long long` wherever sums/products can overflow.

**Verify every file** with the user's `run` shell function (from `~/.zshrc`; compiles with `g++-15 -std=c++17 -O2 -Wall` and runs):

```
cd yt/NNN-problem-slug && for f in *.cpp; do run "$f"; done
```

If `run` is unavailable, use `g++-15 -std=c++17 -O2 -Wall <file> -o a.out && ./a.out`. All files must print `All tests passed` with no warnings. For non-trivial optimal solutions, also stress-test optimal against brute on random small inputs in a scratch file (do not commit it).

## 4. README.md (student-facing)

Use these sections, in order. Keep each tight — bullets and tables over paragraphs.

```markdown
# NNN. <Problem Title>

**Difficulty:** Easy/Medium/Hard · **Tags:** array, two pointers, …
**Problem:** <link> · **Video:** <link — leave as TODO>

## Problem in Simple Words

<2–4 plain sentences. What is given, what to return.>

## Examples

<input → output, each with a one-line "why".>

## Constraints → What They Tell Us

<List constraints, then: "n ≤ 10⁵ → O(n²) too slow (10¹⁰ ops), need O(n log n) or better.">

## Prerequisites

<Concepts needed, one line each. Link ../../algorithms/<x>/code.cpp when relevant.>

## How to Think About It

<The key observation and how someone would discover it on their own — the questions to ask yourself.>

## Approach 1: Brute Force

- **Idea:** …
- **Why it works:** …
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(…), Space O(…)
- **Why it's not enough:** <the exact bottleneck → leads to next approach>

## Approach 2: Better (one section per betterN.cpp, in order; skip if none)

<same bullets>

## Approach N: Optimal

<same bullets, minus "why it's not enough">

## Dry Run (Optimal)

<Step-by-step table on one example: each row = one step, columns = key variables. ASCII art or a mermaid diagram for trees/graphs.>

## Edge Cases

<Each case + what the code does with it.>

## Common Mistakes

<Off-by-one, overflow, wrong initialization, missed case — specific to this problem.>

## Comparison

| Approach | Time | Space | Note |

## Pattern Takeaway

<"When you see <signal>, think <technique>." The reusable lesson for other problems.>

## Practice Next

<3–5 related problems, easiest first, with links and one line on how each relates.>

## Interview Follow-ups

<Likely variations and how the solution changes.>

## TL;DR

<3–5 lines for quick revision.>
```

## 5. video.md (creator-only)

```markdown
# Video: <Problem Title>

## Title Options

<3 options, clear and searchable.>

## Hook (first 30 sec)

<What to say to make viewers stay — the problem's twist or why it matters.>

## Recording Flow

<Chapter by chapter, matching README order. For each: talking points (bullets) + what to draw on the whiteboard + which file to show.>

## YouTube Description

<Short summary, chapter timestamps (00:00 placeholders), problem link, repo folder link.>

## Tags

<Comma-separated.>

## Thumbnail Text

<2–4 words.>
```

## 6. Update the index

Append a row to the table in `yt/README.md`:

```
| NNN | [Problem Title](NNN-problem-slug/) | `topic`, `topic` | TODO |
```

Topic: 1–2 lowercase keywords, each in backticks, comma-separated (e.g. `` `array`, `two pointers` ``).

If the problem is in the Blind 75 section, replace its `—` in the Folder column with `[NNN](NNN-problem-slug/)`.

## 7. Format Markdown

After creating or editing any `.md` file (problem `README.md`, `video.md`, `yt/README.md`), format it with Prettier so table columns line up with their widest cell:

```
npx --yes prettier@3 --write yt/NNN-problem-slug/*.md yt/README.md
```

Re-run it after every later edit to these files — changing one cell can change a whole column's width.

## 8. Finish

Report the folder path, the approaches written with their complexities, and the test results. Don't commit unless asked.
