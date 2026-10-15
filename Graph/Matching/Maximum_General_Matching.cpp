// 一般圖（非二分圖）最大匹配：Edmonds 開花演算法，
// O(V^3)。
// Edmonds blossom, O(V^3); match[v] is the partner or -1
struct general_matching {
    int n;
    vector<vector<int>> g;
    vector<int> match, parent, base, q;
    vector<char> used, blossom;

    general_matching(int n) : n(n), g(n), match(n, -1) {}
    void add_edge(int u, int v) {
        g[u].push_back(v), g[v].push_back(u);
    }
    int lca(int a, int b) {
        vector<char> seen(n);
        for (;;) {
            a = base[a], seen[a] = true;
            if (match[a] == -1) break;
            a = parent[match[a]];
        }
        for (;; b = parent[match[b]])
            if (b = base[b]; seen[b]) return b;
    }
    void mark_path(int v, int b, int child) {
        while (base[v] != b) {
            int m = match[v];
            blossom[base[v]] = blossom[base[m]] = true;
            parent[v] = child, child = m, v = parent[m];
        }
    }
    void push(int i) { used[i] = true, q.push_back(i); }
    int find_path(int root) {
        used.assign(n, false), parent.assign(n, -1);
        base.resize(n);
        iota(base.begin(), base.end(), 0);
        q.clear(), push(root);
        for (int h = 0; h < ssize(q); ++h) {
            int v = q[h];
            for (int to : g[v]) {
                if (base[v] == base[to] || match[v] == to)
                    continue;
                int m = match[to];
                bool in_tree = m != -1 && parent[m] != -1;
                if (to == root || in_tree) {
                    int cur = lca(v, to);
                    blossom.assign(n, false);
                    mark_path(v, cur, to);
                    mark_path(to, cur, v);
                    for (int i = 0; i < n; ++i)
                        if (blossom[base[i]]) {
                            base[i] = cur;
                            if (!used[i]) push(i);
                        }
                } else if (parent[to] == -1) {
                    parent[to] = v;
                    if (m == -1) return to;
                    push(m);
                }
            }
        }
        return -1;
    }
    int solve() {
        int ans = 0;
        for (int v = 0; v < n; ++v) if (match[v] == -1) {
            int u = find_path(v);
            if (u != -1) ++ans;
            while (u != -1) {
                int pv = parent[u], next = match[pv];
                match[u] = pv, match[pv] = u, u = next;
            }
        }
        return ans;
    }
};
