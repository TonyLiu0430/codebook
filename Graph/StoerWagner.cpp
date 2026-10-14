// global min cut, undirected, adjacency matrix, O(V^3)
// n >= 2, weights >= 0; parallel edges: add the weights
using ll = long long;

ll stoer_wagner(vector<vector<ll>> w) {
    int n = w.size();
    ll best = LLONG_MAX;
    vector<int> alive(n);
    iota(alive.begin(), alive.end(), 0);
    for (int phase = n; phase > 1; --phase) {
        vector<ll> key(n);
        vector<char> vis(n);
        int prev = -1, last = -1;
        auto val = [&](int v) { return vis[v] ? -1 : key[v]; };
        for (int it = 0; it < phase; ++it) {
            int s = *ranges::max_element(alive, {}, val);
            vis[s] = true, prev = last, last = s;
            for (int v : alive)
                if (!vis[v]) key[v] += w[s][v];
        }
        best = min(best, key[last]); // cut of the phase
        for (int v : alive) { // merge last into prev
            w[prev][v] += w[last][v];
            w[v][prev] = w[prev][v];
        }
        alive.erase(ranges::find(alive, last));
    }
    return best;
}
