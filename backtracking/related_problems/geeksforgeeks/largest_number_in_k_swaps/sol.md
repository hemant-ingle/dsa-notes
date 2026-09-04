# [←](/backtracking/notes.md) [Largest Number in K Swaps](https://www.geeksforgeeks.org/problems/largest-number-in-k-swaps-1587115620/1)

## Backtracking Flow

For this problem, we build the largest possible number by deciding which position to fix next.
```
choices     → choose an index i > start
constraint  → s[i] must contain the maximum digit from start onward
make choice → swap s[start] with s[i]
recurse     → move to start + 1 and decrease k
undo choice → swap s[start] and s[i] back
```

## Why do we choose the maximum digit?

At position `start`, we want the largest possible digit.

```cpp
char mx = *max_element(s.begin() + start, s.end());
```

If `s[start]` is already `mx`, there is no useful swap to make at this position:

```cpp
if(s[start] == mx) {
    largestInKSwaps(s, start + 1, k, r);
    return;
}
```

Otherwise, we try swapping `s[start]` with every occurrence of `mx`.

This is important because there may be multiple positions containing the same maximum digit, and each choice can produce a different result later.

## Solution
```cpp


class Solution {
  private:
    void largestInKSwaps(string &s, int start, int k, string &r) {
        if(s > r) {
            r = s;
        }
        if(k == 0 || start == s.size() - 1) {
            return;
        }
        
        char mx = *max_element(s.begin() + start, s.end());
        
        if(s[start] == mx) {
            largestInKSwaps(s, start + 1, k, r);
            return;
        }
        
        for(int i=start + 1; i<s.size(); i++) {
            if(s[i] == mx) {
                swap(s[start], s[i]);
                largestInKSwaps(s, start + 1, k - 1, r);
                swap(s[start], s[i]);
            }
        }
    }
  public:
    // Function to find the largest number after k swaps.
    string findMaximumNum(string& s, int k) {
        string r = s;
        largestInKSwaps(s, 0, k, r);
        return r;
    }
};
```

### Example

Consider:
```
s = "129814999"
k = 4
```
At `start = 0`:
```
129814999
^
```
The maximum digit from index `0` onward is `9`.

So we try swapping the first digit `1` with every `9`:
```
929814199
929814919
929814991
```
Each resulting string becomes a separate backtracking branch.

For each branch, we move to the next position and repeat the same process.

The variable `r` always stores the largest string found so far.

### Important Backtracking Idea

We modify the **same string** instead of creating a new string for every branch.
```cpp
swap(s[start], s[i]);

largestInKSwaps(...);

swap(s[start], s[i]);
```
The second swap restores the original state.

This is the standard:
```
make choice
     ↓
recurse
     ↓
undo choice

pattern.
```

### Why `r` Is Needed

We may make a swap that looks good immediately but produces a smaller number later.

Therefore, we cannot simply return the string from the current branch.

Instead:
```cpp
if(s > r) {
    r = s;
}
```
keeps track of the best number encountered across **all branches**.


## Complexity

Let `n` be the length of the string.

### Time Complexity

At each recursive state, we scan the remaining string to find the maximum digit:
```cpp
max_element(...)
```
which takes **O(n)** in the worst case.

The number of recursive states depends on how many occurrences of the maximum digit exist at each position.

A simple worst-case upper bound for the number of branches is:

**O(n<sup>k</sup>)**

Therefore, a safe worst-case bound for this implementation is:

**O(n × n<sup>k</sup>) = O(n<sup>k+1</sup>)**

However, this is a loose upper bound. The actual number of states is usually much smaller because the code only branches on positions containing the maximum digit.

### Space Complexity

The recursion depth is at most `k`.

No new string is created for every recursive call; the algorithm modifies `s` in-place.

Therefore:

**O(k)** auxiliary space.

## Key Takeaways
1. **Fix one position at a time.**
2. At each position, find the **maximum digit** available.
3. If the current digit is already maximum, simply move forward.
4. Otherwise, try swapping with **every occurrence** of the maximum digit.
5. Recursively solve the remaining positions.
6. Undo every swap after recursion.
7. Keep the largest string found in `r`.
```
                 start
                   |
          find maximum digit
                   |
          ┌────────┴────────┐
          |                 |
   already maximum       not maximum
          |                 |
      move forward     try every
                       max position
                           |
                        swap
                           |
                        recurse
                           |
                         undo
```
