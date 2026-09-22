// 1-based rectangle add and rectangle sum; memory is 32*n*m bytes
struct bit2d {
    using ll = long long;
    int n, m;
    array<vector<vector<ll>>, 4> t;

    bit2d(int n, int m) : n(n), m(m) {
        for (auto &a : t) a.assign(n + 1, vector<ll>(m + 1));
    }

    void add_one(int x, int y, ll v) {
        for (int i = x; i <= n; i += i & -i)
            for (int j = y; j <= m; j += j & -j) {
                t[0][i][j] += v;
                t[1][i][j] += v * (x - 1);
                t[2][i][j] += v * (y - 1);
                t[3][i][j] += v * (x - 1) * (y - 1);
            }
    }

    ll get(int k, int x, int y) {
        ll ans = 0;
        for (int i = x; i > 0; i -= i & -i)
            for (int j = y; j > 0; j -= j & -j) ans += t[k][i][j];
        return ans;
    }

    void add(int x1, int y1, int x2, int y2, ll v) {
        assert(1 <= x1 && x1 <= x2 && x2 <= n);
        assert(1 <= y1 && y1 <= y2 && y2 <= m);
        add_one(x1, y1, v);
        if (y2 < m) add_one(x1, y2 + 1, -v);
        if (x2 < n) add_one(x2 + 1, y1, -v);
        if (x2 < n && y2 < m) add_one(x2 + 1, y2 + 1, v);
    }

    ll prefix(int x, int y) {
        if (x <= 0 || y <= 0) return 0;
        return get(0, x, y) * x * y - get(1, x, y) * y -
               get(2, x, y) * x + get(3, x, y);
    }
    ll sum(int x1, int y1, int x2, int y2) {
        return prefix(x2, y2) - prefix(x1 - 1, y2) -
               prefix(x2, y1 - 1) + prefix(x1 - 1, y1 - 1);
    }
};
