#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int> &nums) {
        int candidate;
        int count = 0;

        for(int x: nums) {
            if(count == 0) {
                candidate = x;
                count = 1; /* count++; */
            } else if(candidate == x) {
                count++;
            } else {
                count--;
            }
        }

        return candidate;
    }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<int> nums(n);
    for(int &x: nums) cin>>x;

    Solution solution;
    int result = solution.majorityElement(nums);
    cout<<result<<"\n";

    return 0;
}