# 015. Reverse Bits

**Difficulty:** Easy · **Tags:** bit manipulation, divide and conquer

**Problem:** [LeetCode 190](https://leetcode.com/problems/reverse-bits/) · **Video:** TODO

## Problem in Simple Words

You get a number `n`. Write it as **exactly 32 bits** (with leading zeros).
Reverse that 32-bit string: the first bit becomes the last, the last becomes the first.
Return the number those reversed bits make.

## Examples

| `n`          | 32 bits of `n`                     | Reversed                           | Output       |
| ------------ | ---------------------------------- | ---------------------------------- | ------------ |
| `43261596`   | `00000010100101000001111010011100` | `00111001011110000010100101000000` | `964176192`  |
| `2147483644` | `01111111111111111111111111111100` | `00111111111111111111111111111110` | `1073741822` |
| `2`          | `00000000000000000000000000000010` | `01000000000000000000000000000000` | `1073741824` |

The last one shows why **all 32 bits** matter: `2` is just `10`, but reversed as 32 bits it becomes a huge number.

## Constraints → What They Tell Us

- `0 <= n <= 2^31 - 2`
- `n` is even.

What this means:

- **Always 32 bits:** the work is fixed, so every approach is O(1). The question is how many steps it takes and how clean it is.
- **`n` is even → its last bit is `0`:** after reversing, that `0` becomes the top (sign) bit. So the answer is never negative and fits in `int`.
- **Still, work in `unsigned`:** shifting signed numbers has traps in C++. `unsigned` makes every shift safe, then we convert back at the end.

## Prerequisites

- **Binary and 32-bit numbers:** an `int` is 32 bits. Leading zeros count here.
- **`x & 1`:** the last bit of `x`.
- **`x >> 1`:** drop the last bit. **`x << 1`:** make room for a new last bit.
- **`a | b`:** combine bits from two numbers.
- **Hex masks:** `0x55555555` = `0101…01`, `0x33333333` = `0011…0011`, `0x0f0f0f0f` = `00001111…`. Each hex digit is 4 bits.

## How to Think About It

Think of reversing a **stack of plates**, or reversing the digits of a number:

- **Take** the last bit of `n` (`n & 1`), then drop it (`n >>= 1`).
- **Put** it at the end of `result`: first make room (`result << 1`), then add it (`| bit`).

The first bit you take from `n` (its rightmost) gets pushed left 31 more times, so it ends up leftmost. That's the reverse.

Then ask: _"Do I have to move the bits one at a time?"_ No. Reversing a list = swap its two halves, then reverse each half. With masks, we can swap **all** pairs of halves at once:

```
abcdefgh          8 bits as letters
efgh abcd         swap the two halves (4 bits each)
gh ef cd ab       inside each half, swap the 2-bit pairs
hgfedcba          inside each pair, swap the single bits
```

32 bits → swap 16, 8, 4, 2, 1 → **5 steps**.

## Approach 1: Brute Force (String)

- **Idea:** Turn `n` into a 32-character string of `0`/`1` (`bitset<32>(n).to_string()`). Reverse the string. Turn it back into a number.
- **Why it works:** It does exactly what the problem says, with strings.
- **Code:** [brute.cpp](brute.cpp)
- **Complexity:** Time O(32) = O(1), Space O(32) for the string
- **Why it's not enough:** It builds a string just to move bits around. We can move the bits directly with shifts.

## Approach 2: Better (Bit by Bit)

- **Idea:** Repeat 32 times:
  - `result = (result << 1) | (x & 1)` (make room, add the last bit of `x`)
  - `x >>= 1` (drop that bit)
- **Why it works:** Bits leave `x` from the right and enter `result` from the right, so the first one out ends up furthest left.
- **Code:** [better.cpp](better.cpp)
- **Complexity:** Time O(32) = O(1), Space O(1)
- **Why it's not enough:** It's the answer most interviewers expect. But it always takes 32 steps, one per bit. The follow-up asks: called many times, can it be faster? Swapping halves with masks needs only 5 steps.

Trace with 8 bits, `x = 00001101`:

| Step | Bit taken  | `result`   |
| ---- | ---------- | ---------- |
| 1    | 1          | `1`        |
| 2    | 0          | `10`       |
| 3    | 1          | `101`      |
| 4    | 1          | `1011`     |
| 5–8  | 0, 0, 0, 0 | `10110000` |

## Approach 3: Optimal (Swap Halves with Masks)

- **Idea:** Five lines, each swaps neighbors of a certain size, across the whole number at once:

  | Line | Swaps                   | Mask                    |
  | ---- | ----------------------- | ----------------------- |
  | 1    | the two 16-bit halves   | none (`>> 16`, `<< 16`) |
  | 2    | 8-bit neighbors (bytes) | `0x00ff00ff`            |
  | 3    | 4-bit neighbors         | `0x0f0f0f0f`            |
  | 4    | 2-bit neighbors         | `0x33333333`            |
  | 5    | single bits             | `0x55555555`            |

  Each line: `x = ((x >> k) & mask) | ((x & mask) << k)`.
  - `(x & mask) << k`: take the **right** piece of every pair, move it left.
  - `(x >> k) & mask`: take the **left** piece of every pair, move it right.
  - `|` puts them together.

- **Why it works:** Reversing = swap halves, then reverse each half (recursively). After swapping at sizes 16, 8, 4, 2, 1, every bit has moved to its mirrored position.
- **Code:** [optimal.cpp](optimal.cpp)
- **Complexity:** Time O(log 32) = 5 steps, Space O(1)

## Dry Run (Optimal)

Easier to see with 8 bits and letters (3 steps: swap 4, 2, 1). Same idea as 32 bits with 5 steps.

| Step | Swap size | Mask (8-bit) | Before     | After      |
| ---- | --------- | ------------ | ---------- | ---------- |
| 1    | 4         | `00001111`   | `abcdefgh` | `efghabcd` |
| 2    | 2         | `00110011`   | `efghabcd` | `ghefcdab` |
| 3    | 1         | `01010101`   | `ghefcdab` | `hgfedcba` |

Step 2 in detail (`k = 2`, mask `00110011`):

```
x               = e f g h a b c d
(x & mask) << 2 = g h 0 0 c d 0 0     right pieces moved left
(x >> 2) & mask = 0 0 e f 0 0 a b     left pieces moved right
OR              = g h e f c d a b
```

## Edge Cases

| Case                  | Example      | What happens                                                    |
| --------------------- | ------------ | --------------------------------------------------------------- |
| Zero                  | `0`          | All bits `0` → `0`                                              |
| Small number          | `2`          | Bit 1 moves to bit 30 → `1073741824`                            |
| Already a palindrome  | `2147483646` | `0111…110` reads the same both ways → same number               |
| Alternating bits      | `1431655764` | `0101…0100` → `0010…1010` = `715827882`                         |
| Top bit of the result | any even `n` | Last bit is `0`, so the result's sign bit is `0`: fits in `int` |

## Common Mistakes

- **Stopping when `x == 0`:** leading zeros matter. For `n = 2`, stopping early gives `1` instead of `1073741824`. Always do **32** steps.
- **Shifting in the wrong order:** shift `result` **before** adding the bit. Adding first and shifting after moves the last bit one place too far.
- **Signed shifts:** `>>` on a negative `int` copies the sign bit, and `<<` into the sign bit is undefined before C++20. Work in `unsigned`.
- **Wrong masks:** `0x55555555` (`0101`), `0x33333333` (`0011`), `0x0f0f0f0f` (`00001111`), `0x00ff00ff`. Mixing them up swaps the wrong pieces.
- **Reversing only the "real" digits:** `bitset<32>` keeps the leading zeros. Building the string with your own loop until `n == 0` doesn't.

## Comparison

| Approach       | Time              | Space | Note                                       |
| -------------- | ----------------- | ----- | ------------------------------------------ |
| String reverse | O(32)             | O(32) | Easy to write, builds a string             |
| Bit by bit     | O(32)             | O(1)  | Pop from `n`, push onto `result`, 32 times |
| Mask swaps     | **O(log 32) = 5** | O(1)  | Swap 16, 8, 4, 2, 1 bits at once           |

## Pattern Takeaway

- **"Reverse" with bits → pop with `x & 1`, `x >>= 1`; push with `(result << 1) | bit`.** Same as reversing the digits of a number with `% 10` and `* 10`.
- **Fixed-size bit problems: always loop the full width.** Leading zeros are real bits.
- **Masks like `0x55555555` let you work on every bit pair at once.** Divide and conquer across the whole word in O(log bits).
- **"Called many times?" → precompute** (a table for every byte) or use the mask trick.

## Practice Next

| Problem                                                                                                   | Difficulty | How it relates                                  |
| --------------------------------------------------------------------------------------------------------- | ---------- | ----------------------------------------------- |
| [Number of 1 Bits](https://leetcode.com/problems/number-of-1-bits/) ([#012](../012-number-of-1-bits/))    | Easy       | Same `& 1` and `>> 1` walk through the bits     |
| [Number Complement](https://leetcode.com/problems/number-complement/)                                     | Easy       | Flip bits instead of reversing; masks again     |
| [Binary Number with Alternating Bits](https://leetcode.com/problems/binary-number-with-alternating-bits/) | Easy       | Compare neighboring bits                        |
| [Reverse Integer](https://leetcode.com/problems/reverse-integer/)                                         | Medium     | Same pop/push, with decimal digits and overflow |

## Interview Follow-ups

- **"Called many times, how to optimize?"** →
  - Mask swaps: 5 steps instead of 32.
  - Or a lookup table: precompute the reverse of every byte (256 entries). Split `n` into 4 bytes, reverse each with the table, and put them back in **opposite order**.
- **"Reverse only the lowest k bits?"** → Same loop, `k` times instead of 32.
- **"Is the bit pattern a palindrome?"** → Check `reverseBits(n) == n`.
- **"What about 64 bits?"** → Loop 64 times, or add one more mask step (swap 32-bit halves first).

## TL;DR

- Work in `unsigned`, loop all 32 bits.
- `result = (result << 1) | (x & 1); x >>= 1;`
- Faster: swap halves of size 16, 8, 4, 2, 1 with masks: 5 steps.
- O(1) time and space either way.
