// Johnson 全源最短路 O(VE log V)：有負權邊的稀疏圖，
// V 大到 Floyd O(V^3) 跑不完時用。
// 勢能 h = 超級源點（連到每點、邊權 0）的最短距離，
// 邊權改成 w + h[u] - h[v] >= 0，就能從每點跑
// Dijkstra，真實距離 = d'(s, v) - h[s] + h[v]。
// 回傳 dist[s][v]（走不到為 inf）；有負環回傳 nullopt
using ll = long long;
const ll inf = LLONG_MAX / 4;
using wedge = tuple<int, int, ll>; // from, to, weight

optional<vector<vector<ll>>>
johnson(int n, const vector<wedge> &edges) {
    vector<ll> h(n); // h = 0：已鬆弛超級源點的邊
    for (int i = 0;; ++i) {
        bool changed = false;
        for (auto [u, v, w] : edges)
            if (h[u] + w < h[v])
                h[v] = h[u] + w, changed = true;
        if (!changed) break;
        if (i == n) return nullopt; // 一直能鬆弛：負環
    }
    vector<vector<pair<int, ll>>> g(n);
    for (auto [u, v, w] : edges)
        g[u].push_back({v, w + h[u] - h[v]});
    using state = pair<ll, int>;
    vector dist(n, vector<ll>(n, inf));
    for (int s = 0; s < n; ++s) {
        auto &d = dist[s];
        priority_queue<state, vector<state>, greater<>> pq;
        d[s] = 0, pq.push({0, s});
        while (!pq.empty()) {
            auto [du, u] = pq.top();
            pq.pop();
            if (du != d[u]) continue;
            for (auto [v, w] : g[u])
                if (du + w < d[v])
                    d[v] = du + w, pq.push({d[v], v});
        }
        for (int v = 0; v < n; ++v)
            if (d[v] != inf) d[v] += h[v] - h[s];
    }
    return dist;
}
