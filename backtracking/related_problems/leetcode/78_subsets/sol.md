# [←](/backtracking/notes.md) [Subsets](https://leetcode.com/problems/subsets/description/)

## Backtracking Flow

`choices` :arrow_right: `constraint` :arrow_right: `make choice`:arrow_right: `recurse`

For subsets:
```
choices     → take / skip
constraint  → usually none
make choice → add nums[i] if taking
recurse     → i + 1
```

For example, with:
```cpp
nums = {1, 2, 3}
```

For subsets, the decision tree should be:
```
                    []
                 /      \
              take 1   skip 1
             /             \
          [1]               []
         /   \             /   \
     take 2  skip 2    take 2  skip 2
     [1,2]    [1]       [2]      []

```
The same decision continues for every element:
> **At each index, decide whether to take the element or skip it.**

## Solution
```cpp
class Solution {
    void subsets(vector<int> &nums, int i, vector<int> &current, vector<vector<int>> &results) {
        if(i == nums.size()) {
            results.push_back(current);
            return;
        }

        /* Take nums[i] */
        current.push_back(nums[i]); /* make choice */
        subsets(nums, i+1, current, results); /* recurse */

        /* Undo */
        current.pop_back(); /* undo choice */

        /* Skip nums[i] */
        subsets(nums, i+1, current, results); /* recurse*/
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> results;
        vector<int> current;
        subsets(nums, 0, current, results);
        return results;
    }
};
```

## Complexity
**Time Complexity:** *O(2<sup>n</sup>)* <br>
**Space Complexity:** *O(n)* <br>
**Output Space:** *O(n x 2<sup>n</sup>)* <br>
