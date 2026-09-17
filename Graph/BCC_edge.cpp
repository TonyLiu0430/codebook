// undirected edge-biconnected components; parallel edges are allowed
struct edge_bcc {
    struct edge { int to, id; };
    vector<vector<edge>> g;
    vector<int> dfn, low, comp;
    vector<char> bridge;
    int time = 0;

    edge_bcc(int n) : g(n), dfn(n), low(n), comp(n, -1) {}
    void add_edge(int u, int v) {
        int id = bridge.size();
        bridge.push_back(false);
        g[u].push_back({v, id});
        g[v].push_back({u, id});
    }
    void dfs(int u, int parent_edge = -1) {
        dfn[u] = low[u] = ++time;
        for (edge e : g[u]) {
            if (e.id == parent_edge) continue;
            if (!dfn[e.to]) {
                dfs(e.to, e.id);
                low[u] = min(low[u], low[e.to]);
                if (low[e.to] > dfn[u]) bridge[e.id] = true;
            } else low[u] = min(low[u], dfn[e.to]);
        }
    }
    void paint(int u, int id) {
        comp[u] = id;
        for (edge e : g[u])
            if (!bridge[e.id] && comp[e.to] == -1) paint(e.to, id);
    }
    int solve() {
        for (int u = 0; u < (int)g.size(); ++u) if (!dfn[u]) dfs(u);
        int count = 0;
        for (int u = 0; u < (int)g.size(); ++u)
            if (comp[u] == -1) paint(u, count++);
        return count;
    }
};
