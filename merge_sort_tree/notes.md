# Merge Sort Tree

# Classic Problem: 
[K Query (SPOJ)] ()

# Related Problems:
├── Count elements > X
├── Count elements < X
├── Range frequency
├── K-th smallest
└── Combine with coordinate compression


# Core Idea

# Structure and Images

# Implementation (Classic Problem)
```cpp
#include<bits/stdc++.h>
using namespace std;

class MergeSortTree {
    private:
    vector<vector<int>> seg_tree;
    int n;
    void build(int node, vector<int> &nums, int left, int right) {
        if(left == right) {
            seg_tree[node] = vector<int>(1, nums[left]);
            return;
        }
        int mid = left + ((right - left)>>1);
        build(2*node + 1, nums, left, mid);
        build(2*node + 2, nums, mid + 1, right);
        merge(
            seg_tree[2*node + 1].begin(), seg_tree[2*node + 1].end(), 
            seg_tree[2*node + 2].begin(), seg_tree[2*node + 2].end(), 
            back_inserter(seg_tree[node])
        );
    }
    int query(int node, int ql, int qr, int k, int left, int right) {
        if(qr < left || ql > right) {
            return 0; /* No overlap with the query range, so there are no elements greater than k to count; therefore, count is 0. */
        }
        if(left >= ql && right <= qr) {
            /*
                seg_tree[node] vector is sorted.
                upper_bound(k) => first element > k.
                end() - upper_bound(k) => number of elements > k.
                Equivalent to distance(upper_bound(k), end()).
           */
            return seg_tree[node].end() - upper_bound(seg_tree[node].begin(), seg_tree[node].end(), k); 
        }
        int mid = left + ((right - left)>>1);
        int a = query(2*node + 1, ql, qr, k, left, mid);
        int b = query(2*node + 2, ql ,qr, k, mid + 1, right);
        return a + b; /* Add counts from the left and right subsegments to get the total number of elements greater than k */
    }
    public:
    MergeSortTree(vector<int> &nums) {
        n = nums.size();
        seg_tree.resize(4 * n);
        build(0, nums, 0, n - 1);
    }
    int query(int ql, int qr, int k) {
        return query(0, ql, qr, k, 0, n - 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<int> nums(n);
    for(int &x: nums) cin>>x;

    MergeSortTree mergeSortTree(nums);
    
    int q; cin>>q;
    while(q--) {
        int i, j, k; cin>>i>>j>>k;
        int ans = mergeSortTree.query(i-1, j-1, k); /* Convert query indices i and j from 1-based to 0-based indexing */
        cout<<ans<<"\n";
    }

    return 0;
}
```

# Notes (Important Lines)
1. ```cpp merge( seg_tree[2*node + 1].begin(), seg_tree[2*node + 1].end(), seg_tree[2*node + 2].begin(), seg_tree[2*node + 2].end(), back_inserter(seg_tree[node]) );```
2.

# Complexity

