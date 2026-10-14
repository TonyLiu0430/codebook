// needs ext_gcd from ax+by=gcd.cpp
// x = r[i] (mod m[i]), moduli need not be coprime; lcm must fit in ll
// returns {x, lcm} with 0 <= x < lcm, nullopt if no solution
optional<pair<ll, ll>> crt(const vector<ll> &r, const vector<ll> &m) {
    ll x = 0, l = 1;
    for (int i = 0; i < ssize(r); ++i) {
        auto [g, p, q] = ext_gcd(l, m[i]);
        ll d = (r[i] % m[i] + m[i]) % m[i] - x;
        if (d % g) return nullopt;
        ll mg = m[i] / g, k = (__int128)(d / g % mg) * p % mg;
        ll nl = l / g * m[i];
        x = ((x + (__int128)l * k) % nl + nl) % nl;
        l = nl;
    }
    return pair{x, l};
}
