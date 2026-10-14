// union by size, no path compression: find is O(log n)
// t = d.time(); ...unite...; d.rollback(t) undoes them
// offline dynamic connectivity: put each edge on the
// segment tree over time, dfs it and roll back on return
struct rollback_dsu {
    vector<int> p, size;
    vector<pair<int, int>> history; // (root, merged child)

    rollback_dsu(int n) : p(n), size(n, 1) {
        iota(p.begin(), p.end(), 0);
    }
    int find(int x) {
        while (p[x] != x) x = p[x];
        return x;
    }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        p[b] = a, size[a] += size[b];
        history.push_back({a, b});
        return true;
    }
    int time() { return history.size(); }
    void rollback(int t) {
        while (ssize(history) > t) {
            auto [a, b] = history.back();
            history.pop_back();
            p[b] = b, size[a] -= size[b];
        }
    }
};
