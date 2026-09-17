// range add, range sum; public ranges are [l, r]
struct lazy_sum {
    int n;
    vector<long long> sum, tag;
    lazy_sum(int n) : n(n), sum(4 * max(1, n)), tag(sum.size()) {
        assert(n > 0);
    }

    void apply(int o, int l, int r, long long v) {
        sum[o] += v * (r - l);
        tag[o] += v;
    }
    void push(int o, int l, int r) {
        if (!tag[o]) return;
        int m = (l + r) / 2;
        apply(o * 2, l, m, tag[o]);
        apply(o * 2 + 1, m, r, tag[o]);
        tag[o] = 0;
    }
    void add(int ql, int qr, long long v, int o, int l, int r) {
        if (ql <= l && r <= qr) return apply(o, l, r, v);
        push(o, l, r);
        int m = (l + r) / 2;
        if (ql < m) add(ql, qr, v, o * 2, l, m);
        if (m < qr) add(ql, qr, v, o * 2 + 1, m, r);
        sum[o] = sum[o * 2] + sum[o * 2 + 1];
    }
    long long query(int ql, int qr, int o, int l, int r) {
        if (ql <= l && r <= qr) return sum[o];
        push(o, l, r);
        int m = (l + r) / 2;
        long long ans = 0;
        if (ql < m) ans += query(ql, qr, o * 2, l, m);
        if (m < qr) ans += query(ql, qr, o * 2 + 1, m, r);
        return ans;
    }
    void add(int l, int r, long long v) {
        if (l <= r) add(l, r + 1, v, 1, 0, n);
    }
    long long query(int l, int r) {
        return l <= r ? query(l, r + 1, 1, 0, n) : 0;
    }
};
