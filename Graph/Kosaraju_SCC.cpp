struct kosaraju {
    vector<vector<int>> g, rev;
    vector<int> used, order, comp;

    kosaraju(int n) : g(n), rev(n), used(n), comp(n) {}
    void add_edge(int u, int v) { g[u].push_back(v), rev[v].push_back(u); }
    void dfs(int u) {
        used[u] = true;
        for (int v : g[u]) if (!used[v]) dfs(v);
        order.push_back(u);
    }
    void rdfs(int u, int id) {
        comp[u] = id;
        used[u] = true;
        for (int v : rev[u]) if (!used[v]) rdfs(v, id);
    }
    int solve() {
        fill(used.begin(), used.end(), 0);
        order.clear();
        for (int u = 0; u < (int)g.size(); ++u) if (!used[u]) dfs(u);
        fill(used.begin(), used.end(), 0);
        reverse(order.begin(), order.end());
        int count = 0;
        for (int u : order) if (!used[u]) rdfs(u, count++);
        return count;
    }
};
