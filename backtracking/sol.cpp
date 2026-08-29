class Solution {
    private:
    void binaryStrings(int i, string &s, vector<string> &results) {
        if(i == s.size()) {
            results.push_back(s); /* insert a copy of s string to results vector */
            return;
        }
        vector<char> choices{'0', '1'};
        for(auto choice: choices) {
            s[i] = choice;
            binaryStrings(i + 1, s, results);
        }
    }
    public:
    vector<string> binstr(int n) {
        vector<string> results;
        string s(n, ' '); /* n spaces */
        binaryStrings(0, s, results);
        return results;
    }
};