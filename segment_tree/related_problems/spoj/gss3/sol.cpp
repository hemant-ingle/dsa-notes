#include<bits/stdc++.h>
using namespace std;

class SegmentTree {
    private:
    struct SegmentTreeNode {
        int sum, pref, suff, ans;
        bool valid;
        SegmentTreeNode(): sum(0), pref(0), suff(0), ans(0), valid(false) {}
        SegmentTreeNode(int val): sum(val), pref(val), suff(val), ans(val), valid(true) {}
    };
    vector<SegmentTreeNode> seg_tree;
    int n;

    SegmentTreeNode combine(SegmentTreeNode &a, SegmentTreeNode &b) {
        if(!a.valid) return b;
        if(!b.valid) return a;
        SegmentTreeNode result;
        result.valid = true;
        result.sum = a.sum + b.sum;
        result.pref = max(a.pref, a.sum + b.pref);
        result.suff = max(b.suff, b.sum + a.suff);
        result.ans = max({a.ans, b.ans, a.suff + b.pref});
        return result;    
    }

    void build(int node, vector<int> &nums, int left, int right) {
        if(left == right) {
            seg_tree[node] = SegmentTreeNode(nums[left]);
            return;
        }
        int mid = left + ((right - left)>>1);
        build(2*node + 1, nums, left, mid);
        build(2*node + 2, nums, mid + 1, right);
        seg_tree[node] = combine(seg_tree[2*node + 1], seg_tree[2*node + 2]);
    }

    void update(int node, int pos, int val, int left, int right) {
        if(left == right) {
            seg_tree[node] = SegmentTreeNode(val);
            return;
        }
        int mid = left + ((right - left)>>1);
        if(pos <= mid) {
            update(2*node + 1, pos, val, left, mid);
        } else {
            update(2*node + 2, pos, val, mid + 1, right);
        }
        seg_tree[node] = combine(seg_tree[2*node + 1], seg_tree[2*node + 2]);
    }

    SegmentTreeNode query(int node, int ql, int qr, int left, int right) {
        if(right < ql || left > qr) {
            return SegmentTreeNode(); // invalid node
        }
        if(left >= ql && right <= qr) {
            return seg_tree[node];
        }
        int mid = left + ((right - left)>>1);
        SegmentTreeNode a = query(2*node + 1, ql, qr, left, mid);
        SegmentTreeNode b = query(2*node + 2, ql, qr, mid + 1, right);
        SegmentTreeNode res = combine(a, b);
        return res;
    }

    public:
    SegmentTree(vector<int> &nums) {
        n = nums.size();
        seg_tree.resize(4*n);
        build(0, nums, 0, n - 1);
    }

    void update(int position, int value) {
        update(0, position, value, 0, n - 1);
    }

    int query(int queryLeft, int queryRight) {
        SegmentTreeNode res = query(0, queryLeft, queryRight, 0, n - 1);
        return res.ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N; cin>>N;
    vector<int> A(N);
    for(int &x: A) cin>>x;
    int M; cin>>M;

    SegmentTree st(A);

    while(M--) {
        int o, x, y; cin>>o>>x>>y;
        if(o == 0) {
            st.update(x - 1, y);
        }
        else if(o == 1) {
            int ans = st.query(x - 1, y - 1);
            cout<<ans<<"\n";
        }
    }

    return 0;
}