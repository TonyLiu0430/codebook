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

constexpr uint64_t mod = (1ull<<61) - 1;
uint64_t modmul(uint64_t a, uint64_t b){
	uint64_t l1 = (uint32_t)a, h1 = a>>32, l2 = (uint32_t)b, h2 = b>>32;
	uint64_t l = l1*l2, m = l1*h2 + l2*h1, h = h1*h2;
	uint64_t ret = (l&mod) + (l>>61) + (h << 3) + (m >> 29) + (m << 35 >> 3) + 1;
	ret = (ret & mod) + (ret>>61);
	ret = (ret & mod) + (ret>>61);
	return ret-1;
}