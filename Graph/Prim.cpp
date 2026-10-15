// Prim 陣列版 O(V^2)，不用存邊：稠密圖／完全圖用（如
// 平面點兩兩距離求 MST）；稀疏圖請用 Kruskal。
// w(i, j)：邊權，沒有邊回傳 numeric_limits<T>::max()
// 回傳 {是否連通, MST 權重和}，例：
// prim<double>(n, [&](int i, int j) { return d(i, j); })
template<class T, class F>
pair<bool, T> prim(int n, F w) {
    const T inf = numeric_limits<T>::max();
    vector<T> dist(n, inf);
    vector<char> used(n);
    T total = 0;
    if (n) dist[0] = 0;
    for (int it = 0; it < n; ++it) {
        int u = -1;
        for (int v = 0; v < n; ++v)
            if (!used[v] &&
                (u == -1 || dist[v] < dist[u]))
                u = v;
        if (dist[u] == inf) return {false, total};
        used[u] = true, total += dist[u];
        for (int v = 0; v < n; ++v)
            if (!used[v])
                dist[v] = min(dist[v], w(u, v));
    }
    return {true, total};
}
