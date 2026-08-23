# Kadane's Algorithm
Kadane's Algorithm is a dynamic programming technique used to find the maximum sum of a contiguous subarray in O(n) time and O(1) extra space.

The key idea is to maintain the maximum subarray sum ending at the current position. At every element, either extend the previous subarray or start a new one.

## Classic Problem 
**[Maximum Subarray (Leetcode)](https://leetcode.com/problems/maximum-subarray/description/)**

## Related Problems
1. 

## Core Idea
For every element x, there are only two possibilities:
1. Start a new subarray at x
2. Extend the previous subarray by adding x

Therefore:

*curr = max(x, curr + x);*

Where:

curr = maximum sum of a subarray ending at the current element
best = maximum subarray sum found so far

The recurrence is:

$$\text{curr} = \max(x,\ \text{curr} + x)$$

If the previous curr is negative, extending it only makes the sum smaller, so we start a new subarray.

## Implementation (Classic Problem)
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

## Notes (Important Lines)
1. ```curr = max(x, curr + x)```
This is the core of Kadane's Algorithm.

It answers:
> Should I continue the previous subarray or start a new subarray here?

2. ```best = max(best, curr)```
curr represents the best subarray ending here, while best represents the best subarray seen anywhere so far

3. Why `curr` starts at `0`
This works because the first iteration computes:
```cpp
curr = max(nums[0], 0 + nums[0]);
```
which becomes:
```cpp
curr = nums[0];
```
So the implementation also correctly handles all-negative arrays.

For example:
```
[-5, -2, -8]

curr:
-5 → -2 → -8

best = -2
```

4. Why `best` starts at `-INF`
We cannot initialize best to 0, because the answer can be negative.

For:
```
[-5, -2, -8]
```
he correct answer is `-2` not `0`.

## Complexity
**Time Complexity**: *O(n)*
**Space Complexity**: *O(1)*