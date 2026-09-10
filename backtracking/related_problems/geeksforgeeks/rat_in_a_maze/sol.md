**Time Complexity:** *O(?)*, **Space Complexity:** *O(?)*.

```cpp
class Solution {
  private:
    void ratInMaze(vector<vector<int>> &maze, int i, int j, vector<vector<bool>> &visited,string &current, vector<string> &results) {
        int n = maze.size();
        if(i < 0 || i >= n || j < 0 || j >= n || maze[i][j] == 0 || visited[i][j]) {
            return;
        }
        if(i == n - 1 && j == n - 1) {
            results.push_back(current);
            return;
        }
        
        visited[i][j] = true;
        
        current.push_back('D');
        ratInMaze(maze, i+1, j, visited, current, results);
        current.pop_back();

        current.push_back('L');
        ratInMaze(maze, i, j-1, visited, current, results);
        current.pop_back();

        current.push_back('R');
        ratInMaze(maze, i, j+1, visited, current, results);
        current.pop_back();

        current.push_back('U');
        ratInMaze(maze, i-1, j, visited, current, results);
        current.pop_back();
        
        visited[i][j] = false;
    }
  public:
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        vector<string> results;
        string current;
        vector<vector<bool>> visited(maze.size(), vector<bool>(maze.size(), false));
        ratInMaze(maze, 0, 0, visited, current, results);
        return results;
    }
};
```