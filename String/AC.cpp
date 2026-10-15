// AC 自動機：多模式字串匹配，一次掃 text 統計所有
// pattern 的出現次數。
// lowercase only; call build() after all inserts
// after build, next[] is the full automaton and end counts suffix matches
struct aho_corasick {
    struct node {
        array<int, 26> next{};
        int fail = 0, end = 0;
    };
    vector<node> t{node{}};
    // bfs order; reverse it for dp on the fail tree
    vector<int> order;

    int insert(const string &s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!t[u].next[c])
                t[u].next[c] = t.size(), t.push_back({});
            u = t[u].next[c];
        }
        ++t[u].end;
        return u;
    }
    void build() {
        queue<int> q;
        for (int v : t[0].next) if (v) q.push(v);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            t[u].end += t[t[u].fail].end;
            for (int c = 0; c < 26; ++c) {
                int &v = t[u].next[c];
                int f = t[t[u].fail].next[c];
                if (v) t[v].fail = f, q.push(v);
                else v = f;
            }
        }
    }
    // total pattern occurrences
    long long count(const string &text) {
        long long ans = 0;
        for (int u = 0; char ch : text)
            u = t[u].next[ch - 'a'], ans += t[u].end;
        return ans;
    }
};
