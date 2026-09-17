using ll = long long;
const ll inf = LLONG_MAX / 4;

struct edge {
    int from, to;
    ll weight;
};
struct bellman_result {
    vector<ll> dist;
    vector<int> parent;
    bool negative_cycle;
};

bellman_result bellman_ford(int n, int source, const vector<edge> &edges) {
    vector<ll> dist(n, inf);
    vector<int> parent(n, -1);
    dist[source] = 0;
    bool changed = false;
    for (int i = 0; i < n; ++i) {
        changed = false;
        for (edge e : edges) {
            if (dist[e.from] == inf) continue;
            __int128 raw = (__int128)dist[e.from] + e.weight;
            ll nd = raw < -inf ? -inf : raw > inf ? inf : (ll)raw;
            if (nd < dist[e.to]) {
                dist[e.to] = nd;
                parent[e.to] = e.from;
                changed = true;
            }
        }
        if (!changed) break;
    }
    return {dist, parent, changed}; // reachable negative cycle iff changed
}
