# Backtracking
Backtracking is a systematic way of exploring all possible choices by building a solution step by step. At each step, we make a choice, recursively explore the resulting state, and then undo the previous choice before trying the next choice.

## Classic Problem 
**[ Generate all binary strings (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/generate-all-binary-strings/1)**

## Related Problems
| #   | Problem | Platform | Solution | Redo |
|----:|:-------:|:--------:|:--------:|:----:|
| 01. | **[Generate Binary Strings Without Adjacent Zeros](https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/description/)** | **LeetCode** | [:link:](related_problems/leetcode/3211_generate_binary_strings_without_adjacent_zeros/sol.md) | 🟡 Review |
| 02. | **[Subsets](https://leetcode.com/problems/subsets/description/)** | **LeetCode** | [:link:](related_problems/leetcode/78_subsets/sol.md) | 🟡 Review |
| 03. | Generate all permutations | | | |
| 04. | Generate all combinations | | | |
| 05. | Combination Sum | | | |
| 06. | Maze / Grid Backtracking | | | |
| 07. | N-Queens | | | |


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

## Notes (Important Lines)
1. `i` represents the position currently being decided.
2. `s[i] = choice` makes a choice for the current position.
3. `binaryStrings(i + 1, s, results)` explores all possibilities after that choice.
4. When `i == s.size()`, the string is complete, so we add a copy to `results`.
5. No explicit undo/reset is required here because `s[i]` is overwritten by the next choice.

## Complexity
**Time Complexity**: *O(n × 2<sup>n</sup>)* <br>
There are `2ⁿ` binary strings, and copying each complete string into `results` takes `O(n)`. <br>

**Space Complexity**: *O(n)* auxiliary space <br>
- `O(n)` for the current string.
- `O(n)` recursion stack. <br>
The output itself requires `O(n × 2ⁿ)` space.