// 擴展 BSGS 離散對數：求最小 x >= 0 使 a^x ≡ b (mod m)，
// m 不必是質數，O(sqrt(m))。
// 先不斷除掉 gcd(a,m) 化成互質情形，再用大步小步 (hash
// 表) 碰撞。無解回傳 -1。
using ll = long long;

// smallest x >= 0 with a^x = b (mod m); m need not be prime; -1 if none
// baby-step giant-step, O(sqrt(m))
ll discrete_log(ll a, ll b, ll m) {
    a %= m, b %= m;
    ll k = 1 % m, add = 0;
    for (ll g; (g = gcd(a, m)) > 1;) {
        if (b == k) return add;
        if (b % g) return -1;
        b /= g, m /= g, ++add;
        k = (__int128)k * (a / g) % m;
    }
    if (b == k) return add;
    // now k * a^x = b (mod m) with gcd(a, m) = 1
    ll n = sqrtl(m) + 1, an = 1;
    unordered_map<ll, ll> seen;
    for (ll q = 0, cur = b; q < n; ++q)
        seen[cur] = q, cur = (__int128)cur * a % m;
    for (int i = 0; i < n; ++i) an = (__int128)an * a % m;
    for (ll p = 1, cur = k; p <= n; ++p) {
        cur = (__int128)cur * an % m;
        if (auto it = seen.find(cur); it != seen.end())
            return n * p - it->second + add;
    }
    return -1;
}
