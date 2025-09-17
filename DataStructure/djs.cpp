struct DisjointSet {
    vector<int> parent, sz;  // parent[i] = 父節點, sz[i] = 集合大小
    void init(int n) {
        parent.resize(n + 1);
        sz.assign(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // 路徑壓縮
        }
        return parent[x];
    }
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;  // 已在同一集合
        // 啟發式合併：小的掛到大的下面
        if (sz[x] < sz[y]) swap(x, y);
        parent[y] = x;
        sz[x] += sz[y];
        return true;
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};
