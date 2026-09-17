// range add, range maximum; public ranges are [l, r]
struct segtree {
    struct node { long long mx = 0, lazy = 0; };
    int n;
    vector<node> t;

    segtree(int n) : n(n), t(4 * max(1, n)) { assert(n > 0); }
    void apply(int o, long long v) { t[o].mx += v, t[o].lazy += v; }
    void push(int o) {
        if (!t[o].lazy) return;
        apply(o * 2, t[o].lazy);
        apply(o * 2 + 1, t[o].lazy);
        t[o].lazy = 0;
    }
    void add(int ql, int qr, long long v, int o, int l, int r) {
        if (ql <= l && r <= qr) return apply(o, v);
        push(o);
        int m = (l + r) / 2;
        if (ql < m) add(ql, qr, v, o * 2, l, m);
        if (m < qr) add(ql, qr, v, o * 2 + 1, m, r);
        t[o].mx = max(t[o * 2].mx, t[o * 2 + 1].mx);
    }
    long long max_query(int ql, int qr, int o, int l, int r) {
        if (ql <= l && r <= qr) return t[o].mx;
        push(o);
        int m = (l + r) / 2;
        long long ans = LLONG_MIN;
        if (ql < m) ans = max(ans, max_query(ql, qr, o * 2, l, m));
        if (m < qr) ans = max(ans, max_query(ql, qr, o * 2 + 1, m, r));
        return ans;
    }
    void add(int l, int r, long long v) {
        if (l <= r) add(l, r + 1, v, 1, 0, n);
    }
    long long max_query(int l, int r) {
        assert(l <= r);
        return max_query(l, r + 1, 1, 0, n);
    }
};
