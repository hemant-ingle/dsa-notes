# Kahn's Algorithm
A BFS technique to find topological sort of a DAG

# Classic Problem: 
**[Maximum Subarray (Leetcode)](https://leetcode.com/problems/maximum-subarray/description/)**

# Related Problems:

# Core Idea

# Structure and Images

# Implementation (Classic Problem)
```cpp
class Solution {
private:
    const int INF = 1e9;
public:
    int maxSubArray(vector<int>& nums) {
        int best = -INF;
        int curr = 0;
        for(int x: nums) {
            curr = max(x, curr + x);
            best = max(best, curr);
        }
        return best;
    }
};
```

# Notes (Important Lines)


# Complexity
Time: O(n)

Space: O(1)

