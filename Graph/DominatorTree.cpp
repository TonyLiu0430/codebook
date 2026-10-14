// Lengauer-Tarjan, O((V+E) log V); directed graph g from root
// returns idom; idom[root] = root, unreachable vertices get -1
vector<int> dominator_tree(const vector<vector<int>> &g,
                           int root) {
    int n = g.size(), m = 0;
    vector<vector<int>> rg(n), bucket(n);
    vector<int> dfn(n, -1), order, par(n), sd(n), id(n),
        anc(n), lab(n);
    for (int u = 0; u < n; ++u)
        for (int v : g[u]) rg[v].push_back(u);
    auto dfs = [&](auto &self, int u) -> void {
        dfn[u] = m++, order.push_back(u);
        for (int v : g[u])
            if (dfn[v] == -1)
                self(self, v), par[dfn[v]] = dfn[u];
    };
    dfs(dfs, root);
    // below every index is a dfn
    iota(sd.begin(), sd.end(), 0), anc = lab = sd;
    auto compress = [&](auto &self, int v) -> void {
        if (anc[anc[v]] == anc[v]) return;
        self(self, anc[v]);
        if (sd[lab[anc[v]]] < sd[lab[v]])
            lab[v] = lab[anc[v]];
        anc[v] = anc[anc[v]];
    };
    auto eval = [&](int v) {
        if (anc[v] == v) return v;
        compress(compress, v);
        return lab[v];
    };
    for (int w = m - 1; w > 0; --w) {
        for (int v : rg[order[w]])
            if (dfn[v] != -1)
                sd[w] = min(sd[w], sd[eval(dfn[v])]);
        bucket[sd[w]].push_back(w);
        anc[w] = par[w];
        for (int v : bucket[par[w]]) {
            int u = eval(v);
            id[v] = sd[u] < sd[v] ? u : par[w];
        }
        bucket[par[w]].clear();
    }
    vector<int> idom(n, -1);
    for (int w = 1; w < m; ++w)
        if (id[w] != sd[w]) id[w] = id[id[w]];
    for (int w = 0; w < m; ++w)
        idom[order[w]] = order[w ? id[w] : 0];
    return idom;
}
