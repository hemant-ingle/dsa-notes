**Time Complexity:** *O(?)*, **Space Complexity:** *O(?)*.


```cpp
class Solution {
private:
    void generateParenthesis(int n, int open, int close, string &current, vector<string> &results) {
        if(open == n && close == n) {
            results.push_back(current);
            return;
        }

        if(open < n) {
            current.push_back('(');
            generateParenthesis(n, open+1, close, current, results);
            current.pop_back();
        }

        if(close < open) {
            current.push_back(')');
            generateParenthesis(n, open, close+1, current, results);
            current.pop_back();
        }
    }
public:
    vector<string> generateParenthesis(int n) {
        vector<string> results;
        string current;
        generateParenthesis(n, 0, 0, current, results);
        return results;
    }
};
```