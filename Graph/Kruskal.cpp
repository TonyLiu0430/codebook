using ll = long long;

struct edge {
    int u, v;
    ll weight;
};
struct dsu {
    vector<int> p, size;
    dsu(int n) : p(n), size(n, 1) { iota(p.begin(), p.end(), 0); }
    int find(int x) { return p[x] == x ? x : p[x] = find(p[x]); }
    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (size[a] < size[b]) swap(a, b);
        p[b] = a;
        size[a] += size[b];
        return true;
    }
};

pair<bool, ll> kruskal(int n, vector<edge> edges) {
    ranges::sort(edges, {}, &edge::weight);
    dsu uf(n);
    ll total = 0;
    int used = 0;
    for (edge e : edges) if (uf.unite(e.u, e.v))
        total += e.weight, ++used;
    return {used == n - 1, total};
}
