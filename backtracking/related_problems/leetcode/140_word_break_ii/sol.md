**Time Complexity:** *O(?)*, **Space Complexity:** *O(?)*.

```cpp
class Solution {
private:
    void wordBreak(string &s, int start, unordered_set<string> &words, vector<string> &current, vector<string> &results) {
        if(start == s.size()) {
            string d;
            for(string &x: current) {
                if(!d.empty()) d += " ";
                d += x;
            }
            results.push_back(d);
            return;
        }

        for(int i=start; i<s.size(); i++) {
            string ss = s.substr(start, i - start + 1);
            if(words.count(ss)) {
                current.push_back(ss);
                wordBreak(s, i+1, words, current, results);
                current.pop_back();
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        vector<string> results;
        vector<string> current;
        unordered_set<string> words(wordDict.begin(), wordDict.end());
        wordBreak(s, 0, words, current, results);
        return results;
    }
};
```