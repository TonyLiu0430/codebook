// public indices are 0-based
struct bit {
    using ll = long long;
    vector<ll> t;
    bit(int n) : t(n + 1) {}

    void add(int p, ll x) {
        for (++p; p < ssize(t); p += p & -p) t[p] += x;
    }
    ll prefix(int r) { // [0, r]
        ll ans = 0;
        for (++r; r > 0; r -= r & -r) ans += t[r];
        return ans;
    }
    ll sum(int l, int r) { // [l, r]
        return l > r ? 0 : prefix(r) - (l ? prefix(l - 1) : 0);
    }
};
