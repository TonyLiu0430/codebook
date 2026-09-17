using ll = long long;
using graph_edge = pair<int, ll>; // to, weight
using state = pair<ll, int>;      // distance, vertex
const ll inf = LLONG_MAX / 4;

vector<ll> dijkstra(int source, const vector<vector<graph_edge>> &g) {
    vector<ll> dist(g.size(), inf);
    priority_queue<state, vector<state>, greater<state>> pq;
    dist[source] = 0;
    pq.push({0, source}); // distance, vertex
    while (!pq.empty()) {
        ll d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (d != dist[u]) continue;
        for (graph_edge e : g[u]) {
            int v = e.first;
            ll w = e.second;
            assert(w >= 0);
            if (dist[v] > d + w) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
