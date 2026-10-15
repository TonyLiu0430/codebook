// 擴展歐幾里得：求 ax+by=gcd(a,b) 的一組整數解 (x,y)。
// 用途：求模反元素（gcd(a,m)=1 時 x 即 a^(-1) mod m）、
// 解線性同餘 ax ≡ b (mod m)、exCRT 的基礎。
// 通解：x+k*b/g, y-k*a/g。
using ll = long long;

// returns {g, x, y}: ax + by = g = gcd(a,b)
tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (!b) return {abs(a), a < 0 ? -1 : 1, 0};
    ll g, x, y;
    tie(g, x, y) = ext_gcd(b, a % b);
    return {g, y, x - a / b * y};
}
