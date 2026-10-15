// 模反元素：快速冪 a^(p-2)（費馬小定理，p 為質數）；
// 以及 O(n) 線性求 1..n 所有反元素：inv[i] =
// -floor(p/i)*inv[p mod i]。
// 模數非質數時改用擴展歐幾里得。
using ll = long long;

ll power(ll a, ll n, ll mod) {
    ll ans = 1;
    for (; n; n /= 2, a = (__int128)a * a % mod)
        if (n & 1) ans = (__int128)ans * a % mod;
    return ans;
}

// mod must be prime; 1 <= n < mod
vector<ll> inverse_table(int n, ll mod) {
    assert(1 <= n && n < mod);
    vector<ll> inv(n + 1);
    inv[1] = 1;
    for (int i = 2; i <= n; ++i)
        inv[i] =
            mod - (__int128)(mod / i) * inv[mod % i] % mod;
    return inv;
}
