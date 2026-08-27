#include<bits/stdc++.h>
using namespace std;

vector<bool> sieve_of_eratosthenes(int n) {
    vector<bool> is_prime(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for(long long int i=2; i*i<=n; i++) {
        if(is_prime[i]) {
            for(long long int j=i*i; j<=n; j+=i) {
                is_prime[j] = false;
            }
        }
    }

    return is_prime;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 1e8;
    vector<bool> is_prime = sieve_of_eratosthenes(N);

    int cnt = 0;
    for(int i=2; i<=N; i++) {
        if(is_prime[i]) {
            cnt++;
            if(cnt % 100 == 1) {
                cout<<i<<"\n";
            }
        }
    }

    return 0;
}