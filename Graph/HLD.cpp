// 樹鏈剖分：把樹上路徑／子樹拆成 O(log n) 段連續區間，
// 搭配線段樹做路徑修改與查詢。
// heavy-light decomposition; pos[] indexes a segment tree
// path(u, v) is O(log n) ranges [l, r] of pos
// edge values: store edge (parent, v) at pos[v], skip the lca's pos
struct hld {
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, pos, size;
    int time = 0;

    hld(int n)
        : g(n), parent(n, -1), depth(n), heavy(n, -1),
          head(n), pos(n), size(n, 1) {}
    void add_edge(int u, int v) {
        g[u].push_back(v), g[v].push_back(u);
    }
    void dfs_size(int u) {
        for (int v : g[u]) if (v != parent[u]) {
            parent[v] = u, depth[v] = depth[u] + 1;
            dfs_size(v);
            size[u] += size[v];
            if (heavy[u] == -1 || size[v] > size[heavy[u]])
                heavy[u] = v;
        }
    }
    void dfs_head(int u, int h) {
        head[u] = h, pos[u] = time++;
        if (heavy[u] != -1) dfs_head(heavy[u], h);
        for (int v : g[u])
            if (v != parent[u] && v != heavy[u])
                dfs_head(v, v);
    }
    void build(int root = 0) {
        dfs_size(root), dfs_head(root, root);
    }
    int lca(int u, int v) {
        for (; head[u] != head[v]; u = parent[head[u]])
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
        return depth[u] < depth[v] ? u : v;
    }
    vector<pair<int, int>> path(int u, int v) {
        vector<pair<int, int>> res;
        for (; head[u] != head[v]; u = parent[head[u]]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);
            res.push_back({pos[head[u]], pos[u]});
        }
        if (depth[u] > depth[v]) swap(u, v);
        res.push_back({pos[u], pos[v]}); // u is the lca
        return res;
    }
    pair<int, int> subtree(int u) {
        return {pos[u], pos[u] + size[u] - 1};
    }
};
