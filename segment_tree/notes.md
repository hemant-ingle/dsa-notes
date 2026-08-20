# Segment Tree

# Classic Problem: 
[Dynamic Range Sum Queries (CSES)] (https://cses.fi/problemset/task/1648/)

# Related Problems:


# Core Idea

# Structure and Images

# Implementation (Classic Problem)
```cpp
#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
    private:
    vector<long long int> seg_tree;
    int n;

    void build(int node, vector<int> &nums, int left, int right) {
        if(left == right) {
            seg_tree[node] = nums[left];
            return;
        }
        int mid = left + ((right - left)>>1);
        build(2*node + 1, nums, left, mid);
        build(2*node + 2, nums, mid + 1, right);
        seg_tree[node] = seg_tree[2*node + 1] + seg_tree[2*node + 2];
    }

    void update(int node, int pos, int val, int left, int right) {
        if(left == right) {
            seg_tree[node] = val;
            return;
        }
        int mid = left + ((right - left)>>1);
        if(pos <= mid) {
            update(2*node + 1, pos, val, left, mid);
        } else {
            update(2*node + 2, pos, val, mid + 1, right);
        }
        seg_tree[node] = seg_tree[2*node + 1] + seg_tree[2*node + 2];
    }

    long long int query(int node, int ql, int qr, int left, int right) {
        if(right < ql || left > qr) {
            return 0;
        }
        if(left >= ql && right <= qr) {
            return seg_tree[node];
        }
        int mid = left + ((right - left)>>1);
        long long int a = query(2*node + 1, ql, qr, left, mid);
        long long int b = query(2*node + 2, ql, qr, mid + 1, right);
        return a + b;
    }

    public:
    SegmentTree(vector<int> &nums) {
        n = nums.size();
        seg_tree.resize(4*n); // can also be written as seg_tree.assign(4*n, 0);
        build(0, nums, 0, n - 1);
    }

    void update(int pos, int val) {
        update(0, pos, val, 0, n - 1);
    }

    long long int query(int ql, int qr) {
        return query(0, ql, qr, 0, n - 1);
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q; cin>>n>>q;
    vector<int> nums(n);
    for(int &x: nums) cin>>x;

    SegmentTree st(nums);

    while(q--) {
        int qt; cin>>qt;
        if(qt == 1) {
            int k, u; cin>>k>>u;
            st.update(k - 1, u);
        }
        else if(qt == 2) {
            int a, b; cin>>a>>b;
            long long int res = st.query(a - 1, b - 1);
            cout<<res<<"\n";
        }
    }

    return 0;
}
```

# Notes (Important Lines)
1. ```remember the function signature of build, query, and update function```
2. what are left and right parameters.
3. node parameter



# Complexity
Time:
1. Build: O(n),
2. Query: O(logn)
3. Update: O(logn)

Space: O(n)

[Segment Tree Draft](segment_tree_draft.md)