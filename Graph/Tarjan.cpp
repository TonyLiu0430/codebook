// directed strongly connected components
struct tarjan {
    vector<vector<int>> g;
    vector<int> dfn, low, comp, stack;
    vector<char> in_stack;
    int time = 0, count = 0;

    tarjan(int n)
        : g(n), dfn(n), low(n), comp(n, -1), in_stack(n) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    void dfs(int u) {
        dfn[u] = low[u] = ++time;
        stack.push_back(u);
        in_stack[u] = true;
        for (int v : g[u]) {
            if (!dfn[v]) dfs(v), low[u] = min(low[u], low[v]);
            else if (in_stack[v]) low[u] = min(low[u], dfn[v]);
        }
        if (low[u] != dfn[u]) return;
        while (true) {
            int v = stack.back();
            stack.pop_back();
            in_stack[v] = false;
            comp[v] = count;
            if (v == u) break;
        }
        ++count;
    }
    int solve() {
        for (int u = 0; u < (int)g.size(); ++u) if (!dfn[u]) dfs(u);
        return count;
    }
};
