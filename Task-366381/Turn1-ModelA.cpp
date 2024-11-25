#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Compute modular inverse using extended Euclidean algorithm
long long modInv(long long a, long long mod) {
    long long tmp_mod = mod;
    long long x0 = 0, x1 = 1;
    
    if (mod == 1) return 0;
    
    while (a > 1) {
        long long q = a / tmp_mod;
        long long t = tmp_mod;
        tmp_mod = a % tmp_mod;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += tmp_mod;
    return x1;
}

// Precompute factorials and their modular inverses
void precompute(long long n, long long mod) {
    fact.assign(n + 1, 1);
    inv_fact.assign(n + 1, 0);
    
    for (int i = 2; i <= n; ++i) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    
    inv_fact[n] = modInv(fact[n], mod);
    
    for (int i = n - 1; i >= 1; --i) {
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % mod;
    }
}

// Calculate C(n, r) using precomputed factorials and inverses
long long comb(long long n, long long r, long long mod) {
    if (r > n) return 0;
    return (fact[n] * inv_fact[r] * inv_fact[n - r]) % mod;
}

int main() {
    long long n = 100;  // Maximum value for combinations
    long long mod = 1e9 + 7;  // A large prime number
    
    precompute(n, mod);
    
    // Example usage
    long long r = 20;
    long long result = comb(n, r, mod);
    cout << "C(" << n << ", " << r << ") mod " << mod << " = " << result << endl;
    
    return 0;
}