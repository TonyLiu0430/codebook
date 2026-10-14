// Hierholzer, O(V+E); works for directed and undirected graphs
struct euler {
    int n;
    bool directed;
    vector<vector<pair<int, int>>> g; // to, edge id
    vector<pair<int, int>> edges;

    euler(int n, bool directed)
        : n(n), directed(directed), g(n) {}
    void add_edge(int u, int v) {
        int id = edges.size();
        edges.push_back({u, v});
        g[u].push_back({v, id});
        if (!directed) g[v].push_back({u, id});
    }
    // vertex sequence of an euler path (a circuit if possible); empty if none
    vector<int> path() {
        int m = edges.size(), s = m ? edges[0].first : 0,
            odd = 0;
        vector<int> deg(n);
        for (auto [u, v] : edges)
            ++deg[u], directed ? --deg[v] : ++deg[v];
        for (int i = 0; i < n; ++i) {
            int d = directed ? deg[i] : deg[i] % 2;
            if (d == 1) s = i, ++odd;
            else if (d != 0 && !(directed && d == -1))
                return {};
        }
        if (odd > (directed ? 1 : 2)) return {};

        vector<int> it(n), ans, stack{s};
        vector<char> used(m);
        while (!stack.empty()) {
            int u = stack.back(), &i = it[u];
            auto &e = g[u];
            while (i < ssize(e) && used[e[i].second]) ++i;
            if (i == ssize(e)) {
                ans.push_back(u), stack.pop_back();
                continue;
            }
            used[e[i].second] = true;
            stack.push_back(e[i].first);
        }
        // edges are not connected
        if (ssize(ans) != m + 1) return {};
        ranges::reverse(ans);
        return ans;
    }
};
