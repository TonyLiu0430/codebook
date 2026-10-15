// Prim O(V^2)：完全圖／稠密圖的 MST（稀疏圖用 Kruskal）
// 不存邊，邊權由 w(i, j) 現算；沒邊回傳 T 的最大值
// 回傳 {是否連通, 權重和}
// 例1 完全圖（平面點距離）：
// prim<double>(n, [&](int i, int j) {
//     return hypot(x[i] - x[j], y[i] - y[j]); });
// 例2 鄰接矩陣，g[i][j] == -1 表示沒邊：
// const ll inf = numeric_limits<ll>::max();
// prim<ll>(n, [&](int i, int j) {
//     return g[i][j] == -1 ? inf : g[i][j]; });
template<class T>
pair<bool, T> prim(int n, auto &&w) {
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
