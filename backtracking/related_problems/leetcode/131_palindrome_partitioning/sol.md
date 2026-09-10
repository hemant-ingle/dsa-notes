**Time Complexity:** *O(?)*, **Space Complexity:** *O(?)*
```cpp
class Solution {
private:
    bool is_palindrome(string &s, int x, int y) {
        while(x < y) {
            if(s[x] != s[y]) {
                return false;
            }
            x++;
            y--;
        }
        return true;
    }
    void partition(string &s, int start, vector<string> &current, vector<vector<string>> &results) {
        if(start == s.size()) {
            results.push_back(current);
            return;
        }

        for(int i=start; i<s.size(); i++) {
            if(is_palindrome(s, start, i)) {
                string ss = s.substr(start, i - start + 1);
                current.push_back(ss);
                partition(s, i+1, current, results);
                current.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> results;
        vector<string> current;
        partition(s, 0, current, results);
        return results;
    }
};
```