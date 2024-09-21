typedef unsigned __int128 ulll;

ulll power(ulll a, ulll n, ulll m) {
    ulll re = 1;
    while (n > 0) {
        if (n & 1) re = re * a % m;
        a = a * a % m;
        n >>= 1;
    }
    return re;
}

ulll inv(ulll a, ulll m) {
    return power(a, m - 2, m);
}

struct Rh {
    const ulll p, mod;
    vector<ulll> ps{1};
    Rh(ulll p, ulll mod) : p(p), mod(mod) {}
    vector<ulll> build(const string &s) {
        vector<ulll> h(s.size() + 1);
        h[0] = 0;
        ps.resize(s.size() + 1);
        for (int i = 0; i < s.size(); i++) {
            ps[i + 1] = ps[i] * p % mod;
            h[i + 1] = (h[i] + s[i] * ps[i + 1] % mod) % mod;
        }
        return h;
    }
    ulll subhash(const vector<ulll> &h, int l, int r) {
        // [l, r] 指原字串
        return ((h[r + 1] - h[l]) * inv(ps[l], mod)) % mod;
    }
};