# 🚀 Regex Matcher

This program is designed to match strings against regular expressions, offering a way to validate your calculations.

---

## 🛠️ Features

- ✅ **Custom Regex Parser**: Parses and evaluates regex patterns with precision.  
- 🔍 **Matching Capability**: Matches strings against regex patterns.  
- 📋 **Examples Included**: A set of test cases is provided to demonstrate how it works.  

---

## 📝 Usage

1. **Clone the repository**:
   ```bash
   git clone https://github.com/xirzo/regex.git
   cd regex
   ```
2. **Build the project**:
   - Run:
     ```bash
     mkdir build
     cd build
     cmake ..
     make
     ```
3. **Run the program**:
   ```bash
   ./regex_matcher
   ```

---

## 🧪 Example

Here’s a sample regex used in the program:

```text
(a|.|-)(a|.|-)*@((a*.*a)|a)((a*.*a)|a)*
```

### Cases:

| **Regex**                                  | **Input**         | **Result**   |
|-------------------------------------------|-------------------|--------------|
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@aaaaaaa`    | ✅ Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@aaa...aaa`  | ✅ Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@a.a.a.a`    | ✅ Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@.a.a.a`     | ✅ Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@.....a`     | ✅ Match      |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@.....`      | ❌ No Match   |
| `(a\|.\|-)(a\|.\|-)*@((a*.*a)\|a)((a*.*a)\|a)*` | `aaaa@aaaa....`   | ❌ No Match   |

