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