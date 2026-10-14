// binary lifting on a tree; O(n log n) build, O(log n) query
struct lca {
    int lg = 1;
    vector<vector<int>> g, up;
    vector<int> depth;

    lca(int n) : g(n), depth(n) {
        while ((1 << lg) < n) ++lg;
        up.assign(lg, vector<int>(n));
    }
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    void build(int root = 0) {
        vector<int> stack{root};
        up[0][root] = root;
        while (!stack.empty()) {
            int u = stack.back();
            stack.pop_back();
            for (int v : g[u]) if (v != up[0][u])
                up[0][v] = u, depth[v] = depth[u] + 1, stack.push_back(v);
        }
        for (int k = 1; k < lg; ++k)
            for (int v = 0; v < ssize(depth); ++v)
                up[k][v] = up[k - 1][up[k - 1][v]];
    }
    int query(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        for (int k = lg - 1; k >= 0; --k)
            if (depth[a] - (1 << k) >= depth[b]) a = up[k][a];
        if (a == b) return a;
        for (int k = lg - 1; k >= 0; --k)
            if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        return up[0][a];
    }
    int dist(int a, int b) {
        return depth[a] + depth[b] - 2 * depth[query(a, b)];
    }
};
