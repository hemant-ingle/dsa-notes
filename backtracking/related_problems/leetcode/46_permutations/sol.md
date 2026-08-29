# [←](/backtracking/notes.md) [Permutations](https://leetcode.com/problems/permutations/description/)

## Backtracking Flow

`choices` :arrow_right: `constraint` :arrow_right: `make choice`:arrow_right: `recurse` :arrow_right: `undo choice`

For subsets:
```
choices     → choose any unused element
constraint  → element must not already be used
make choice → add the chosen element to current mark the element as used
recurse     → choose the next element
undo choice → remove the element from current mark the element as unused
```


## Solution
```cpp
class Solution {
private:
    void backtrack(vector<int> &nums, vector<int> &current,
                 unordered_set<int> &used, vector<vector<int>> &results) {
        if (current.size() == nums.size()) {
            results.push_back(current);
            return;
        }

        for (int num : nums) {
            if (used.count(num)) {
                continue;
            }
            /* Make choice */
            current.push_back(num);
            used.insert(num);

            /* Recurse */
            backtrack(nums, current, used, results);

            /* Undo choice */
            current.pop_back();
            used.erase(num);
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> results;
        vector<int> current;
        unordered_set<int> seen;
        backtrack(nums, current, seen, results);
        return results;
    }
};
```

## Complexity
**Time Complexity:** *O(n × n!)* <br>
There are `n!` permutations, and copying each complete permutation into `results` takes `O(n)` time.<br>
**Space Complexity:** *O(n)* <br>
The recursion depth is `n`, and `current` and `seen` each require `O(n)` auxiliary space.<br>
**Output Space:** *O(n × n!)* <br>
There are `n!` permutations, each containing `n` elements.* <br>
**Total Space Complexity:** *O(n × n!)* including the output.
