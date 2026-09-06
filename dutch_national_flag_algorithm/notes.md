# Dutch National Flag Algorithm
The **Dutch National Flag (DNF) algorithm** is a one-pass, in-place algorithm used to divide an array into three partitions based on a pivot value.

The three partitions are:
```
[ elements < mid ][ elements = mid ][ elements > mid ]
```
It is especially useful when an array contains only **three categories of values.**

## History
The algorithm was introduced by **Edsger W. Dijkstra** and was named after the Dutch national flag, which has three colors:
```
🇳🇱 **Dutch National Flag**

🟥🟥🟥🟥🟥🟥🟥 Red
⬜⬜⬜⬜⬜⬜⬜ White
🟦🟦🟦🟦🟦🟦🟦 Blue
```

The three colors inspired the idea of dividing an array into **three regions**, leading to what we now call **three-way partitioning.**

## Classic Problem 
**[Sort Colors (Leetcode)](https://leetcode.com/problems/sort-colors/description/)**

## Related Problems
- Three-way partitioning
- QuickSort with duplicate elements
- Partitioning an array around a pivot
- Problems involving exactly three categories

## Core Idea

Use **three pointers:**
```
i → boundary of elements < mid
j → current element / boundary of unknown elements
k → boundary of elements > mid
```
The array can be visualized as:
```
[ < mid ][ = mid ][  unknown  ][ > mid ]
    ↑        ↑          ↑           ↑
    i        j          j           k
```
At any point:

- `[0, i-1]` → elements `< mid`
- `[i, j-1]` → elements `= mid`
- `[j, k]` → unknown elements
- `[k+1, n-1]` → elements `> mid`

The algorithm processes the **unknown region** until j > k.

## Implementation (Classic Problem)
```cpp
class Solution {
private:
    void three_way_partition(vector<int> &nums, int mid) {
        int n, i, j, k;
        n = nums.size();
        i = j = 0;
        k = n - 1;
        while(j <= k) {
            if(nums[j] < mid) {
                swap(nums[i], nums[j]);
                i++;
                j++;
            } else if(nums[j] > mid) {
                swap(nums[j], nums[k]);
                k--;
            } else {
                j++;
            }
        }
    }
public:
    void sortColors(vector<int>& nums) {
        three_way_partition(nums, 1);
    }
};
```

## Key Invariant

At every iteration:
```
[0 ... i-1]     < mid
[i ... j-1]     = mid
[j ... k]       unknown
[k+1 ... n-1]   > mid
```
The algorithm's job is simply to **shrink the unknown region** [j, k] until it becomes empty.

## Complexity
**Time Complexity**: *O(n)*
**Space Complexity**: *O(1)*