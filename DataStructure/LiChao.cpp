// 李超線段樹：動態插入直線 kx+b，查詢某個 x 的最大值；
// 常用於斜率優化 DP。
// Li Chao tree on integer x in [lo, hi]: add line kx+b, query max
// for min, insert {-k, -b} and negate the answer
using ll = long long;

struct li_chao {
    struct line {
        ll k = 0, b = LLONG_MIN;
        ll operator()(ll x) const { return k * x + b; }
    };
    struct node { line f; int l = -1, r = -1; };
    ll lo, hi;
    vector<node> t{node{}};

    li_chao(ll lo, ll hi) : lo(lo), hi(hi) {}
    void add(line f) {
        int u = 0;
        for (ll l = lo, r = hi;;) {
            ll m = l + (r - l) / 2;
            bool left = f(l) > t[u].f(l),
                 mid = f(m) > t[u].f(m);
            if (mid) swap(t[u].f, f);
            if (l == r || f.b == LLONG_MIN) return;
            bool go_left = left != mid;
            if (go_left) r = m;
            else l = m + 1;
            int c = go_left ? t[u].l : t[u].r;
            if (c == -1) {
                c = t.size(), t.push_back({});
                (go_left ? t[u].l : t[u].r) = c;
            }
            u = c;
        }
    }
    ll query(ll x) {
        ll ans = LLONG_MIN, l = lo, r = hi;
        for (int u = 0; u != -1;) {
            ans = max(ans, t[u].f(x));
            ll m = l + (r - l) / 2;
            if (x <= m) u = t[u].l, r = m;
            else u = t[u].r, l = m + 1;
        }
        return ans;
    }
};
