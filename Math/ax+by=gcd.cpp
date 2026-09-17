using ll = long long;

// returns {g, x, y}: ax + by = g = gcd(a,b)
tuple<ll, ll, ll> ext_gcd(ll a, ll b) {
    if (!b) return {abs(a), a < 0 ? -1 : 1, 0};
    ll g, x, y;
    tie(g, x, y) = ext_gcd(b, a % b);
    return {g, y, x - a / b * y};
}
