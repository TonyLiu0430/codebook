// static rectangle point count, inclusive bounds
struct range_tree_2d {
    vector<int> xs;
    vector<vector<int>> ys;

    range_tree_2d(vector<pair<int, int>> p) {
        ranges::sort(p);
        for (auto q : p) xs.push_back(q.first);
        ys.resize(4 * max<size_t>(1, p.size()));
        if (!p.empty()) build(1, 0, p.size(), p);
    }
    void build(int o, int l, int r, const vector<pair<int, int>> &p) {
        if (r - l == 1) return ys[o].push_back(p[l].second);
        int m = (l + r) / 2;
        build(o * 2, l, m, p);
        build(o * 2 + 1, m, r, p);
        ranges::merge(ys[o * 2], ys[o * 2 + 1], back_inserter(ys[o]));
    }
    int query(int ql, int qr, int y1, int y2, int o, int l, int r) {
        if (ql <= l && r <= qr)
            return ranges::upper_bound(ys[o], y2) -
                   ranges::lower_bound(ys[o], y1);
        int m = (l + r) / 2, ans = 0;
        if (ql < m) ans += query(ql, qr, y1, y2, o * 2, l, m);
        if (m < qr) ans += query(ql, qr, y1, y2, o * 2 + 1, m, r);
        return ans;
    }
    int count(int x1, int y1, int x2, int y2) {
        int l = ranges::lower_bound(xs, x1) - xs.begin();
        int r = ranges::upper_bound(xs, x2) - xs.begin();
        return l == r ? 0 : query(l, r, y1, y2, 1, 0, xs.size());
    }
};
