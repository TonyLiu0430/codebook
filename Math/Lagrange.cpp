// needs power, mod from BerlekampMassey.cpp
// y[i] = f(i) in [0, mod) for i in [0, n), deg f < n
ll lagrange(const vector<ll> &y, ll x) {
    int n = y.size();
    x %= mod;
    vector<ll> pre(n + 1, 1), suf(n + 1, 1), fact(n, 1);
    for (int i = 0; i < n; ++i)
        pre[i + 1] = pre[i] * ((x - i + mod) % mod) % mod;
    for (int i = n - 1; i >= 0; --i)
        suf[i] = suf[i + 1] * ((x - i + mod) % mod) % mod;
    for (int i = 1; i < n; ++i)
        fact[i] = fact[i - 1] * i % mod;
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll t = y[i] * pre[i] % mod * suf[i + 1] % mod;
        ll d = fact[i] * fact[n - 1 - i] % mod;
        t = t * power(d, mod - 2) % mod;
        if ((n - 1 - i) % 2) t = (mod - t) % mod;
        ans = (ans + t) % mod;
    }
    return ans;
}
