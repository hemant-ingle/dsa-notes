#include<bits/stdc++.h>
using namespace std;

class Solution {
private:
    void generate(int n,string &current, vector<int> &results) {
        if(current.size() == n) {
            results.push_back(stoi(current));
            return;
        }

        int start = (current.empty() ? 1 : current.back() - '0' + 1);
        for(int i=1; i<=9; i++) {
            current.push_back(i + '0');
            generate(n, current, results);
            current.pop_back();
        }
    }
public:
    vector<int> increasingNumbers(int n) {
        vector<int> results;
        string current;
        if(n == 1) {
            results.push_back(0);
        }
        generate(n, current, results); 
        return results;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin>>n;

    Solution solution;
    vector<int> results = solution.increasingNumbers(n);
    cout<<"[";
    for(int i=0; i<results.size(); i++) {
        if(i > 0) cout<<" ";
        cout<<results[i];
    }
    cout<<"]\n";
    return 0;
}