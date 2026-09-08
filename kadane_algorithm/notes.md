# Kadane's Algorithm
Kadane's Algorithm is a dynamic programming technique used to find the maximum sum of a contiguous subarray in O(n) time and O(1) extra space.

The key idea is to maintain the maximum subarray sum ending at the current position. At every element, either extend the previous subarray or start a new one.

## Classic Problem 
**[Maximum Subarray (Leetcode)](https://leetcode.com/problems/maximum-subarray/description/)**

## Related Problems

## Core Idea
For every element x, there are only two possibilities:
1. Start a new subarray at x
2. Extend the previous subarray by adding x

Therefore:

*curr = max(x, curr + x);*

Where:

curr = maximum sum of a subarray ending at the current element
best = maximum subarray sum found so far

The recurrence is: ***curr = max(x, curr + x)***

<!-- $$\text{curr} = \max(x,\ \text{curr} + x)$$ -->

If the previous curr is negative, extending it only makes the sum smaller, so we start a new subarray.

## Implementation

### Implementation 1 (Classic Problem) - Empty Subarray **NOT** Allowed
Use this when the subarray must contain **at least one element.**
```cpp
class Solution {
private:
public:
    int maxSubArray(vector<int>& nums) {
        int best = nums[0];
        int curr = nums[0];
        for(int i=1; i<nums.size(); i++) {
            curr = max(nums[i], curr + nums[i]);
            best = max(best, curr);
        }
        return best;
    }
};
```

### Implementation 2 - Empty Subarray Allowed
Use this when choosing **no element** is allowed.
```cpp
class Solution {
private:
public:
    int maxSubArray(vector<int>& nums) {
        int best = 0;
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
curr represents the best subarray ending at the current position, while best represents the best subarray seen anywhere so far

3. Why `curr` starts at `0`
In Implementation 2
```cpp
int curr = 0;
``

This works because the first iteration computes:
```cpp
curr = max(nums[0], 0 + nums[0]);
```
which becomes:
```cpp
curr = nums[0];
```
So the first element is handled correctly.

4. Why `best` starts at `0` when empty subarray is allowed
If the empty subarray is allowed, the answer can never be less than `0`.

For example:
```
[-5, -2, -8]
```
The best non-empty subarray is `[-2]` with sum `-2`.

But because the empty subarray is allowed:
```
answer = 0
```
Therefore:
```
int best = 0;
```
is appropriate.

5. Why best starts at `nums[0]` when empty subarray is NOT allowed

If the subarray must contain at least one element, initializing `best` to `0` would be incorrect for an all-negative array.

For:
```
[-5, -2, -8]
```
the correct answer is:
```
-2
```
Therefore, we initialize:
```
int best = nums[0];
int curr = nums[0];
```
This ensures that at least one element is selected.

## Empty Subarray — Quick Rule
|         Condition          | `curr`  | `best`  |	 All-negative input   |
|:---------------------------|--------:|--------:|-----------------------:|
| Empty subarray NOT allowed | nums[0] | nums[0] | Maximum negative value |
| Empty subarray allowed     | 0       | 0       | 0                      |

**Example**
```
nums = [-5, -2, -8]

Empty not allowed:

answer = -2

Empty allowed:

answer = 0
```

## Complexity
**Time Complexity**: *O(n)* <br>
**Space Complexity**: *O(1)*