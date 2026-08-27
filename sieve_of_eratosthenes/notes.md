# Sieve of Eratosthenes
An algorithm used to efficiently find all prime numbers up to a given limit ``n`.

# Classic Problem: 
**[TDPRIMES - Printing some primes (SPOJ)](https://www.spoj.com/problems/TDPRIMES/)**

# Related Problems:

# Core Idea
The key observation is:

> If a number `x` is composite, then it has at least one prime factor `≤ √x`.

So we start from `2`, the first prime, and **mark all of its multiples as composite.**

Then we move to the next unmarked number. It is prime, so we mark all of its multiples.

For example:
```
2 → mark 4, 6, 8, 10, 12, ...

3 → mark 6, 9, 12, 15, ...

5 → mark 10, 15, 20, 25, ...
```

We only need to perform this process while:
```
i² ≤ n
```
because every composite number `≤ n` must have a factor `≤ √n`.

## Why start marking from `i²`?

For a prime `i`:
```
i × 2
i × 3
...
i × (i - 1)
```
have already been marked by smaller prime factors.

Therefore, the first multiple that may still be unmarked is:
```
i × i
```
So we start with:
```
j = i * i;
```

# Structure and Images

# Implementation (Classic Problem)
```cpp
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
```

# Notes (Important Lines)


# Complexity
Time: O(n.loglogn)

Space: O(n)

