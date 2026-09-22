// empty result means the graph has a cycle
vector<int> topological_sort(const vector<vector<int>> &g) {
    vector<int> indeg(g.size()), order;
    for (auto &es : g) for (int v : es) ++indeg[v];
    queue<int> q;
    for (int i = 0; i < ssize(g); ++i)
        if (!indeg[i]) q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : g[u]) if (!--indeg[v]) q.push(v);
    }
    if (order.size() != g.size()) order.clear();
    return order;
}
