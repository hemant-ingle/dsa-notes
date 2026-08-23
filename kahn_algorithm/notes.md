# Kahn's Algorithm
A BFS technique to find topological sort of a DAG

# Classic Problem: 
**[Topological Sort (GeeksforGeeks)](https://www.geeksforgeeks.org/problems/topological-sort/1)**

# Related Problems:
1. **[SPOJ ~ TOPOSORT - Topological Sorting](https://www.spoj.com/problems/TOPOSORT/)** [:link:]()


# Core Idea

# Structure and Images

# Implementation (Classic Problem)
```cpp
class Solution {
  private:
  vector<int> topological_sort(int V, vector<vector<int>> &adj) {
      vector<int> indegrees(V, 0);
      
      for(int i=0; i<V; i++) {
          for(int x: adj[i]) {
              indegrees[x]++;
          }
      }
      
      queue<int> _queue;
      
      for(int i=0; i<V; i++) {
          if(indegrees[i] == 0) {
              _queue.push(i);
          }
      }
      
      vector<int> topo;
      
      while(!_queue.empty()) {
          int vertex = _queue.front();
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
  
  public:
    vector<int> topoSort(int V, vector<vector<int>>& edges) {
        
        vector<vector<int>> adj(V, vector<int>());
        for(auto &edge: edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
        }
        
        vector<int> result = topological_sort(V, adj);
        return result;
    }
};
```

# Notes (Important Lines)


# Complexity
Time:

Space: 

