// mod must be prime; give about 2L terms for order L
using ll = long long;
const ll mod = 998244353;

ll power(ll a, ll n) {
    ll ans = 1;
    for (a %= mod; n; n /= 2, a = a * a % mod)
        if (n & 1) ans = ans * a % mod;
    return ans;
}

// returns c: s[i] = sum c[j] * s[i - 1 - j]
vector<ll> berlekamp_massey(const vector<ll> &s) {
    int n = s.size(), L = 0, m = 0;
    vector<ll> C(n + 1), B(n + 1), T;
    C[0] = B[0] = 1;
    ll b = 1;
    for (int i = 0; i < n; ++i) {
        ++m;
        ll d = s[i] % mod;
        for (int j = 1; j <= L; ++j)
            d = (d + C[j] * s[i - j]) % mod;
        if (!d) continue;
        T = C;
        ll coef = d * power(b, mod - 2) % mod;
        for (int j = m; j <= n; ++j)
            C[j] = (C[j] + (mod - coef) * B[j - m]) % mod;
        if (2 * L > i) continue;
        L = i + 1 - L, B = T, b = d, m = 0;
    }
    vector<ll> c(L);
    for (int j = 0; j < L; ++j)
        c[j] = (mod - C[j + 1]) % mod;
    return c;
}

// k-th term (0-based), s: first L terms, O(L^2 log k)
ll linear_rec(vector<ll> s, vector<ll> c, ll k) {
    int n = c.size();
    auto mul = [&](vector<ll> a, vector<ll> b) {
        vector<ll> r(2 * n + 1);
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                r[i + j] = (r[i + j] + a[i] * b[j]) % mod;
        for (int i = 2 * n; i > n; --i)
            for (int j = 0; j < n; ++j) {
                ll &t = r[i - 1 - j];
                t = (t + r[i] * c[j]) % mod;
            }
        r.resize(n + 1);
        return r;
    };
    vector<ll> pol(n + 1), e(n + 1);
    pol[0] = e[1] = 1;
    for (++k; k; k /= 2) {
        if (k & 1) pol = mul(pol, e);
        e = mul(e, e);
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        ans = (ans + pol[i + 1] * s[i]) % mod;
    return ans;
}
