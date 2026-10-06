// 有向圖 SCC，O(V+E)；low[u] == dfn[u] 時彈棧到 u
// dfn：訪問順序；樹邊用 low[v]，棧內已訪問邊用 dfn[v] 更新 low[u]
// 無向圖橋／割點：見 BCC_edge.cpp；邊雙向加，不用 in_stack
// 只跳過父邊 id（保留重邊）；其餘已訪問邊用 dfn[v] 更新 low[u]
// 橋：DFS 樹邊 (u,v) 在 dfs(v) 後滿足 low[v] > dfn[u]
// 割點：非根 u 有 DFS 子節點 v 滿足 low[v] >= dfn[u]
// DFS 根須有至少兩個 DFS 樹子節點才是割點（不是看度數）
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
        for (int u = 0; u < ssize(g); ++u) if (!dfn[u]) dfs(u);
        return count;
    }
};
