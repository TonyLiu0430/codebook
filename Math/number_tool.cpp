using ll = long long;

ll mod_power(ll a, ll n, ll mod) {
    ll ans = 1;
    for (; n; n /= 2, a = (__int128)a * a % mod)
        if (n & 1) ans = (__int128)ans * a % mod;
    return ans;
}

// mod must be prime and n < mod
struct combinations {
    ll mod;
    vector<ll> fact, inv_fact;
    combinations(int n, ll mod) : mod(mod), fact(n + 1, 1), inv_fact(n + 1) {
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
        inv_fact[n] = mod_power(fact[n], mod - 2, mod);
        for (int i = n; i; --i) inv_fact[i - 1] = inv_fact[i] * i % mod;
    }
    ll choose(int n, int k) const {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[k] % mod * inv_fact[n - k] % mod;
    }
};
