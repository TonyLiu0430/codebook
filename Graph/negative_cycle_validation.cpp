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
            for (int j = 0; j < n; ++j) if (dist[k][j] != inf) {
                __int128 x = (__int128)dist[i][k] + dist[k][j];
                ll value = x < -inf ? -inf : x > inf ? inf : (ll)x;
                dist[i][j] = min(dist[i][j], value);
            }

    vector<vector<char>> negative(n, vector<char>(n));
    for (int k = 0; k < n; ++k) if (dist[k][k] < 0)
        for (int i = 0; i < n; ++i) if (dist[i][k] != inf)
            for (int j = 0; j < n; ++j) if (dist[k][j] != inf)
                negative[i][j] = true;
    return {dist, negative};
}
