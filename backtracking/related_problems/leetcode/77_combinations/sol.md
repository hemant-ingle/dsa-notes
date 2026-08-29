# [←](/backtracking/notes.md) [Combinations](https://leetcode.com/problems/combinations/description/)

## Backtracking Flow

`choices` :arrow_right: `constraint` :arrow_right: `make choice`:arrow_right: `recurse` :arrow_right: `undo choice`

For subsets:
```
choices     → choose an element from start onward
constraint  → only choose elements after the current start to avoid duplicate combinations
make choice → add the chosen element to current
recurse     → move start to i + 1
undo choice → remove the chosen element from current
```


## Solution
```cpp
class Solution {
private:
    void backtrack(int start, int end, int k, vector<int> &current, vector<vector<int>> &results) {
        if(current.size() == k) {
            results.push_back(current);
            return;
        }

        for(int i = start; i <= end; i++) {
            current.push_back(i);
            backtrack(i + 1, end, k, current, results);
            current.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> results;
        vector<int> current;
        backtrack(1, n, k, current, results);
        return results;
    }
};
```

## Complexity
**Time Complexity:** *O(k × C(n, k))* <br>
There are `C(n, k)` combinations, and copying each complete combination into results takes `O(k)` time.<br>
**Space Complexity:** *O(k)* <br>
The recursion depth is at most `k`, and current stores at most `k` elements.<br>
**Output Space:** *O(k × C(n, k))* <br>
There are `C(n, k)` combinations, each containing `k` elements. <br>
**Total Space Complexity:** *O(k × C(n, k))* including the output.
