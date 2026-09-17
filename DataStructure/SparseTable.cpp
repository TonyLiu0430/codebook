// idempotent rmq: minimum on [l, r]
template<class t>
struct sparse_table {
    vector<int> lg;
    vector<vector<t>> st;

    sparse_table(const vector<t> &a) : lg(a.size() + 1) {
        for (int i = 2; i < (int)lg.size(); ++i) lg[i] = lg[i / 2] + 1;
        int k = a.empty() ? 0 : lg[a.size()] + 1;
        st.assign(k, vector<t>(a.size()));
        if (a.empty()) return;
        st[0] = a;
        for (int j = 1; j < k; ++j)
            for (int i = 0; i + (1 << j) <= (int)a.size(); ++i)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    t query(int l, int r) const {
        assert(l <= r);
        int k = lg[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
