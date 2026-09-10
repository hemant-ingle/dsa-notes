**Time Complexity:** *O(?)*, **Space Complexity:** *O(?)*.

```cpp
class Solution {
private:
    void letterCombinations(string &digits, int pos, vector<string> &mappings, string &current, vector<string> &results) {
        if(pos == digits.size()) {
            results.push_back(current);
            return;
        }

        for(char c: mappings[digits[pos] - '0']) {
            current.push_back(c);
            letterCombinations(digits, pos+1, mappings, current, results);
            current.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        vector<string> results;
        string current;
        vector<string> mappings {
            "", "", "abc", "def",
            "ghi", "jkl", "mno",
            "pqrs", "tuv", "wxyz"
        };
        letterCombinations(digits, 0, mappings, current, results);
        return results;
    }
};
```