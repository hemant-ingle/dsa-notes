## Complexity
**Time Complexity:** *O(2<sup>n</sup>)* <br>
**Space Complexity:** *O(n)* <br>
**Output Space:** *O(n x 2<sup>n</sup>) <br>

## Backtracking Flow

`choices` :arrow_right: `constraint` :arrow_right: `make choice`:arrow_right: `recurse`

## Solution
```cpp
class Solution {
private:
    void binaryStrings(string &s, int i, vector<string> &results) {
        if(i == s.size()) {
            results.push_back(s);
            return;
        }
        vector<char> choices{'0', '1'};
        for(auto choice: choices) {
            if(i > 0 &&  s[i-1] == '0' && choice == '0') {
                continue;
            }
            s[i] = choice;
            binaryStrings(s, i+1, results);
        }
    }
public:
    vector<string> validStrings(int n) {
        vector<string> results;
        string s(n, ' ');
        binaryStrings(s, 0, results);
        return results;
    }
};
```