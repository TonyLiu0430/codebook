// centroid decomposition; cpar[] is the parent in the centroid tree
// centroid tree depth is O(log n); every path passes some centroid
struct centroid {
    vector<vector<int>> g;
    vector<int> size, cpar;
    vector<char> removed;

    centroid(int n) : g(n), size(n), cpar(n, -1), removed(n) {}
    void add_edge(int u, int v) { g[u].push_back(v), g[v].push_back(u); }
    int calc_size(int u, int p) {
        size[u] = 1;
        for (int v : g[u]) if (v != p && !removed[v]) size[u] += calc_size(v, u);
        return size[u];
    }
    int find(int u, int p, int total) {
        for (int v : g[u])
            if (v != p && !removed[v] && size[v] * 2 > total)
                return find(v, u, total);
        return u;
    }
    void build(int u = 0, int p = -1) {
        int c = find(u, -1, calc_size(u, -1));
        cpar[c] = p, removed[c] = true;
        // solve(c): count paths through c using vertices not removed
        for (int v : g[c]) if (!removed[v]) build(v, c);
    }
};
