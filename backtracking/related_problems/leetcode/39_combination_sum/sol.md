**Time Complexity:** *O(?)*, **Space Complexity:** *O(?)*

```cpp
class Solution {
private:
    void combinationSum(vector<int> &candidates, int i, int target, vector<int> &current, vector<vector<int>> &results) {
        if(target < 0 || i == candidates.size()) return;
        if(target == 0) {
            results.push_back(current);
            return;
        }
        current.push_back(candidates[i]);
        combinationSum(candidates, i, target - candidates[i], current, results);
        current.pop_back();
        
        combinationSum(candidates, i+1, target, current, results);
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> results;
        vector<int> current;
        combinationSum(candidates, 0, target, current, results);
        return results;
    }
};
```