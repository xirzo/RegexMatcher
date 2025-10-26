This program was written to easily check answers for my *Discrete math* homework.

## Build

```sh
git clone https://github.com/xirzo/regexmatcher.git
cd regexmatcher
cmake -B build/
cmake --build build/ 
./build/bin/regex
```

Now you may just edit the `bin/main.cpp` with your *regex* and recompile it.

## Example

Here’s a sample regex used in the program:

```text
(a|.|-)(a|.|-)*@((a*.*a)|a)((a*.*a)|a)*
```

### Cases:

| **Regex**                                  | **Input**         | **Result**   |
|-------------------------------------------|-------------------|--------------|
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@aaaaaaa`    | Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@aaa...aaa`  | Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@a.a.a.a`    | Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@.a.a.a`     | Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@.....a`     | Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@.....`      | No Match   |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@aaaa....`   | No Match   |

