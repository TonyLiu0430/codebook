// Hopcroft-Karp 二分圖最大匹配，O(E sqrt(V))，點數邊數
// 大時使用。
// O(E sqrt V); left side [0, n), right side [0, m)
struct hopcroft_karp {
    int n;
    vector<vector<int>> g;
    vector<int> ml, mr, dist; // partner of left / right

    hopcroft_karp(int n, int m)
        : n(n), g(n), ml(n, -1), mr(m, -1), dist(n) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    bool bfs() {
        queue<int> q;
        bool found = false;
        for (int u = 0; u < n; ++u)
            if (ml[u] == -1) dist[u] = 0, q.push(u);
            else dist[u] = -1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : g[u]) {
                int w = mr[v];
                if (w == -1) found = true;
                else if (dist[w] == -1)
                    dist[w] = dist[u] + 1, q.push(w);
            }
        }
        return found;
    }
    bool dfs(int u) {
        for (int v : g[u]) {
            int w = mr[v];
            if (~w && dist[w] != dist[u] + 1) continue;
            if (~w && !dfs(w)) continue;
            return ml[u] = v, mr[v] = u, true;
        }
        dist[u] = -1;
        return false;
    }
    int solve() {
        int ans = 0;
        while (bfs())
            for (int u = 0; u < n; ++u)
                if (ml[u] == -1 && dfs(u)) ++ans;
        return ans;
    }
};
