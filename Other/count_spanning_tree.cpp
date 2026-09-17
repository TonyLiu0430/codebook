using ll = long long;

ll mod_power(ll a, ll n, ll mod) {
    ll ans = 1;
    for (; n; n /= 2, a = (__int128)a * a % mod)
        if (n & 1) ans = (__int128)ans * a % mod;
    return ans;
}

// undirected multigraph; mod must be prime
ll spanning_trees(int n, const vector<pair<int, int>> &edges, ll mod) {
    if (n == 1) return 1;
    vector<vector<ll>> a(n - 1, vector<ll>(n - 1));
    for (auto e : edges) {
        int u = e.first, v = e.second;
        if (u == v) continue;
        if (u < n - 1) a[u][u] = (a[u][u] + 1) % mod;
        if (v < n - 1) a[v][v] = (a[v][v] + 1) % mod;
        if (u < n - 1 && v < n - 1) {
            a[u][v] = (a[u][v] + mod - 1) % mod;
            a[v][u] = (a[v][u] + mod - 1) % mod;
        }
    }
    ll det = 1;
    for (int col = 0; col < n - 1; ++col) {
        int pivot = col;
        while (pivot < n - 1 && !a[pivot][col]) ++pivot;
        if (pivot == n - 1) return 0;
        if (pivot != col) swap(a[pivot], a[col]), det = mod - det;
        det = (__int128)det * a[col][col] % mod;
        ll inv = mod_power(a[col][col], mod - 2, mod);
        for (int row = col + 1; row < n - 1; ++row) {
            ll mul = (__int128)a[row][col] * inv % mod;
            for (int j = col; j < n - 1; ++j)
                a[row][j] = (a[row][j] - (__int128)mul * a[col][j] % mod + mod) % mod;
        }
    }
    return det;
}
