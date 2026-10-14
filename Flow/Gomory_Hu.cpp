// needs dinic.cpp; undirected graph, n - 1 max flows (Gusfield)
// returns tree edges {u, v, w}; min cut(a, b) = min w on the tree path
vector<tuple<int, int, ll>> gomory_hu(
    int n, const vector<tuple<int, int, ll>> &edges) {
    vector<int> p(n);
    vector<tuple<int, int, ll>> tree;
    for (int s = 1; s < n; ++s) {
        dinic d(n);
        for (auto [u, v, w] : edges)
            d.add_edge(u, v, w), d.add_edge(v, u, w);
        ll f = d.max_flow(s, p[s]);
        auto side = d.min_cut_side(s);
        for (int i = s + 1; i < n; ++i)
            if (p[i] == p[s] && side[i]) p[i] = s;
        tree.push_back({s, p[s], f});
    }
    return tree;
}
