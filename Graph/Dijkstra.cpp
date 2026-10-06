using ll = long long;
using graph_edge = pair<int, ll>; // to, weight
using state = pair<ll, int>;      // distance, vertex
const ll inf = LLONG_MAX / 4;

vector<ll> dijkstra(int source, const vector<vector<graph_edge>> &g) {
    vector<ll> dist(g.size(), inf);
    priority_queue<state, vector<state>, greater<>> pq;
    dist[source] = 0;
    pq.push({0, source}); // distance, vertex
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, w] : g[u]) {
            assert(w >= 0);
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
