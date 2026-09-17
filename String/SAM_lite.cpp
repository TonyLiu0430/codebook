struct sam {
    struct state {
        int len = 0, link = -1;
        array<int, 26> next{};
    };
    vector<state> st{state{}};
    int last = 0;

    void add(char ch) {
        int c = ch - 'a';
        assert(0 <= c && c < 26);
        int cur = st.size(), p = last;
        st.push_back({});
        st[cur].len = st[last].len + 1;
        while (p != -1 && !st[p].next[c])
            st[p].next[c] = cur, p = st[p].link;
        if (p == -1) st[cur].link = 0;
        else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) st[cur].link = q;
            else {
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q)
                    st[p].next[c] = clone, p = st[p].link;
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }
};
