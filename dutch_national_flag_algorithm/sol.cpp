#include<bits/stdc++.h>
using namespace std;

void three_way_partition(vector<int> &nums, int mid) {
    int n, i, j, k;
    n = nums.size();
    i = j = 0;
    k = n - 1;
    while(j <= k) {
        if(nums[j] < mid) {
            swap(nums[i], nums[j]);
            i++;
            j++;
        } else if(nums[j] > mid) {
            swap(nums[j], nums[k]);
            k--;
        } else { /* nums[j] == mid */
            j++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin>>n;
    vector<int> nums(n);
    for(int &x: nums) cin>>x;
    int mid = 1;
    three_way_partition(nums, mid);
    return 0;
}