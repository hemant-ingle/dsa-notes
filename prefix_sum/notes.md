# Prefix Sum
A technique used to precompute cumulative sums so that the sum of any contiguous subarray/range can be calculated in **O(1)** time.

## Classic Problem 
**[CSUMQ - Cumulative Sum Query (SPOJ)](https://www.spoj.com/problems/CSUMQ/)**

## Related Problems
- Range Sum Query - Immutable (LeetCode 303)
- Subarray Sum Equals K (LeetCode 560)
- Continuous Subarray Sum (LeetCode 523)
- Product of Array Except Self (related prefix/suffix idea)
- Find Pivot Index (LeetCode 724)
- Running Sum of 1d Array (LeetCode 1480)

## Core Idea

Prefix Sum stores the cumulative sum of elements from the beginning of the array.

```
prefix[i] = v[0] + v[1] + ... + v[i]
```

Once the prefix sums are built, any range `sum [i, j]` can be obtained by subtracting two cumulative sums:

```
sum(i...j) = prefix[j] - prefix[i-1]
```

Why?

```
prefix[j]     = v[0] + v[1] + ... + v[i-1] + v[i] + ... + v[j]
prefix[i-1]   = v[0] + v[1] + ... + v[i-1]

difference    =                              v[i] + ... + v[j]
```

So the expensive work is done once during preprocessing, allowing every range-sum query to be answered in O(1).

The key pattern is:

> **Precompute cumulative information → subtract the unwanted prefix.**

## Implementation (Classic Problem)
```cpp
#include<bits/stdc++.h>
using namespace std;


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin>>N;
    vector<int> v(N);
    for(int &x: v) cin>>x;

    vector<int> prefix_sum(N);
    prefix_sum[0] = v[0];
    for(int i=1; i<N; i++) {
        prefix_sum[i] = prefix_sum[i-1] + v[i];
    }

    int Q; cin>>Q;
    
    while(Q--) {
        int i, j; cin>>i>>j;
        int ans = prefix_sum[j] - (i > 0 ? prefix_sum[i - 1] : 0);
        cout<<ans<<"\n";
    }
    
    return 0;
}
```

## Notes (Important Lines)

**1. Build the prefix sum**

```cpp
prefix_sum[i] = prefix_sum[i - 1] + v[i];
```

**2. Calculate a range sum**
```cpp
prefix_sum[j] - prefix_sum[i - 1]
```

`prefix_sum[j]` contains everything from `0` to `j`.

Subtracting `prefix_sum[i - 1]` removes everything before `i`.

**3. Handle the first index**
```cpp
prefix_sum[j] - (i > 0 ? prefix_sum[i - 1] : 0)
```
If `i == 0`, there is no prefix before the range, so subtract `0`.

**4. The most important idea**
```
             unwanted          required
        ┌──────────────┬──────────────────┐
Array:  │  0 ... i-1   │      i ... j     │
        └──────────────┴──────────────────┘
                         ↑_______________↑
                                 |
                     prefix[j] - prefix[i-1]
```
Think of prefix sum as:

> **"Get a large sum, then remove the part I don't need."**

## Complexity
**Preprocessing Time Complexity:** *O(n)*
**Each Query:** *O(1)*
**Total Time Complexity:** *O(n + q)*, where `n` is the array size and `q` is the number of queries.
**Space Complexity:** *O(n)*