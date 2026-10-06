// idempotent rmq: minimum on [l, r]
template<class t>
struct sparse_table {
    vector<vector<t>> st;

    sparse_table(const vector<t> &a) {
        int k = a.empty() ? 0 : __lg(a.size()) + 1;
        st.assign(k, vector<t>(a.size()));
        if (a.empty()) return;
        st[0] = a;
        for (int j = 1; j < k; ++j)
            for (int i = 0; i + (1 << j) <= ssize(a); ++i)
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }
    t query(int l, int r) {
        assert(l <= r);
        int k = __lg(r - l + 1);
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
