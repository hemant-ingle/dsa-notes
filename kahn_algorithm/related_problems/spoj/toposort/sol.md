**[SPOJ ~ TOPOSORT - Topological Sorting](https://www.spoj.com/problems/TOPOSORT/)**

```cpp
#include<bits/stdc++.h>
using namespace std;

vector<int> topological_sort(int V, vector<vector<int>> &adj) {
    vector<int> indegrees(V + 1, 0);

    for(int i=1; i<=V; i++) {
        for(int x: adj[i]) {
            indegrees[x]++;
        }
    }

    priority_queue<int, vector<int>, greater<int>> _queue;

    for(int i=1; i<=V; i++) {
        if(indegrees[i] == 0) {
            _queue.push(i);
        }
    }

    vector<int> topo;

    while(!_queue.empty()) {
        int vertex = _queue.top();
        _queue.pop();

        topo.push_back(vertex);

        for(int x: adj[vertex]) {
            indegrees[x]--;
            if(indegrees[x] == 0) {
                _queue.push(x);
            }
        }
    }

    if(topo.size() != V) return {};
    return topo;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; cin>>n>>m;
    vector<vector<int>> adj(n+1, vector<int>());
    while(m--) {
        int u, v; cin>>u>>v;
        adj[u].push_back(v);
    }

    vector<int> topo = topological_sort(n, adj);
    if(topo.empty()) {
        cout<<"Sandro fails.\n";
    } else {
        for(int x: topo) cout<<x<<" ";
        cout<<"\n";
    }
    return 0;
}
```