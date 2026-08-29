# Backtracking
Backtracking is a systematic way of exploring all possible choices by building a solution step by step. At each step, we make a choice, recursively explore the resulting state, and then undo the previous choice before trying the next choice.

## Classic Problem 
**[ Generate all binary strings (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/generate-all-binary-strings/1)**

## Related Problems
| #   | Problem | Platform | Solution | Redo |
|----:|:-------:|:--------:|:--------:|:----:|
| 01. | **[Generate Binary Strings Without Adjacent Zeros](https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/description/)** | **LeetCode** | [:link:](related_problems/leetcode/3211_generate_binary_strings_without_adjacent_zeros/sol.md) | 🟡 |
| 02. | **[Subsets](https://leetcode.com/problems/subsets/description/)** | **LeetCode** | [:link:](related_problems/leetcode/78_subsets/sol.md) | 🟡 |
| 03. | **[Permutations](https://leetcode.com/problems/permutations/description/)** | **LeetCode** | [:link:](related_problems/leetcode/46_permutations/sol.md) | 🟡 |
| 04. | **[Combinations](https://leetcode.com/problems/combinations/description/)** | **LeetCode** | [:link:](related_problems/leetcode/77_combinations/sol.md) | 🟡 |
| 05. | **[Combination Sum](https://leetcode.com/problems/combination-sum/description/)** | **LeetCode** | [:link:](related_problems/leetcode/39_combination_sum/sol.md) | 🟡 |
| 06. | **[Maze / Grid Backtracking]()** | **** | [:link:](related_problems/leetcode//sol.md) | 🟡 |
| 07. | **[Unique Paths](https://leetcode.com/problems/unique-paths/description/)** | **LeetCode** | [:link:](related_problems/leetcode/62_unique_paths/sol.md) | 🟡 |
| 08. | **[N-Queens](https://leetcode.com/problems/n-queens/description/)** | **LeetCode** | [:link:](related_problems/leetcode/51_n_queens/sol.md) | 🟡 |
| 09. | **[Generate Parentheses](https://leetcode.com/problems/generate-parentheses/description/)** | **LeetCode** | [:link:](related_problems/leetcode/22_generate_parentheses/sol.md) | 🟡 |

## Core Idea
At every position, there are two possible choices:

```
                ""
              /    \
            0        1
           / \      / \
         00  01   10  11
```
For a binary string of length n, we make exactly n decisions, and each decision has two choices.

The general pattern is:
```
Choose
  ↓
Explore recursively
  ↓
Choose the next option
```
The important part is that the same string can be reused. We modify the current position before making the recursive call.

## Implementation (Classic Problem)
### Implementaion 1
```cpp
class Solution {
    private:
    void binaryStrings(string &s, int i, vector<string> &results) {
        if(i == s.size()) {
            results.push_back(s); /* insert a copy of s string to results vector */
            return;
        }
        vector<char> choices{'0', '1'};
        for(auto choice: choices) {
            s[i] = choice;
            binaryStrings(s, i + 1, results);
        }
    }
    public:
    vector<string> binstr(int n) {
        vector<string> results;
        string s(n, ' '); /* n spaces */
        binaryStrings(s, 0, results);
        return results;
    }
};
```

### Implementaion 2
```cpp
/*
Backtracking Flow: 
    choices → constraint → make choice → recurse → undo

choices     → '0' / '1'
constraint  → none
make choice → current.push_back(choice)
recurse     → i + 1
undo        → current.pop_back()
*/

class Solution {
    private:
    void binaryStrings(int n, int i,string &current, vector<string> &results) {
        if(i == n) {
            results.push_back(current);
            return;
        }
        
        /* Take '0' */
        current.push_back('0'); /* make choice */
        binaryStrings(n, i+1, current, results); /* recurse */
        current.pop_back(); /* undo choice */
        
        current.push_back('1'); /* make choice */
        binaryStrings(n, i+1, current, results); /* recurse */
        current.pop_back(); /* undo choice */ /* very important */
    }
    public:
    vector<string> binstr(int n) {
        vector<string> results;
        string current;
        binaryStrings(n, 0, current, results);
        return results;
    }
};
```

## Notes (Important Lines)
### Implementation 1
1. `i` represents the position currently being decided.
2. `s[i] = choice` makes a choice for the current position.
3. `binaryStrings(i + 1, s, results)` explores all possibilities after that choice.
4. When `i == s.size()`, the string is complete, so we add a copy to `results`.
5. No explicit undo/reset is required here because `s[i]` is overwritten by the next choice.

### Implementation 2
1. `i` represents the number of positions already decided.
2. current stores the partial string built so far.
3. `current.push_back('0')` makes the choice `0`.
4. `binaryStrings(n, i + 1, current, results)` recursively explores all strings that can be formed after choosing `0`.
5. `current.pop_back()` undoes the `0` choice, restoring `current` to the state it had before that choice.
6. `current.push_back('1')` makes the next choice `1`.
7. The recursive call explores all possibilities after choosing `1`.
8. The final `current.pop_back()` undoes the `1` choice. This is important because the function must restore `current` before returning to its caller.
9. When `i == n`, all `n` positions have been decided, so `current` represents a complete binary string and we add a copy to `results`.
10. The key backtracking pattern is:
```
make choice
    ↓
recurse
    ↓
undo choice
```

For this problem, the recursion tree is essentially:
```
              ""
           /      \
         "0"      "1"
        /  \      /  \
      "00" "01" "10" "11"
       ...         ...
```
**The important distinction between the two implementations:**

- **Implementation 1:** modifies a fixed position → the next choice overwrites the previous choice, so explicit undo is unnecessary.
- **Implementation 2:** grows the string using push_back() → the previous choice remains in the string, so it must be explicitly removed using pop_back().

So the real lesson is:
> **Backtracking requires restoring the state whenever your choice permanently changes the shared state.**

## Complexity
**Time Complexity**: *O(n × 2<sup>n</sup>)* <br>
There are `2ⁿ` binary strings, and copying each complete string into `results` takes `O(n)`. <br>

**Space Complexity**: *O(n)* auxiliary space <br>
- `O(n)` for the current string.
- `O(n)` recursion stack. <br>
The output itself requires `O(n × 2ⁿ)` space.