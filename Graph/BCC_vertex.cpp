// 無向圖點雙連通分量 O(V+E)：找割點、把點分到各點雙分量
// （割點同時屬於多個分量；孤立點自成一個分量；重邊 OK）
// 圓方樹 tree：0..n-1 為原點，n+i 為第 i 個分量的方點，
// 方點連向分量內每個點；u 到 v 必經的點 = 樹上路徑的原點
struct vertex_bcc {
    vector<vector<int>> g, comps, tree;
    vector<int> dfn, low, stk;
    vector<char> cut;
    int time = 0;

    vertex_bcc(int n) : g(n), dfn(n), low(n), cut(n) {}
    void add_edge(int u, int v) {
        g[u].push_back(v), g[v].push_back(u);
    }
    void dfs(int u, bool root) {
        dfn[u] = low[u] = ++time;
        stk.push_back(u);
        int child = 0;
        for (int v : g[u]) {
            if (dfn[v]) {
                low[u] = min(low[u], dfn[v]);
                continue;
            }
            dfs(v, false), ++child;
            low[u] = min(low[u], low[v]);
            if (low[v] < dfn[u]) continue;
            if (!root || child > 1) cut[u] = true;
            comps.push_back({u}); // u 加子樹 v 為一分量
            int x;
            do x = stk.back(), stk.pop_back(),
               comps.back().push_back(x);
            while (x != v);
        }
    }
    void solve() {
        int n = g.size();
        for (int u = 0; u < n; ++u) if (!dfn[u]) {
            int k = comps.size();
            dfs(u, true), stk.clear();
            if (ssize(comps) == k) comps.push_back({u});
        }
        tree.assign(n + comps.size(), {});
        for (int i = 0; i < ssize(comps); ++i)
            for (int x : comps[i]) {
                tree[n + i].push_back(x);
                tree[x].push_back(n + i);
            }
    }
};
