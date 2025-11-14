struct TarjanSCC {
	// n must be first
    int n, timer = 0, scc_cnt = 0;
    vector<vector<int>> g;
    vector<int> dfn, low, in_stack, scc_id;
    stack<int> stk;

    TarjanSCC(int n) : n(n), g(n), dfn(n, -1), low(n), in_stack(n, 0), scc_id(n, -1) {}

    void add_edge(int u, int v) {
        g[u].push_back(v);
    }

    void dfs(int u) {
        dfn[u] = low[u] = timer++;
        stk.push(u);
        in_stack[u] = 1;

        for (int v : g[u]) {
            if (dfn[v] == -1) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (in_stack[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }

        // root of SCC
        if (low[u] == dfn[u]) {
            while (true) {
                int v = stk.top(); stk.pop();
                in_stack[v] = 0;
                scc_id[v] = scc_cnt;
                if (v == u) break;
            }
            scc_cnt++;
        }
    }

    // returns SCC count
    int run() {
        for (int i = 0; i < n; i++)
            if (dfn[i] == -1)
                dfs(i);
        return scc_cnt;
    }
};

// tarjan BCC
割點
點 u 為割點 if and only if 滿足 1. or 2. 
1. u 爲樹根，且 u 有多於一個子樹。 
2. u 不爲樹根，且滿足存在 (u,v) 爲樹枝邊 (或稱父子邊，即 u 爲 v 在搜索樹中的父親)，使得 DFN(u) <= Low(v)。

-------------------------------------------------------
橋
一條無向邊 (u,v) 是橋 if and only if (u,v) 爲樹枝邊，且滿足 DFN(u) < Low(v)。
int n, timer = 0;
vector<vector<int>> g;
vector<int> dfn /* init by -1*/, low;

void dfs(int u, int parent) {
    dfn[u] = low[u] = timer++;

    for (int v : g[u]) {
        if (v == parent) continue;

        if (dfn[v] == -1) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

