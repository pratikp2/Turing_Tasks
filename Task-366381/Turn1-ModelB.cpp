 #include<bits/stdc++.h>
 using namespace std;
 
 #define MAX 100000
 long long int fact[MAX+5];
 long long int mod = 1000000007;
 
 // function to calculate nCr % p
 long long int nCr(int n, int r)
 {
 	long long int ans = 1;
 	if (r > n/2)
 		r = n - r;
 
 	for (int i = 0; i < r; i++)
 	{
 		ans = (ans * (n - i)) % mod;
 		ans = (ans * power(i + 1, mod - 2)) % mod;
 	}
 	return ans;
 }
  // Function to calculate (base^power)%mod
 long long int power(long long int base, long long int power)
 {
 	long long int ans = 1;
 	while (power)
 	{
 		if (power & 1)
 			ans = (ans * base) % mod;
 		base = (base * base) % mod;
 		power >>= 1;
 	}
 	return ans;
 }
  // Function to calculate n! % p
 void factMod(long long int p)
 {
 	fact[0] = fact[1] = 1;
 	for (int i = 2; i <= MAX; i++)
 		fact[i] = (fact[i - 1] * i) % p;
 }
  int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

   factMod(mod); // Calculate factorial modulo 'mod' for all n from 0 to MAX

   int t;
   cin >> t;
   while (t--)
   {
       int n, r;
       cin >> n >> r;

       if (n < 0 || r < 0)
       {
           cout << 0 << "\n";
           continue;
       }
       
 	   cout << nCr(n, r) << "\n";
   }
    return 0;
}
 