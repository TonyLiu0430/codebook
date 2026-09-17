// static rectangle point count, inclusive bounds
struct range_tree_2d {
    vector<int> xs;
    vector<vector<int>> ys;

    range_tree_2d(vector<pair<int, int>> p) {
        sort(p.begin(), p.end());
        for (auto q : p) xs.push_back(q.first);
        ys.resize(4 * max<size_t>(1, p.size()));
        if (!p.empty()) build(1, 0, p.size(), p);
    }
    void build(int o, int l, int r, const vector<pair<int, int>> &p) {
        if (r - l == 1) return ys[o].push_back(p[l].second);
        int m = (l + r) / 2;
        build(o * 2, l, m, p);
        build(o * 2 + 1, m, r, p);
        merge(ys[o * 2].begin(), ys[o * 2].end(),
              ys[o * 2 + 1].begin(), ys[o * 2 + 1].end(),
              back_inserter(ys[o]));
    }
    int query(int ql, int qr, int y1, int y2, int o, int l, int r) const {
        if (ql <= l && r <= qr)
            return upper_bound(ys[o].begin(), ys[o].end(), y2) -
                   lower_bound(ys[o].begin(), ys[o].end(), y1);
        int m = (l + r) / 2, ans = 0;
        if (ql < m) ans += query(ql, qr, y1, y2, o * 2, l, m);
        if (m < qr) ans += query(ql, qr, y1, y2, o * 2 + 1, m, r);
        return ans;
    }
    int count(int x1, int y1, int x2, int y2) const {
        int l = lower_bound(xs.begin(), xs.end(), x1) - xs.begin();
        int r = upper_bound(xs.begin(), xs.end(), x2) - xs.begin();
        return l == r ? 0 : query(l, r, y1, y2, 1, 0, xs.size());
    }
};
