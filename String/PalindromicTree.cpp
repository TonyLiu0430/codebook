// eertree, lowercase; node 0 has len -1, node 1 has len 0
// every other node is a distinct palindrome; call count() for occurrences
struct palindromic_tree {
    struct node {
        int len, link = 0, cnt = 0;
        array<int, 26> next{};
    };
    vector<node> t{{-1}, {0}};
    string s;
    int last = 1;

    int get_link(int u) {
        int i = s.size() - 1;
        while (i - t[u].len - 1 < 0 || s[i - t[u].len - 1] != s[i]) u = t[u].link;
        return u;
    }
    void add(char ch) {
        s += ch;
        int c = ch - 'a', u = get_link(last);
        if (!t[u].next[c]) {
            int v = t.size();
            t.push_back({t[u].len + 2});
            t[v].link = t[u].len == -1 ? 1 : t[get_link(t[u].link)].next[c];
            t[u].next[c] = v;
        }
        last = t[u].next[c];
        ++t[last].cnt;
    }
    void count() { // links point to shorter, earlier nodes
        for (int i = ssize(t) - 1; i > 1; --i) t[t[i].link].cnt += t[i].cnt;
    }
};
