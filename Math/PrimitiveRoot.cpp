// needs mod_power from number_tool.cpp; p is an odd prime
ll primitive_root(ll p) {
    vector<ll> f;
    ll n = p - 1;
    for (ll i = 2; i * i <= n; ++i) if (n % i == 0) {
        f.push_back(i);
        while (n % i == 0) n /= i;
    }
    if (n > 1) f.push_back(n);
    for (ll g = 2;; ++g)
        if (ranges::all_of(f, [&](ll q) {
                return mod_power(g, (p - 1) / q, p) != 1;
            })) return g;
}
