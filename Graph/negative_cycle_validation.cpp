// Floyd-Warshall 全點對最短路 O(n^3)，並標記哪些點對會
// 受負環影響（距離為 -inf）。
// 單純偵測負環請用 bellman-ford
using ll = long long;
const ll inf = LLONG_MAX / 4;

struct floyd_result {
    vector<vector<ll>> dist;
    vector<vector<char>> negative;
};

floyd_result floyd_warshall(vector<vector<ll>> dist) {
    int n = dist.size();
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i) if (dist[i][k] != inf)
            for (int j = 0; j < n; ++j) {
                if (dist[k][j] == inf) continue;
                auto x = (__int128)dist[i][k] + dist[k][j];
                ll v = clamp<__int128>(x, -inf, inf);
                dist[i][j] = min(dist[i][j], v);
            }

    vector<vector<char>> negative(n, vector<char>(n));
    for (int k = 0; k < n; ++k) if (dist[k][k] < 0)
        for (int i = 0; i < n; ++i) if (dist[i][k] != inf)
            for (int j = 0; j < n; ++j)
                negative[i][j] |= dist[k][j] != inf;
    return {dist, negative};
}
