#define ll long long int

long long int fact[1001];
long long int dp[1001][1001];

// taken from https://www.geeksforgeeks.org/calculate-stirling-numbers-which-represents-the-number-of-ways-to-arrange-r-objects-around-n-different-circles/
void stirlingNumber(int r, int n, int m) { 
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][i] = 1;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= r; j++) {
            dp[i][j] = (dp[i - 1][j - 1] + j * dp[i - 1][j] % m) % m;
        }
    }
 }

// taken from https://cp-algorithms.com/algebra/binary-exp.html
long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Taken from https://codeforces.com/topic/79406/en2
ll inv(ll a, ll p){
    return binpow(a, p-2, p);
}

ll nCk(ll n, ll k, ll p){
    if (k == 1) return n;
    return (fact[n] * inv(fact[k], p) % p) * inv(fact[n-k], p) % p;
}

class Solution {
public:
    int numberOfWays(int n, int x, int y) {
        int mod = 1e9 + 7;
        fact[0] = 1;
        for (int i = 1; i <= 1000; i++) {
            fact[i] = (fact[i-1] * i) % mod; 
        }
        stirlingNumber(1000, 1000, mod);
        long long int ans = 0;
        for (int i = 1; i <= x; i++) {
            ans = ans + binpow(y, i, mod) * nCk(x, i, mod) % mod * dp[n][i] % mod * fact[i] % mod;
            ans %= mod;
        }
        return ans;
    }
};

/*

total ways to score is the same across all different permutations


n!
total ways to score => y^n

number of permutations of n given x spots

n = 5
x = 1
=> P(n, x)

n = 1
x = 5
=> P(n, x)
<=> P(x, n)

a b c
=>
a b
a c
b a
b c
c a
c b

4 

a b c


27
3 => 3! * 4^3
3! * 4^2
3! * 4^1

3 * 4 + 18 * 16 + 6 * 64

x^(n-1)

*/