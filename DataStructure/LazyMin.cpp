// 區間加值、區間最小值的懶標記線段樹，並支援線段樹上二
// 分：找區間內第一個／最後一個 <= x 的位置。
// range add, range min, segment tree binary search, n >= 1
// public ranges are [l, r]; first/last_le: -1 if none
using ll = long long;

struct lazy_min {
    int n, fl, fr; // fl, fr, fx, rev: arguments of find()
    ll fx;
    bool rev;
    vector<ll> mn, tag;
    lazy_min(const vector<ll> &a)
        : n(a.size()), mn(4 * n), tag(4 * n) {
        build(a, 1, 0, n);
    }
    void pull(int o) {
        mn[o] = min(mn[o * 2], mn[o * 2 + 1]);
    }
    void apply(int o, ll v) { mn[o] += v, tag[o] += v; }
    void push(int o) {
        apply(o * 2, tag[o]), apply(o * 2 + 1, tag[o]);
        tag[o] = 0;
    }
    void build(const vector<ll> &a, int o, int l, int r) {
        if (r - l == 1) return void(mn[o] = a[l]);
        int m = (l + r) / 2;
        build(a, o * 2, l, m), build(a, o * 2 + 1, m, r);
        pull(o);
    }
    void add(int ql, int qr, ll v, int o, int l, int r) {
        if (qr <= l || r <= ql) return;
        if (ql <= l && r <= qr) return apply(o, v);
        push(o);
        int m = (l + r) / 2;
        add(ql, qr, v, o * 2, l, m);
        add(ql, qr, v, o * 2 + 1, m, r);
        pull(o);
    }
    ll query(int ql, int qr, int o, int l, int r) {
        if (qr <= l || r <= ql) return LLONG_MAX;
        if (ql <= l && r <= qr) return mn[o];
        push(o);
        int m = (l + r) / 2;
        return min(query(ql, qr, o * 2, l, m),
                   query(ql, qr, o * 2 + 1, m, r));
    }
    // first (rev: last) i in [fl, fr) with a[i] <= fx
    int find(int o, int l, int r) {
        if (fr <= l || r <= fl || mn[o] > fx) return -1;
        if (r - l == 1) return l;
        push(o);
        int m = (l + r) / 2, L = o * 2, R = o * 2 + 1;
        int a = rev ? find(R, m, r) : find(L, l, m);
        if (a != -1) return a;
        return rev ? find(L, l, m) : find(R, m, r);
    }
    void add(int l, int r, ll v) {
        add(l, r + 1, v, 1, 0, n);
    }
    ll query(int l, int r) {
        return query(l, r + 1, 1, 0, n);
    }
    int first_le(int l, int r, ll x) {
        fl = l, fr = r + 1, fx = x, rev = false;
        return find(1, 0, n);
    }
    int last_le(int l, int r, ll x) {
        fl = l, fr = r + 1, fx = x, rev = true;
        return find(1, 0, n);
    }
};
