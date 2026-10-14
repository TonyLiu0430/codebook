// lowercase only; call build() after all inserts
// after build, next[] is the full automaton and end counts suffix matches
struct aho_corasick {
    struct node {
        array<int, 26> next{};
        int fail = 0, end = 0;
    };
    vector<node> t{node{}};
    vector<int> order; // bfs order; reverse it for dp on the fail tree

    int insert(const string &s) {
        int u = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!t[u].next[c]) t[u].next[c] = t.size(), t.push_back({});
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
                if (v) t[v].fail = t[t[u].fail].next[c], q.push(v);
                else v = t[t[u].fail].next[c];
            }
        }
    }
    long long count(const string &text) { // total pattern occurrences
        long long ans = 0;
        for (int u = 0; char ch : text)
            u = t[u].next[ch - 'a'], ans += t[u].end;
        return ans;
    }
};
